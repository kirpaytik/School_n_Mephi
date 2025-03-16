#include <gtest/gtest.h>
#include "../gtest/TestForDefBuild.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(DefBuildTest, ConstructorTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int cost = rand() % 150 + 50;
		int level = rand() % 3 + 1;
		int radius = rand() % 4 + 2;
		int damage = rand() % 50 + 10;
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);

		TestForDefBuild defbuild(cost, level, radius, damage, strat);

		EXPECT_EQ(defbuild.getCost(), cost);
		EXPECT_EQ(defbuild.getLevel(), level);
		EXPECT_EQ(defbuild.getRadius(), radius);
		EXPECT_EQ(defbuild.getDamage(), damage);
		EXPECT_EQ(defbuild.getStrategy(), strat);
	}
}


TEST(DefBuildTest, GettersAndSettersTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int cost = rand() % 150 + 50;
		int level = rand() % 3 + 1;
		int radius = rand() % 4 + 2;
		int damage = rand() % 50 + 10;
		AttackStrategy strat = static_cast<AttackStrategy>(rand() % 5);
		TestForDefBuild defbuild(cost, level, radius, damage, strat);

		EXPECT_EQ(defbuild.getCost(), cost);
		EXPECT_EQ(defbuild.getLevel(), level);
		EXPECT_EQ(defbuild.getRadius(), radius);
		EXPECT_EQ(defbuild.getDamage(), damage);

		strat = static_cast<AttackStrategy>((static_cast<int>(strat) + rand() % 4 + 1) % 5);
		defbuild.setStrategy(strat);
		EXPECT_EQ(defbuild.getStrategy(), strat);
	}
}


TEST(DefBuildTest, SomeVirtualMethodsTetst)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		TestForDefBuild defbuild(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5));
		EXPECT_TRUE(defbuild.isReady());

		EXPECT_TRUE(defbuild.getEffect() == EffectType::POISON || defbuild.getEffect() == EffectType::SLOWNESS || defbuild.getEffect() == EffectType::WEAKNESS);
		defbuild.setUnready();
		EXPECT_TRUE(defbuild.isReady());
		defbuild.advanceReadiness();
		EXPECT_TRUE(defbuild.isReady());
		defbuild.onAttackComplete(nullptr);
		EXPECT_TRUE(defbuild.isReady());

		int level = 1;
		TestForDefBuild defbuild2(rand() % 150 + 50, level, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5));

		EXPECT_FALSE(defbuild2.isUpgraded());
		defbuild2.upgrade();
		EXPECT_FALSE(defbuild2.isUpgraded());
		defbuild2.upgrade();
		EXPECT_TRUE(defbuild2.isUpgraded());
	}
}
