#include <gtest/gtest.h>
#include "../hpp/MagicTower.hpp"

#include "../hpp/BuildAttack.hpp"
#include "../hpp/PriceTable.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(MagicTowerTest, ConstructorTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int cost = rand() % 150 + 50;
		int level = rand() % 3 + 1;
		int radius = rand() % 4 + 2;
		int damage = rand() % 50 + 10;
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		int speed = rand() % 5 + 1;
		EffectType effect = static_cast<EffectType>(rand() % 3);

		MagicTower mtower(cost, level, radius, damage, strat, speed, effect);

		EXPECT_EQ(mtower.getCost(), cost);
		EXPECT_EQ(mtower.getLevel(), level);
		EXPECT_EQ(mtower.getRadius(), radius);
		EXPECT_EQ(mtower.getDamage(), damage);
		EXPECT_EQ(mtower.getStrategy(), strat);
		EXPECT_EQ(mtower.getAttackSpeed(), speed);
		EXPECT_EQ(mtower.getEffect(), effect);
	}
}


TEST(MagicMagicTowerTest, GettersAndSettersTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int cost = rand() % 150 + 50;
		int level = rand() % 3 + 1;
		int radius = rand() % 4 + 2;
		int damage = rand() % 50 + 10;
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		int speed = rand() % 5 + 1;
		EffectType effect = static_cast<EffectType>(rand() % 3);

		MagicTower mtower(cost, level, radius, damage, strat, speed, effect);

		EXPECT_EQ(mtower.getCost(), cost);
		EXPECT_EQ(mtower.getLevel(), level);
		EXPECT_EQ(mtower.getRadius(), radius);
		EXPECT_EQ(mtower.getDamage(), damage);
		EXPECT_EQ(mtower.getStrategy(), strat);
		EXPECT_EQ(mtower.getAttackSpeed(), speed);

		EXPECT_EQ(mtower.getType(), BuildType::MAGICTOWER);

		EXPECT_EQ(mtower.getEffect(), effect);
		effect = static_cast<EffectType>((static_cast<int>(effect) + rand() % 2 + 1) % 3);
		mtower.setEffect(effect);
		EXPECT_EQ(mtower.getEffect(), effect);
	}
}


TEST(MagicTowerTest, AttackTests)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int damage = rand() % 50 + 10;
		EffectType type = static_cast<EffectType>(rand() % 3);
		MagicTower mtower(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, damage, static_cast<AttackStrategy>(rand() % 5), rand() % 5 + 1, type);

		BuildAttack* battack = mtower.attack();
		EffectAttack* effect = battack->getEffect();
		EXPECT_EQ(battack->getDamage(), damage);
		EXPECT_NE(effect, nullptr);
		EXPECT_EQ(effect->getType(), type);
		delete battack;
	}
}


TEST(MagicTowerTest, UpgradeTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		EffectType effect = static_cast<EffectType>(rand() % 3);
		int level = 1;
		MagicTower mtower(rand() % 150 + 50, level, rand() % 4 + 2, rand() % 50 + 10, strat, rand() % 5 + 1, effect);

		mtower.upgrade();
		BuildStats stats = PriceTable::instance().getBuildStats(BuildType::MAGICTOWER, strat, effect, 2);
		EXPECT_EQ(mtower.getCost(), stats.cost);
		EXPECT_EQ(mtower.getRadius(), stats.radius);
		EXPECT_EQ(mtower.getDamage(), stats.damage);
		EXPECT_EQ(mtower.getAttackSpeed(), stats.attackspeed);
		EXPECT_FALSE(mtower.isUpgraded());

		mtower.upgrade();
		stats = PriceTable::instance().getBuildStats(BuildType::MAGICTOWER, strat, effect, 3);
		EXPECT_EQ(mtower.getCost(), stats.cost);
		EXPECT_EQ(mtower.getRadius(), stats.radius);
		EXPECT_EQ(mtower.getDamage(), stats.damage);
		EXPECT_EQ(mtower.getAttackSpeed(), stats.attackspeed);
		EXPECT_TRUE(mtower.isUpgraded());
	}
}
