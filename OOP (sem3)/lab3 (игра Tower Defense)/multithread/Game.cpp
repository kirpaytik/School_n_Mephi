#include "../mvc/Game.hpp"

#include "../hpp/Landscape.hpp"
#include "../hpp/PriceTable.hpp"

#include "../hpp/Castle.hpp"
#include "../hpp/Lair.hpp"
#include "../hpp/Enemy.hpp"
#include "../hpp/DefBuild.hpp"
#include "../hpp/Tower.hpp"
#include "../hpp/MagicTower.hpp"
#include "../hpp/MagicTrap.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

#include <thread>
#include <atomic>
#include <cmath>


Game::Game() : land(nullptr) {}


Game::~Game() { delete land; }


Landscape* Game::getLandscape() const { return land; }


bool Game::initializeGame(std::ifstream& file)
{
	try {
		land = parseLandscape(file);
		connectRoads();
		return checkGameLevel();
	} catch (const std::exception& e) {
		std::cerr << "Error initializing game: " << e.what() << std::endl;
		return false;
	}
}


void Game::connectRoads()
{
	Castle* castle = land->getCastle();
	if (!castle) {
		throw std::logic_error("Castle is not initialized.");
	}

	int x_castle = land->getCastleX();
	int y_castle = land->getCastleY();

	// Find castle's adjacent roads, which is the last path's road
	std::unordered_set<Road*> lastRoads;
	for (Road* road : land->getRoads()) {
		if (Landscape::calculateDistance(x_castle, y_castle, road->getX(), road->getY()) == 1.0f) {
			road->setNextRoad(nullptr);
			lastRoads.insert(road);
		}
	}
	if (lastRoads.empty()) {
		throw std::logic_error("No road found adjacent to the castle.");
	}

	std::vector<Road*> roadsWithNext(lastRoads.begin(), lastRoads.end());

	while (!roadsWithNext.empty()) {
		std::vector<Road*> newRoadsWithNext;

		for (Road* curr_road : roadsWithNext) {
			for (Road* road : land->getRoads()) {
				// совпадает, или уже имеет следующую дорогу, или начальная без следующей - так что эта не "предыдущая" для curr_road
				if (road == curr_road || road->getNextRoad() || lastRoads.find(road) != lastRoads.end())
					continue;

				if (Landscape::calculateDistance(curr_road->getX(), curr_road->getY(),
												road->getX(), road->getY()) == 1.0f) {
					road->setNextRoad(curr_road);
					newRoadsWithNext.push_back(road);
				}
			}
		}

		roadsWithNext = std::move(newRoadsWithNext);
	}

	// bool flag = true;
	// while (flag) {
	// 	flag = false;
	// 	for (Road* curr_road : land->getRoads()) {
	// 		if (!curr_road->getNextRoad())
	// 			continue;

	// 		for (Road* road : land->getRoads()) {
	// 			// совпадает или уже имеет следующую дорогу, так что эта не "предыдущая" для curr_road
	// 			if (road == curr_road || road->getNextRoad())
	// 				continue;

	// 			if (Landscape::calculateDistance(curr_road->getX(), curr_road->getY(),
	// 											road->getX(), road->getY()) == 1.0f) {
	// 				road->setNextRoad(curr_road);
	// 				flag = true;
	// 			}
	// 		}
	// 	}
	// }
}


bool Game::checkGameLevel() const
{
	if (land->getCastle() == nullptr) {
		std::cerr << "Error: No castle?" << std::endl;
		return false;
	}

	if (land->getLairs().empty()) {
		std::cerr << "Error: No lairs?" << std::endl;
		return false;
	}

	for (const std::tuple<Lair*, int, int>& lair_tuple : land->getLairs()) {
		Lair* lair = std::get<0>(lair_tuple);
		if (!lair->getEnemy()) {
			std::cerr << "Error: Lair '" << lair->getName() << "': no enemies?" << std::endl;
			return false;
		}
	}

	int x_castle = land->getCastleX();
	int y_castle = land->getCastleY();
	if (x_castle < 0 || x_castle >= land->getWidth() || y_castle < 0 || y_castle >= land->getHeight()) {
		std::cerr << "Where did you put your Castle bruh" << std::endl;
		return false;
	}

	for (const std::tuple<Lair*, int, int>& lair_tuple : land->getLairs()) {
		int x_lair = std::get<1>(lair_tuple);
		int y_lair = std::get<2>(lair_tuple);
		if (x_lair < 0 || x_lair >= land->getWidth() || y_lair < 0 || y_lair >= land->getHeight()) {
			std::cerr << "Where did you put the '" << std::get<0>(lair_tuple)->getName() << "' Lair lol" << std::endl;
			return false;
		}

		bool path_found = false;
		for (Road* road : land->getRoads()) {
			if (land->calculateDistance(x_lair, y_lair, road->getX(), road->getY()) <= 1.0f) {
				Road* curr_road = road;
				while (curr_road != nullptr) {
					if (land->calculateDistance(curr_road->getX(), curr_road->getY(), x_castle, y_castle) <= 1.0f) {
						path_found = true;
						break;
					}
					curr_road = curr_road->getNextRoad();
				}
				if (path_found) break;
			}
		}

		if (!path_found) {
			std::cerr << "Error: No path to castle? Lair '" << std::get<0>(lair_tuple)->getName() << "'." << std::endl;
			return false;
		}
	}

	return true;
}


void Game::checkGameStatus()
{
	if (!land->getCastle()->isAlive()) {
		status = GameStatus::LOSS;
		return;
	}

	if (land->areEnemiesLeft())
		status = GameStatus::RUNNING;
	else
		status = GameStatus::WIN;
}


int Game::isGameOver()
{
	checkGameStatus();
	return status == GameStatus::RUNNING ? 0 : (status == GameStatus::WIN ? 1 : -1);
}


void Game::update()
{
	moveEnemies();
	killCorpses();

	land->spawnTimeProcess();

	enemiesProcessEffects();
	killCorpses();

	land->processBuildsReadiness();

	attackDefBuilds();
	killCorpses();
}


void Game::moveEnemies()
{
	std::vector<Road*> roads = land->getRoads();
	std::reverse(roads.begin(), roads.end());

	std::vector<std::pair<Enemy*, Road*>> enemies;
	for (Road* road : roads) {
		if (Enemy* enemy = road->getEnemy()) {
			enemies.push_back(std::pair<Enemy*, Road*>(enemy, road));
		}
	}

	// если хотя бы один враг двигался или умер, есть смысл попробовать подвигать всех оставшихся на своём месте ещё раз
	bool hasMoved = true;
	while (hasMoved && !enemies.empty()) {
		std::atomic<bool> localMoved = false;

		std::vector<std::pair<Enemy*, Road*>> remainingEnemies;
		std::mutex remainingMutex;
		std::set<DefBuild*> mtrapsToActivate;
		std::mutex mtrapsMutex;

		int numThreads = std::min((int)std::thread::hardware_concurrency() - 2, (int)enemies.size());
		if (numThreads < 1) numThreads = 1;
		int chunkSize = (enemies.size() + numThreads - 1) / numThreads;

		std::vector<std::thread> threads(numThreads);
		for (int t = 0; t < numThreads; ++t) {
			int start = t * chunkSize;
			int end = std::min(start + chunkSize, (int)enemies.size());

			threads[t] = std::thread([&, start, end]() {
				std::vector<std::pair<Enemy*, Road*>> threadRemaining;
				std::set<DefBuild*> threadMtraps;

				for (int i = start; i < end; ++i) {
					Enemy* enemy = enemies[i].first;
					Road* road = enemies[i].second;

					bool isMoved = land->moveEnemy(enemy, road, threadMtraps);

					// если враг, двигаем ещё раз
					if (!isMoved) {
						threadRemaining.push_back(std::pair<Enemy*, Road*>(enemy, road));
					} else {
						localMoved = true;
					}
				}

				std::unique_lock<std::mutex> lock(remainingMutex);
				remainingEnemies.insert(remainingEnemies.end(), threadRemaining.begin(), threadRemaining.end());
				lock.unlock();

				lock = std::move(std::unique_lock<std::mutex>(mtrapsMutex));
				mtrapsToActivate.insert(threadMtraps.begin(), threadMtraps.end());
			}); // thread lambda end
		} // threads cycle end

		for (auto& thread : threads) {
			thread.join();
		}

		std::vector<DefBuild*> mtrapsVector(mtrapsToActivate.begin(), mtrapsToActivate.end());
		land->setOffMTraps(mtrapsVector, nullptr);

		// no need in trying to move dead enemies lol
		remainingEnemies.erase(
			std::remove_if(remainingEnemies.begin(), remainingEnemies.end(),
				[this](const std::pair<Enemy*, Road*>& enemyPair)
				{ return isCorpse(enemyPair.first); }
			),
			remainingEnemies.end()
		);

		killCorpses();

		enemies = std::move(remainingEnemies);
		hasMoved = localMoved;
	}
}


void Game::enemiesProcessEffects()
{
	for (Road* road : land->getRoads()) {
		Enemy* enemy = road->getEnemy();
		if (enemy) {
			enemy->processEffects();
		}
	}
}


void Game::attackDefBuilds()
{
	size_t num_threads = std::thread::hardware_concurrency();
	size_t reserved_threads = 2; // Оставляем 2 потока для системы
	if (num_threads > reserved_threads) {
		num_threads -= reserved_threads;
	} else {
		num_threads = 1; // Минимум 1 поток
	}

	std::vector<DefBuild*> builds;
	for (Field* field : land->getFields()) {
		DefBuild* defbuild = field->getBuild();
		if (defbuild) {
			builds.push_back(defbuild);
		}
	}

	int num_builds = builds.size();
	int builds_per_thread = std::ceil(static_cast<float>(num_builds) / num_threads);

	std::vector<std::thread> threads;
	for (int i = 0; i < num_builds; i += builds_per_thread) {
		threads.emplace_back([this, builds, i, builds_per_thread]() {
			for (int j = i; j < i + builds_per_thread && j < builds.size(); ++j) {
				land->attack(builds[j]);
			}
		});
	}

	for (std::thread& thread : threads) {
		thread.join();
	}
}


void Game::killCorpses()
{
	for (Road* road : land->getRoads()) {
		Enemy* enemy = road->getEnemy();

		if (enemy && ( !enemy->isAlive() || land->isCastleReached(enemy) )) {
			land->killEnemy(enemy);
		}
	}
}


bool Game::killIfCorpse(Enemy* enemy)
{
	if (!enemy->isAlive() || land->isCastleReached(enemy)) {
		land->killEnemy(enemy);
		return true;
	}

	return false;
}


bool Game::isCorpse(Enemy* enemy)
{
	if (!enemy->isAlive() || land->isCastleReached(enemy))
		return true;

	return false;
}


bool Game::canBuildHere(int x, int y) const
{
	Field* field = land->getField(x, y);
	if (field && field->getBuild())
		return false;

	Road* road = land->getRoad(x, y);
	if (road && road->getMTrap())
		return false;

	if (!road && !field)
		return false;

	return true;
}


bool Game::canBuildHere(int x, int y, BuildType type) const
{
	// if это поле; неправильный тип башни или занято
	Field* field = land->getField(x, y);
	if (field && (type == BuildType::MAGICTRAP || field->getBuild()))
		return false;

	// if это дорога; неправильный тип башни или занято
	Road* road = land->getRoad(x, y);
	if (road && (type != BuildType::MAGICTRAP || road->getMTrap()))
		return false;

	// if вообще нет клетки
	if (!road && !field)
		return false;

	return true;
}


bool Game::canUpgradeHere(int x, int y) const
{
	DefBuild* defbuild = land->getBuild(x, y);
	if (defbuild && !defbuild->isUpgraded())
		return true;

	return false;
}


bool Game::isDefBuildHere(int x, int y) const { return land->getBuild(x, y) != nullptr; }


int Game::getUpgradeCost(int x, int y) const
{
	DefBuild* defbuild = land->getBuild(x, y);

	PriceBuildKey key1 = {defbuild->getType(), defbuild->getStrategy(), EffectType::POISON, defbuild->getLevel()};
	if (defbuild->getType() != BuildType::TOWER) key1.effect = defbuild->getEffect();

	PriceBuildKey key2 = key1;
	++(key2.level);

	return PriceTable::getBuildCost(key2) - PriceTable::getBuildCost(key1);
}


bool Game::isEnoughGold(int cost) const { return land->getCastle()->getGold() >= cost; }


void Game::buildDefBuild(int x, int y, PriceBuildKey key)
{
	BuildStats stats;
	try {
		stats = PriceTable::getBuildStats(key);
	} catch (const std::exception& e) {
		std::cerr << "hidude: " << e.what() << std::endl;
		throw e;
	}
	DefBuild* defbuild;

	if (key.type == BuildType::TOWER) {
		defbuild = new Tower(stats.cost, key.level, stats.radius, stats.damage, key.strat, stats.attackspeed);
	}
	else if (key.type == BuildType::MAGICTOWER) {
		defbuild = new MagicTower(stats.cost, key.level, stats.radius, stats.damage, key.strat, stats.attackspeed, key.effect);
	}
	else if (key.type == BuildType::MAGICTRAP) {
		defbuild = new MagicTrap(stats.cost, key.level, stats.radius, stats.damage, key.strat, key.effect);
	}

	// land->setDefBuild(x, y, defbuild);
	defbuild->installOnCell(land, x, y);

	land->getCastle()->reduceGold(stats.cost);
}


void Game::upgradeDefBuild(int x, int y, int cost)
{ land->getBuild(x, y)->upgrade(); land->getCastle()->reduceGold(cost); }
