#include <gtest/gtest.h>
#include "../hpp/Cell.hpp"
#include "../hpp/Road.hpp"
#include "../hpp/Enemy.hpp"
#include "../hpp/MagicTrap.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(RoadTest, ConstructorWithoutEntities)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int x = rand() % 100;
		int y = rand() % 100;

		Road road(x, y);

		EXPECT_EQ(road.getX(), x);
		EXPECT_EQ(road.getY(), y);

		EXPECT_TRUE(road.isEmptyEnemy());
		EXPECT_TRUE(road.isEmptyMTrap());
		EXPECT_EQ(road.getNextRoad(), nullptr);
	}
}


TEST(RoadTest, ConstructorWithEnemy)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int x = rand() % 100;
		int y = rand() % 100;

		Enemy* enemy = new Enemy(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));
		Road road(x, y, enemy);

		EXPECT_EQ(road.getX(), x);
		EXPECT_EQ(road.getY(), y);

		EXPECT_FALSE(road.isEmptyEnemy());
		EXPECT_EQ(road.getEnemy(), enemy);

		EXPECT_TRUE(road.isEmptyMTrap());
		EXPECT_EQ(road.getNextRoad(), nullptr);
	}
}


TEST(RoadTest, ConstructorWithMagicTrap)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int x = rand() % 100;
		int y = rand() % 100;

		MagicTrap* mtrap = new MagicTrap(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5), static_cast<EffectType>(rand() % 3));
		Road road(x, y, mtrap);

		EXPECT_EQ(road.getX(), x);
		EXPECT_EQ(road.getY(), y);

		EXPECT_FALSE(road.isEmptyMTrap());
		EXPECT_EQ(road.getMTrap(), mtrap);

		EXPECT_TRUE(road.isEmptyEnemy());
		EXPECT_EQ(road.getNextRoad(), nullptr);
	}
}


TEST(RoadTest, ConstructorWithBothEntities)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int x = rand() % 100;
		int y = rand() % 100;

		Enemy* enemy = new Enemy(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));
		MagicTrap* mtrap = new MagicTrap(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5), static_cast<EffectType>(rand() % 3));
		Road road(x, y, enemy, mtrap);

		EXPECT_EQ(road.getX(), x);
		EXPECT_EQ(road.getY(), y);

		EXPECT_FALSE(road.isEmptyEnemy());
		EXPECT_EQ(road.getEnemy(), enemy);

		EXPECT_FALSE(road.isEmptyMTrap());
		EXPECT_EQ(road.getMTrap(), mtrap);

		EXPECT_EQ(road.getNextRoad(), nullptr);
	}
}


TEST(RoadTest, SetAndGetEnemy)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		MagicTrap* mtrap = new MagicTrap(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5), static_cast<EffectType>(rand() % 3));
		Road road(0, 0, mtrap);

		Enemy* enemy = new Enemy(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));
		road.setEnemy(enemy);

		EXPECT_FALSE(road.isEmptyEnemy());
		EXPECT_EQ(road.getEnemy(), enemy);
		EXPECT_EQ(road.getMTrap(), mtrap); // check that setting enemy does not mess up current mtrap

		road.setEnemy(nullptr);
		EXPECT_TRUE(road.isEmptyEnemy());
		EXPECT_EQ(road.getMTrap(), mtrap);
		delete enemy;
	}
}


TEST(RoadTest, SetAndGetMagicTrap)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		Enemy* enemy = new Enemy(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));
		Road road(0, 0, enemy);

		MagicTrap* mtrap = new MagicTrap(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5), static_cast<EffectType>(rand() % 3));
		road.setMTrap(mtrap);

		EXPECT_FALSE(road.isEmptyMTrap());
		EXPECT_EQ(road.getMTrap(), mtrap);
		EXPECT_EQ(road.getEnemy(), enemy); // check that setting mtrap does not mess up current enemy

		road.setMTrap(nullptr);
		EXPECT_TRUE(road.isEmptyMTrap());
		EXPECT_EQ(road.getEnemy(), enemy);
		delete mtrap;
	}
}


TEST(RoadTest, SetAndGetNextRoad)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		Road road1(0, 0);
		Road road2(1, 1);

		road1.setNextRoad(&road2);

		EXPECT_EQ(road1.getNextRoad(), &road2);
	}
}
