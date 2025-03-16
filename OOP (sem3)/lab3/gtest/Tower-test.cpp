#include <gtest/gtest.h>
#include "../hpp/Tower.hpp"

#include "../hpp/BuildAttack.hpp"
#include "../hpp/Landscape.hpp"
#include "../hpp/Field.hpp"
#include "../hpp/PriceTable.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(TowerTest, ConstructorTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int cost = rand() % 150 + 50;
		int level = rand() % 3 + 1;
		int radius = rand() % 4 + 2;
		int damage = rand() % 50 + 10;
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		int speed = rand() % 5 + 1;

		Tower tower(cost, level, radius, damage, strat, speed);

		EXPECT_EQ(tower.getCost(), cost);
		EXPECT_EQ(tower.getLevel(), level);
		EXPECT_EQ(tower.getRadius(), radius);
		EXPECT_EQ(tower.getDamage(), damage);
		EXPECT_EQ(tower.getStrategy(), strat);
		EXPECT_EQ(tower.getAttackSpeed(), speed);

		EXPECT_EQ(tower.getType(), BuildType::TOWER);
	}
}


TEST(TowerTest, AttackTests)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int damage = rand() % 50 + 10;
		int speed = rand() % 5 + 1;
		Tower tower(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, damage, static_cast<AttackStrategy>(rand() % 5), speed);

		EXPECT_TRUE(tower.isReady());
		tower.setUnready();
		for (int j = 0; j < speed; ++j) {
			EXPECT_FALSE(tower.isReady());
			tower.advanceReadiness();
		}
		EXPECT_TRUE(tower.isReady());

		BuildAttack* battack = tower.attack();
		EXPECT_EQ(battack->getDamage(), damage);
		EXPECT_EQ(battack->getEffect(), nullptr);
		delete battack;
	}
}


TEST(TowerTest, TowerLandscapeTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int width = rand() % 100 + 1;
		int height = rand() % 100 + 1;
		std::vector<Field*> fields;
		for (int j = 0; j < rand() % (width * height); ++j) {
			fields.push_back(new Field(rand() % width, rand() % height));
		}
		Landscape land(width, height, std::tuple<Castle*, int, int>(nullptr, -1, -1), {}, fields, {});

		for (int j = 0; j < fields.size(); ++j) {
			Tower* tower = new Tower(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5), rand() % 5 + 1);
			int x = fields[j]->getX();
			int y = fields[j]->getY();
			tower->installOnCell(&land, x, y);
			EXPECT_EQ(land.getField(x, y)->getBuild(), tower);

			std::pair<int, int> pair = tower->getCoord(&land);
			EXPECT_EQ(pair.first, x);
			EXPECT_EQ(pair.second, y);

			land.getField(x, y)->setBuild(nullptr);
			delete tower;
		}
	}
}


TEST(TowerTest, UpgradeTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		int level = 1;
		Tower tower(rand() % 150 + 50, level, rand() % 4 + 2, rand() % 50 + 10, strat, rand() % 5 + 1);

		tower.upgrade();
		BuildStats stats = PriceTable::instance().getBuildStats(BuildType::TOWER, strat, 2);
		EXPECT_EQ(tower.getCost(), stats.cost);
		EXPECT_EQ(tower.getRadius(), stats.radius);
		EXPECT_EQ(tower.getDamage(), stats.damage);
		EXPECT_EQ(tower.getAttackSpeed(), stats.attackspeed);
		EXPECT_FALSE(tower.isUpgraded());

		tower.upgrade();
		stats = PriceTable::instance().getBuildStats(BuildType::TOWER, strat, 3);
		EXPECT_EQ(tower.getCost(), stats.cost);
		EXPECT_EQ(tower.getRadius(), stats.radius);
		EXPECT_EQ(tower.getDamage(), stats.damage);
		EXPECT_EQ(tower.getAttackSpeed(), stats.attackspeed);
		EXPECT_TRUE(tower.isUpgraded());
	}
}
