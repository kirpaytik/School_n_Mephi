#include "../hpp/Lair.hpp"

#include "../hpp/Enemy.hpp"

#include <unordered_map>
#include <algorithm>
#include <random>

#include <iostream>


Lair::Lair(const std::string& name, std::vector<std::pair<Enemy*, int>>& enemies) :
	name(name), enemies(enemies), maxenemies(enemies.size())
{
	std::sort(this->enemies.begin(), this->enemies.end(), [](const std::pair<Enemy*, int>& a, const std::pair<Enemy*, int>& b)
		{ return a.second < b.second; });

	enemyParams[EnemyType::NORMAL] = {150, 2, 20};
	enemyParams[EnemyType::FAST] = {100, 3, 30};
	enemyParams[EnemyType::TANK] = {300, 1, 50};
}

Lair::Lair(const std::string& name, const std::vector<std::pair<EnemyType, int>>& enemies) :
	name(name), enemies(), maxenemies(enemies.size())
{
	enemyParams[EnemyType::NORMAL] = {150, 2, 20};
	enemyParams[EnemyType::FAST] = {100, 3, 30};
	enemyParams[EnemyType::TANK] = {300, 1, 50};

	for (std::pair<EnemyType, int> enemy_pair : enemies) {
		Enemy* enemy = generateEnemy(enemy_pair.first);
		this->enemies.push_back(std::make_pair(enemy, enemy_pair.second));
	}

	std::sort(this->enemies.begin(), this->enemies.end(), [](const std::pair<Enemy*, int>& a, const std::pair<Enemy*, int>& b)
		{ return a.second < b.second; });
}

Lair::Lair(const std::string& name, int numEnemies) : name(name), maxenemies(numEnemies)
{
	enemyParams[EnemyType::NORMAL] = {150, 2, 20};
	enemyParams[EnemyType::FAST] = {100, 3, 30};
	enemyParams[EnemyType::TANK] = {300, 1, 50};

	int spawnTime = 0;
	for (int i = 0; i < numEnemies; ++i) {
		EnemyType type = (EnemyType)((rand() % 4) % 3); // so NORMAL will be 2x more likely to spawn
		Enemy* enemy = generateEnemy(type);
		spawnTime += rand() % 7 + 1;
		enemies.push_back(std::make_pair(enemy, spawnTime));
	}

	std::sort(this->enemies.begin(), this->enemies.end(), [](const std::pair<Enemy*, int>& a, const std::pair<Enemy*, int>& b)
		{ return a.second < b.second; });
}

Lair::~Lair()
{
	for (std::pair<Enemy*, int>& pair : enemies) {
		delete pair.first;
	}
}


Enemy* Lair::generateEnemy(EnemyType type)
{
	if (enemyParams.find(type) != enemyParams.end()) {
		return new Enemy(enemyParams[type].maxhealth, 
						 enemyParams[type].speed,
						 enemyParams[type].gold,
						 type);
	}

	return nullptr;
}

std::string Lair::getName() const { return name; }

EnemyType Lair::stringToEnemyType(const std::string& type)
{
	if (type == "NORMAL") return EnemyType::NORMAL;
	if (type == "FAST") return EnemyType::FAST;
	if (type == "TANK") return EnemyType::TANK;
	return EnemyType::CUSTOM;
}

// IControlSpawns
Enemy* Lair::getEnemy() const { if (enemies.empty()) return nullptr; return enemies[0].first; }
int Lair::getSpawnTime() const { if (enemies.empty()) return -1; return enemies[0].second; }
int Lair::getNumberOfEnemiesLeft() const { return enemies.size(); }
int Lair::getMaxEnemies() const { return maxenemies; }

void Lair::spawnTimeProcess()
{
	for (std::pair<Enemy*, int>& enemy: enemies) {
		if (enemy.second > 0)
			--enemy.second;
	}
}


Enemy* Lair::spawnEnemy()
{
	if (enemies.empty())
		return nullptr;

	if (enemies[0].second == 0) {
		Enemy* enemy = enemies[0].first;
		enemies.erase(enemies.begin());
		return enemy;
	}

	return nullptr;
}
