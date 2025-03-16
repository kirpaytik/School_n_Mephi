#include <gtest/gtest.h>
#include "../hpp/MagicTrap.hpp"

#include "../hpp/BuildAttack.hpp"
#include "../hpp/Landscape.hpp"
#include "../hpp/Road.hpp"
#include "../hpp/PriceTable.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(MagicTrapTest, ConstructorTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int cost = rand() % 150 + 50;
		int level = rand() % 3 + 1;
		int radius = rand() % 4 + 2;
		int damage = rand() % 50 + 10;
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		EffectType effect = static_cast<EffectType>(rand() % 3);

		MagicTrap mtrap(cost, level, radius, damage, strat, effect);

		EXPECT_EQ(mtrap.getCost(), cost);
		EXPECT_EQ(mtrap.getLevel(), level);
		EXPECT_EQ(mtrap.getRadius(), radius);
		EXPECT_EQ(mtrap.getDamage(), damage);
		EXPECT_EQ(mtrap.getStrategy(), strat);
		EXPECT_EQ(mtrap.getEffect(), effect);
	}
}


TEST(MagicTrapTest, GettersAndSettersTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int cost = rand() % 150 + 50;
		int level = rand() % 3 + 1;
		int radius = rand() % 4 + 2;
		int damage = rand() % 50 + 10;
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		EffectType effect = static_cast<EffectType>(rand() % 3);

		MagicTrap mtrap(cost, level, radius, damage, strat, effect);

		EXPECT_EQ(mtrap.getCost(), cost);
		EXPECT_EQ(mtrap.getLevel(), level);
		EXPECT_EQ(mtrap.getRadius(), radius);
		EXPECT_EQ(mtrap.getDamage(), damage);
		EXPECT_EQ(mtrap.getStrategy(), strat);

		EXPECT_EQ(mtrap.getType(), BuildType::MAGICTRAP);

		EXPECT_EQ(mtrap.getEffect(), effect);
		effect = static_cast<EffectType>((static_cast<int>(effect) + rand() % 2 + 1) % 3);
		mtrap.setEffect(effect);
		EXPECT_EQ(mtrap.getEffect(), effect);
	}
}


TEST(MagicTrapTest, MagicTrapLandscapeTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int width = rand() % 100 + 1;
		int height = rand() % 100 + 1;
		std::vector<Road*> roads;
		for (int j = 0; j < rand() % (width * height); ++j) {
			roads.push_back(new Road(rand() % width, rand() % height));
		}
		Landscape land(width, height, std::tuple<Castle*, int, int>(nullptr, -1, -1), {}, {}, roads);

		for (int j = 0; j < roads.size(); ++j) {
			MagicTrap* mtrap = new MagicTrap(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5), static_cast<EffectType>(rand() % 3));
			int x = roads[j]->getX();
			int y = roads[j]->getY();
			mtrap->installOnCell(&land, x, y);
			EXPECT_EQ(land.getRoad(x, y)->getMTrap(), mtrap);

			std::pair<int, int> pair = mtrap->getCoord(&land);
			EXPECT_EQ(pair.first, x);
			EXPECT_EQ(pair.second, y);

			mtrap->onAttackComplete(&land);
			EXPECT_EQ(land.getRoad(x, y)->getMTrap(), nullptr);
		}
	}
}


TEST(MagicTrapTest, AttackTests)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int damage = rand() % 50 + 10;
		EffectType type = static_cast<EffectType>(rand() % 3);
		MagicTrap mtrap(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, damage, static_cast<AttackStrategy>(rand() % 5), type);

		BuildAttack* battack = mtrap.attack();
		EffectAttack* effect = battack->getEffect();
		EXPECT_EQ(battack->getDamage(), damage);
		EXPECT_NE(effect, nullptr);
		EXPECT_EQ(effect->getType(), type);
		delete battack;
	}
}


TEST(MagicTrapTest, UpgradeTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		EffectType effect = static_cast<EffectType>(rand() % 3);
		int level = 1;
		MagicTrap mtrap(rand() % 150 + 50, level, rand() % 4 + 2, rand() % 50 + 10, strat, effect);

		mtrap.upgrade();
		BuildStats stats = PriceTable::instance().getBuildStats(BuildType::MAGICTRAP, strat, effect, 2);
		EXPECT_EQ(mtrap.getCost(), stats.cost);
		EXPECT_EQ(mtrap.getRadius(), stats.radius);
		EXPECT_EQ(mtrap.getDamage(), stats.damage);
		EXPECT_FALSE(mtrap.isUpgraded());

		mtrap.upgrade();
		stats = PriceTable::instance().getBuildStats(BuildType::MAGICTRAP, strat, effect, 3);
		EXPECT_EQ(mtrap.getCost(), stats.cost);
		EXPECT_EQ(mtrap.getRadius(), stats.radius);
		EXPECT_EQ(mtrap.getDamage(), stats.damage);
		EXPECT_TRUE(mtrap.isUpgraded());
	}
}
