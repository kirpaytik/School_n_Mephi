#include "../hpp/Landscape.hpp"

#include "../hpp/Castle.hpp"
#include "../hpp/Lair.hpp"
#include "../hpp/Road.hpp"
#include "../hpp/Field.hpp"
#include "../hpp/Enemy.hpp"
#include "../hpp/DefBuild.hpp"
#include "../hpp/BuildAttack.hpp"

#include "../hpp/EffectAttack.hpp"

#include <cmath>
#include <limits>

#include <mutex>
#include <set>

#include <iostream>


Landscape::Landscape() : width(0), height(0), castle(nullptr, 0, 0), lairs(), fields(), roads() {}

Landscape::Landscape(int width, int height, std::tuple<Castle*, int, int> castle,
	std::vector<std::tuple<Lair*, int, int>> lairs, std::vector<Field*> fields, std::vector<Road*> roads) :
	width(width), height(height), castle(castle), lairs(lairs), fields(fields), roads(roads) {}

Landscape::~Landscape()
{
	delete std::get<0>(castle);
	for (std::tuple<Lair*, int, int>& lair: lairs) {
		delete std::get<0>(lair);
	}
	for (Field* field : fields) {
		delete field;
	}
	for (Road* road : roads) {
		delete road;
	}
}


int Landscape::getWidth() const { return width; }

int Landscape::getHeight() const { return height; }

Castle* Landscape::getCastle() const { return std::get<0>(castle); }
int Landscape::getCastleX() const { return std::get<1>(castle); }
int Landscape::getCastleY() const { return std::get<2>(castle); }

std::vector<std::tuple<Lair*, int, int>> Landscape::getLairs() const { return lairs; }

Lair* Landscape::getLair(int indx) const { return std::get<0>(lairs.at(indx)); }

bool Landscape::areEnemiesLeft() const
{
	for (std::tuple<Lair*, int, int> lair : lairs) {
		if (std::get<0>(lair)->getEnemy())
			return true;
	}

	for (Road* road : roads) {
		if (road->getEnemy())
			return true;
	}

	return false;
}

std::vector<Field*> Landscape::getFields() const { return fields; }
std::vector<Road*> Landscape::getRoads() const { return roads; }

Field* Landscape::getField(int indx) const { return fields.at(indx); }

Road* Landscape::getRoad(int indx) const { return roads.at(indx); }

Field* Landscape::getField(int x, int y) const
{
	for (Field* field : fields)
		if (field->getX() == x && field->getY() == y)
			return field;

	return nullptr;
}


Road* Landscape::getRoad(int x, int y) const
{
	for (Road* road : roads)
		if (road->getX() == x && road->getY() == y)
			return road;

	return nullptr;
}


Field* Landscape::getField(const DefBuild* defbuild) const
{
	for (Field* field : fields)
		if (field->getBuild() == defbuild)
			return field;

	return nullptr;
}

Road* Landscape::getEmptyRoad(std::tuple<Lair*, int, int> lairTuple) const
{
	int x_lair = std::get<1>(lairTuple), y_lair = std::get<2>(lairTuple);

	for (Road* road : roads) {
		if (road->isEmptyEnemy() && calculateDistance(x_lair, y_lair, road->getX(), road->getY()) == 1)
			return road;
	}

	return nullptr;
}

Road* Landscape::getRoad(const Enemy* enemy) const
{
	for (Road* road : roads)
		if (road->getEnemy() == enemy)
			return road;

	return nullptr;
}


Road* Landscape::getRoad(const MagicTrap* mtrap) const
{
	for (Road* road : roads)
		if (road->getMTrap() == mtrap)
			return road;

	return nullptr;
}


DefBuild* Landscape::getBuild(int x, int y) const
{
	Field* field = getField(x, y);
	if (field && field->getBuild())
		return field->getBuild();

	Road* road = getRoad(x, y);
	if (road && road->getMTrap())
		return road->getMTrap();

	return nullptr;
}


// void Landscape::setDefBuild(DefBuild* defbuild)
// {
// 	Tower* tower = dynamic_cast<Tower*>(defbuild);
// 	if (tower) {
// 		getField(x, y)->setBuild(defbuild);
// 	}

// 	MagicTrap* mtrap = dynamic_cast<MagicTrap*>(defbuild);
// 	if (mtrap) {
// 		getRoad(x, y)->setMTrap(defbuild);
// 	}
// }


// std::pair<int, int> Landscape::getCoord(DefBuild* defbuild) const
// {
// 	int x, y;

// 	Tower* tower = dynamic_cast<Tower*>(defbuild);
// 	if (tower) {
// 		Field* field = getField(tower);
// 		x = field->getX();
// 		y = field->getY();
// 	}

// 	MagicTrap* mtrap = dynamic_cast<MagicTrap*>(defbuild);
// 	if (mtrap) {
// 		Road* curr_road = getRoad(mtrap);
// 		x = curr_road->getX();
// 		y = curr_road->getY();
// 	}

// 	return std::pair<int, int>(x, y);
// }


void Landscape::spawnTimeProcess()
{
	for (std::tuple<Lair*, int, int> lair_tuple : lairs) {
		Lair* lair = std::get<0>(lair_tuple);
		// reduce time
		lair->spawnTimeProcess();
		// spawn
		if (lair->getSpawnTime() == 0) {
			spawnEnemyAtLair(lair_tuple);
		}
	}
}


Enemy* Landscape::spawnEnemy()
{
	for (std::tuple<Lair*, int, int> lair_tuple : lairs) {
		spawnEnemyAtLair(lair_tuple);
	}

	return nullptr; // doesn't needed but cuz same interface with Lair which needs the return of Enemy*
}


void Landscape::spawnEnemyAtLair(std::tuple<Lair*, int, int> lairTuple)
{
	Road* road = getEmptyRoad(lairTuple);
	if (!road)
		return;

	Enemy* enemy = std::get<0>(lairTuple)->spawnEnemy();
	if (enemy) {
		road->setEnemy(enemy);
	}
}


bool Landscape::moveEnemy(Enemy* enemy, Road* curr_road, std::set<DefBuild*>& mtraps)
{
	if (!enemy->isAlive())
		return true;

	int move_dist = enemy->move();
	Road* const road_temp = curr_road; // remember position before any movement
	Road* next_road = curr_road;

	std::vector<DefBuild*> localMtraps;

	// move step-by-step
	while (move_dist > 0) {
		next_road = next_road->getNextRoad();
		if (!next_road) {
			return true; // castle is reached
		}
		std::unique_lock<std::mutex> lockNext(next_road->getMutex());

		DefBuild* defbuild = next_road->getMTrap();
		if (defbuild) {
			localMtraps.push_back(defbuild); // save the activated mtrap until the enemy would actually be moved
		}

		// if the next road is empty, then move the enemy to it
		if (!next_road->getEnemy()) {
			std::unique_lock<std::mutex> lockCurr(curr_road->getMutex());

			curr_road->setEnemy(nullptr);
			curr_road = next_road;

			lockCurr.unlock();

			next_road->setEnemy(enemy);

			mtraps.insert(localMtraps.begin(), localMtraps.end());
			localMtraps.clear();
		}

		--move_dist;
	}

	return road_temp != curr_road;
}


void Landscape::activateTrapIfEnemy(Road* road)
{
	DefBuild* mtrap = road->getMTrap();
	if (road->getEnemy() && mtrap) {
		attack(mtrap);
	}
}


bool Landscape::setOffMTraps(std::vector<DefBuild*>& mtraps, Enemy* enemy)
{
	for (DefBuild* mtrap : mtraps) {
		attack(mtrap);

		if (enemy && !enemy->isAlive())
			return true;
	}

	mtraps.clear();
	return false;
}


void Landscape::dealDamage(Enemy* enemy, BuildAttack* battack)
{
	int damage = enemy->damageTaken(battack->getDamage());
	enemy->setHealth(enemy->getHealth() - damage);

	if (!enemy->isAlive())
		return;

	if (battack->getEffect()) {
		enemy->applyEffect(battack->getEffect());
		battack->setEffectNoMemory(nullptr);
		// effect pointer should be handled (used or deleted) in Enemy::applyEffect()
		// to avoid memory leaks set here battack->effect to nullptr
	}
}


void Landscape::killEnemy(Enemy* enemy)
{
	Castle* cstl = std::get<0>(castle);
	if (isCastleReached(enemy)) {
		if (enemy->getHealth() > 0)
		cstl->setHealth(cstl->getCurrentHealth() - cstl->damageTaken(enemy->attack()));

	} else {
		cstl->addGold(enemy->getGold());
	}

	Road* curr_road = getRoad(enemy);
	if (curr_road) {
		curr_road->setEnemy(nullptr);
	}

	delete enemy;
}

bool Landscape::isCastleReached(Enemy* enemy) const
{
	Road* road = getRoad(enemy);
	int x_enemy = road->getX(), y_enemy = road->getY();
	int x_castle = std::get<1>(castle), y_castle = std::get<2>(castle);

	return calculateDistance(x_enemy, y_enemy, x_castle, y_castle) == 1;
}


void Landscape::processBuildsReadiness()
{
	for (Field* field : fields) {
		DefBuild* defbuild = field->getBuild();
		if (defbuild && !defbuild->isReady()) {
			defbuild->advanceReadiness();
		}
	}
}


void Landscape::attack(DefBuild* defbuild)
{
	if (defbuild && !defbuild->isReady())
		return;

	// cycle to find enemy to attack and try again if it was killed by another thread
	while (true) {
		Enemy* enemy = attack_strategy(defbuild);
		if (!enemy)
			return;

		std::unique_lock<std::mutex> lock(enemy->getMutex()); // will be automatically unlocked if needed
		if (!enemy->isAlive())
			continue; // find another enemy to attack

		BuildAttack* battack = defbuild->attack();
		dealDamage(enemy, battack);
		delete battack;
		lock.unlock();


		defbuild->setUnready();
		defbuild->onAttackComplete(this);

		return;
	}
}


Enemy* Landscape::attack_strategy(DefBuild* defbuild) const
{
	Enemy* enemy;
	switch (defbuild->getStrategy()) {
	case AttackStrategy::NearestToTower:
		enemy = attack_nearest_to_tower(defbuild);
		break;
	case AttackStrategy::FurthestFromTower:
		enemy = attack_furthest_from_tower(defbuild);
		break;
	case AttackStrategy::NearestToCastle:
		enemy = attack_nearest_to_castle(defbuild);
		break;
	case AttackStrategy::LowestHP:
		enemy = attack_lowest_hp(defbuild);
		break;
	case AttackStrategy::HighestHP:
		enemy = attack_highest_hp(defbuild);
		break;
	}
	return enemy;
}


float Landscape::calculateDistance(int x1, int y1, int x2, int y2)
	{ return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2)); }


Enemy* Landscape::attack_nearest_to_tower(DefBuild* defbuild) const
{
	std::pair<int, int> coords = defbuild->getCoord(this);
	int x_curr = coords.first, y_curr = coords.second;

	Enemy* target_enemy1 = nullptr;
	Enemy* target_enemy2 = nullptr;
	float min_dist1 = std::numeric_limits<float>::infinity();
	float min_dist2 = std::numeric_limits<float>::infinity();

	for (Road* road : roads) {
		Enemy* enemy = road->getEnemy();
		if (!enemy)
			continue;

		std::lock_guard<std::mutex> lock(enemy->getMutex());
		if (!enemy->isAlive())
			continue;

		int x_enemy = road->getX();
		int y_enemy = road->getY();

		float dist = calculateDistance(x_curr, y_curr, x_enemy, y_enemy);
		if (dist < min_dist1) {
			min_dist1 = dist;
			if (dist <= defbuild->getRadius()) {
				target_enemy1 = enemy;
			}
		}
		if (dist < min_dist2 && !( enemy->hasEffect(EffectType::POISON) )) {
			min_dist2 = dist;
			if (dist <= defbuild->getRadius()) {
				target_enemy2 = enemy;
			}
		}
	}

	return target_enemy2 ? target_enemy2 : target_enemy1;
}


Enemy* Landscape::attack_furthest_from_tower(DefBuild* defbuild) const
{
	std::pair<int, int> coords = defbuild->getCoord(this);
	int x_curr = coords.first, y_curr = coords.second;

	// enemy to attack according to the strategy
	Enemy* target_enemy1 = nullptr;
	float max_dist1 = -1.0;

	// enemy to attack according to the strategy combined with no poison effect strategy
	Enemy* target_enemy2 = nullptr;
	float max_dist2 = -1.0;

	for (Road* road : roads) {
		Enemy* enemy = road->getEnemy();
		if (!enemy)
			continue;

		std::lock_guard<std::mutex> lock(enemy->getMutex());
		if (!enemy->isAlive())
			continue;

		int x_enemy = road->getX();
		int y_enemy = road->getY();

		float dist = calculateDistance(x_curr, y_curr, x_enemy, y_enemy);
		if (dist > max_dist1 && dist <= defbuild->getRadius()) {
			max_dist1 = dist;
			target_enemy1 = enemy;
		}
		if (dist > max_dist2 && dist <= defbuild->getRadius() && !( enemy->hasEffect(EffectType::POISON) )) {
			max_dist2 = dist;
			target_enemy2 = enemy;
		}
	}

	return target_enemy2 ? target_enemy2 : target_enemy1;
}


Enemy* Landscape::attack_nearest_to_castle(DefBuild* defbuild) const
{
	int x_castle = std::get<1>(castle), y_castle = std::get<2>(castle);
	std::pair<int, int> coords = defbuild->getCoord(this);
	int x_dbuild = coords.first, y_dbuild = coords.second;

	Enemy* target_enemy = nullptr;
	float min_dist = std::numeric_limits<float>::infinity();

	for (Road* road : roads) {
		Enemy* enemy = road->getEnemy();
		if (!enemy)
			continue;

		std::lock_guard<std::mutex> lock(enemy->getMutex());
		if (!enemy->isAlive())
			continue;

		int x_enemy = road->getX();
		int y_enemy = road->getY();

		float dist_castle = calculateDistance(x_castle, y_castle, x_enemy, y_enemy);
		float dist_dbuild = calculateDistance(x_dbuild, y_dbuild, x_enemy, y_enemy);

		if (dist_dbuild <= defbuild->getRadius() && dist_castle < min_dist) {
			min_dist = dist_castle;
			target_enemy = enemy;
		}
	}

	return target_enemy;
}


Enemy* Landscape::attack_lowest_hp(DefBuild* defbuild) const
{
	std::pair<int, int> coords = defbuild->getCoord(this);
	int x_curr = coords.first, y_curr = coords.second;

	Enemy* target_enemy1 = nullptr;
	Enemy* target_enemy2 = nullptr;
	float min_hp1 = std::numeric_limits<float>::infinity();
	float min_hp2 = std::numeric_limits<float>::infinity();

	for (Road* road : roads) {
		Enemy* enemy = road->getEnemy();
		if (!enemy)
			continue;

		std::lock_guard<std::mutex> lock(enemy->getMutex());
		if (!enemy->isAlive())
			continue;

		int x_enemy = road->getX();
		int y_enemy = road->getY();

		float dist = calculateDistance(x_curr, y_curr, x_enemy, y_enemy);

		if (enemy->getHealth() < min_hp1 && dist <= defbuild->getRadius()) {
			min_hp1 = enemy->getHealth();
			target_enemy1 = enemy;
		}
		if (enemy->getHealth() < min_hp2 && dist <= defbuild->getRadius() && enemy->hasEffect(EffectType::POISON)) {
			min_hp2 = enemy->getHealth();
			target_enemy2 = enemy;
		}
	}

	return target_enemy2 ? target_enemy2 : target_enemy1;
}


Enemy* Landscape::attack_highest_hp(DefBuild* defbuild) const
{
	std::pair<int, int> coords = defbuild->getCoord(this);
	int x_curr = coords.first, y_curr = coords.second;

	Enemy* target_enemy1 = nullptr;
	Enemy* target_enemy2 = nullptr;
	float max_hp1 = 0;
	float max_hp2 = 0;

	for (Road* road : roads) {
		Enemy* enemy = road->getEnemy();
		if (!enemy)
			continue;

		std::lock_guard<std::mutex> lock(enemy->getMutex());
		if (!enemy->isAlive())
			continue;

		int x_enemy = road->getX();
		int y_enemy = road->getY();

		float dist = calculateDistance(x_curr, y_curr, x_enemy, y_enemy);

		if (enemy->getHealth() > max_hp1 && dist <= defbuild->getRadius()) {
			max_hp1 = enemy->getHealth();
			target_enemy1 = enemy;
		}
		if (enemy->getHealth() > max_hp2 && dist <= defbuild->getRadius() && enemy->hasEffect(EffectType::POISON)) {
			max_hp2 = enemy->getHealth();
			target_enemy2 = enemy;
		}
	}

	return target_enemy2 ? target_enemy2 : target_enemy1;
}
