#include <gtest/gtest.h>
#include "../hpp/Lair.hpp"
#include "../hpp/Enemy.hpp"

#include <random>
#include <string>
#include <utility>
// #include <cstdlib>
// #include <ctime>


int NUMBEROFTESTS = 20;


char getRandomChar()
{
	int alphLen = 26 * 2 + 10 + 1; // 26 in latin alphabet + 26 for capital case + 10 numbers + 1 space
	const char alphabet[alphLen + 1] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
	return alphabet[rand() % alphLen];
}


std::string getRandomString()
{
	std::string str;
	int len = rand() % 15;
	for (int i = 0; i < len; ++i) {
		str += getRandomChar();
	}

	return str;
}


TEST(LairTests, ConstructorWithEnemyPointersVector)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		std::vector<std::pair<Enemy*, int>> enemies;
		int len = rand() % 10 + 1;

		int lasttime = 100;
		Enemy* lastenemy;
		for (int j = 0; j < len; ++j) {
			Enemy* enemy = new Enemy(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, EnemyType::CUSTOM);
			int spawntime = lasttime - (rand() % 10 + 1);
			enemies.push_back(std::pair<Enemy*, int>(enemy, spawntime));

			lasttime = spawntime;
			lastenemy = enemy;
		}

		std::string name = getRandomString();
		Lair lair(name, enemies);

		EXPECT_EQ(lair.getName(), name);
		EXPECT_EQ(lair.getNumberOfEnemiesLeft(), len);
		EXPECT_EQ(lair.getMaxEnemies(), len);

		EXPECT_EQ(lair.getSpawnTime(), lasttime);
		EXPECT_EQ(lair.getEnemy(), lastenemy);
	}
}


TEST(LairTests, GenerateEnemyTest)
{
	std::vector<std::pair<Enemy*, int>> enemies;
	enemies.push_back(std::pair<Enemy*, int>(nullptr, 0));
	Lair lair(getRandomString(), enemies);

	Enemy* enemy = lair.generateEnemy(EnemyType::NORMAL);
	EXPECT_EQ(enemy->getHealth(), 150);
	EXPECT_EQ(enemy->getSpeed(), 2);
	EXPECT_EQ(enemy->getGold(), 20);
	delete enemy;

	enemy = lair.generateEnemy(EnemyType::FAST);
	EXPECT_EQ(enemy->getHealth(), 100);
	EXPECT_EQ(enemy->getSpeed(), 3);
	EXPECT_EQ(enemy->getGold(), 30);
	delete enemy;

	enemy = lair.generateEnemy(EnemyType::TANK);
	EXPECT_EQ(enemy->getHealth(), 300);
	EXPECT_EQ(enemy->getSpeed(), 1);
	EXPECT_EQ(enemy->getGold(), 50);
	delete enemy;

	enemy = lair.generateEnemy(EnemyType::CUSTOM);
	EXPECT_EQ(enemy, nullptr);
}


TEST(LairTests, ConstructorWithEnemyTypesVector)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		std::vector<std::pair<EnemyType, int>> enemies;
		int len = rand() % 10 + 1;

		int lasttime = 100;
		EnemyType lastenemy;
		for (int j = 0; j < len; ++j) {
			EnemyType enemy = static_cast<EnemyType>(rand() % 3);
			int spawntime = lasttime - (rand() % 10 + 1);
			enemies.push_back(std::pair<EnemyType, int>(enemy, spawntime));

			lasttime = spawntime;
			lastenemy = enemy;
		}

		std::string name = getRandomString();
		Lair lair(name, enemies);

		EXPECT_EQ(lair.getName(), name);
		EXPECT_EQ(lair.getNumberOfEnemiesLeft(), len);
		EXPECT_EQ(lair.getMaxEnemies(), len);

		EXPECT_EQ(lair.getSpawnTime(), lasttime);
		EXPECT_EQ(lair.getEnemy()->getType(), lastenemy);
	}
}


TEST(LairTests, ConstructorWithNumberOfEnemies)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		std::string name = getRandomString();
		int number = rand() % 20 + 1;

		Lair lair(name, number);

		EXPECT_EQ(lair.getName(), name);
		EXPECT_EQ(lair.getNumberOfEnemiesLeft(), number);
		EXPECT_EQ(lair.getMaxEnemies(), number);
	}
}


TEST(LairTests, SpawnTests)
{
	std::vector<std::pair<EnemyType, int>> enemies;
	int time0 = 2;
	int time1 = 3;
	int time2 = 3;
	enemies.push_back(std::pair<EnemyType, int>(static_cast<EnemyType>(rand() % 3), time0));
	enemies.push_back(std::pair<EnemyType, int>(static_cast<EnemyType>(rand() % 3), time1));
	enemies.push_back(std::pair<EnemyType, int>(static_cast<EnemyType>(rand() % 3), time2));
	Lair lair(getRandomString(), enemies);

	EXPECT_EQ(lair.spawnEnemy(), nullptr);

	lair.spawnTimeProcess();
	EXPECT_EQ(lair.getSpawnTime(), time0 - 1);
	EXPECT_EQ(lair.spawnEnemy(), nullptr);

	lair.spawnTimeProcess();
	EXPECT_EQ(lair.getSpawnTime(), time0 - 2);
	Enemy* enemy = lair.spawnEnemy();
	EXPECT_TRUE(enemy != nullptr);
	delete enemy;
	EXPECT_EQ(lair.getSpawnTime(), time1 - 2);
	EXPECT_EQ(lair.spawnEnemy(), nullptr);

	lair.spawnTimeProcess();
	enemy = lair.spawnEnemy();
	EXPECT_TRUE(enemy != nullptr);
	delete enemy;
	enemy = lair.spawnEnemy();
	EXPECT_TRUE(enemy != nullptr);
	delete enemy;
	EXPECT_EQ(lair.getSpawnTime(), -1);
	EXPECT_EQ(lair.getEnemy(), nullptr);
	EXPECT_EQ(lair.spawnEnemy(), nullptr);
}


TEST(LairTests, StringToEnemytypeTest)
{
	EXPECT_EQ(Lair::stringToEnemyType("NORMAL"), EnemyType::NORMAL);
	EXPECT_EQ(Lair::stringToEnemyType("FAST"), EnemyType::FAST);
	EXPECT_EQ(Lair::stringToEnemyType("TANK"), EnemyType::TANK);

	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		std::string str = getRandomString();
		if (str == "NORMAL" || str == "FAST" || str == "TANK")
			{ --i; continue; }
		EXPECT_EQ(Lair::stringToEnemyType(str), EnemyType::CUSTOM);
	}
}
