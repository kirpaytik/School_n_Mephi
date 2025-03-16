#include <gtest/gtest.h>
#include "../hpp/EffectAttack.hpp"

#include <random>

int NUMBEROFTESTS = 20;


TEST(EffectAttackTest, Constructor)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		EffectType type = static_cast<EffectType>(rand() % 3);
		int level = rand() % 3 + 1;

		EffectAttack effect(type, level);

		EXPECT_EQ(effect.getType(), type);
		EXPECT_EQ(effect.getLevel(), level);
	}
}


TEST(EffectAttackTest, SettersAndGetters)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		EffectType type = static_cast<EffectType>(rand() % 3);
		int level = rand() % 3 + 1;
		EffectAttack effect(type, level);

		EXPECT_EQ(effect.getType(), type);
		EXPECT_EQ(effect.getLevel(), level);
	}


	EffectAttack effect2(EffectType::WEAKNESS, 2);

	EXPECT_EQ(effect2.getAttribute(), 25);
	EXPECT_EQ(effect2.getMinApplied(), 10);


	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		EffectAttack effect3(static_cast<EffectType>(rand() % 3), rand() % 3 + 1);
		int duration = rand() % 20 + 1;

		effect3.setDuration(duration);
		EXPECT_EQ(effect3.getDuration(), duration);
		EXPECT_FALSE(effect3.isExpired());

		effect3.setDuration(0);
		EXPECT_EQ(effect3.getDuration(), 0);
		EXPECT_TRUE(effect3.isExpired());

		duration = rand() % 20 + 1;
		effect3.addDuration(duration);
		EXPECT_EQ(effect3.getDuration(), duration);
		duration += rand() % 20 + 1;
		effect3.addDuration(duration - effect3.getDuration());
		EXPECT_EQ(effect3.getDuration(), duration);
	}
}


TEST(EffectAttackTest, UpgradeAndLevelsTest)
{
	// POISON
	EffectAttack effect1(EffectType::POISON, 1);
	EXPECT_EQ(effect1.getLevel(), 1);
	EXPECT_EQ(effect1.getAttribute(), 5);
	EXPECT_EQ(effect1.getMinApplied(), 0);
	EXPECT_FALSE(effect1.isUpgraded());
	EXPECT_EQ(effect1.getAppliedValue(rand() % 1000), 5);
	EXPECT_EQ(effect1.getDuration(), 4);

	effect1.upgrade();
	EXPECT_EQ(effect1.getLevel(), 2);
	EXPECT_EQ(effect1.getAttribute(), 8);
	EXPECT_EQ(effect1.getMinApplied(), 0);
	EXPECT_FALSE(effect1.isUpgraded());
	EXPECT_EQ(effect1.getAppliedValue(rand() % 1000), 8);
	EXPECT_EQ(effect1.getDuration(), 6);

	effect1.upgrade();
	EXPECT_EQ(effect1.getLevel(), 3);
	EXPECT_EQ(effect1.getAttribute(), 14);
	EXPECT_EQ(effect1.getMinApplied(), 0);
	EXPECT_TRUE(effect1.isUpgraded());
	EXPECT_EQ(effect1.getAppliedValue(rand() % 1000), 14);
	EXPECT_EQ(effect1.getDuration(), 3);

	EffectAttack effect12(EffectType::POISON, 3);
	EXPECT_TRUE(effect12.isUpgraded());
	effect12.upgrade();
	EXPECT_TRUE(effect1 == effect12); // upgrade max-upgraded effect1 should not change it

	// SLOWNESS
	EffectAttack effect2(EffectType::SLOWNESS, 1);
	EXPECT_EQ(effect2.getLevel(), 1);
	EXPECT_EQ(effect2.getAttribute(), 10);
	EXPECT_EQ(effect2.getMinApplied(), 0);
	EXPECT_FALSE(effect2.isUpgraded());
	int speed = rand() % 20;
	EXPECT_EQ(effect2.getAppliedValue(speed), int(speed * 0.1));
	EXPECT_EQ(effect2.getDuration(), 4);

	effect2.upgrade();
	EXPECT_EQ(effect2.getLevel(), 2);
	EXPECT_EQ(effect2.getAttribute(), 20);
	EXPECT_EQ(effect2.getMinApplied(), 0);
	EXPECT_FALSE(effect2.isUpgraded());
	speed = rand() % 20;
	EXPECT_EQ(effect2.getAppliedValue(speed), int(speed * 0.2));
	EXPECT_EQ(effect2.getDuration(), 6);

	effect2.upgrade();
	EXPECT_EQ(effect2.getLevel(), 3);
	EXPECT_EQ(effect2.getAttribute(), 50);
	EXPECT_EQ(effect2.getMinApplied(), 1);
	EXPECT_TRUE(effect2.isUpgraded());
	speed = rand() % 20 + 2;
	EXPECT_EQ(effect2.getAppliedValue(speed), int(speed * 0.5));
	EXPECT_EQ(effect2.getAppliedValue(1), 1);
	EXPECT_EQ(effect2.getDuration(), 3);

	EffectAttack effect22(EffectType::SLOWNESS, 3);
	EXPECT_TRUE(effect22.isUpgraded());
	effect22.upgrade();
	EXPECT_TRUE(effect2 == effect22);

	// WEAKNESS
	EffectAttack effect3(EffectType::WEAKNESS, 1);
	EXPECT_EQ(effect3.getLevel(), 1);
	EXPECT_EQ(effect3.getAttribute(), 15);
	EXPECT_EQ(effect3.getMinApplied(), 0);
	EXPECT_FALSE(effect3.isUpgraded());
	int damage = rand() % 100;
	EXPECT_EQ(effect3.getAppliedValue(damage), int(damage * 0.15));
	EXPECT_EQ(effect3.getDuration(), 4);

	effect3.upgrade();
	EXPECT_EQ(effect3.getLevel(), 2);
	EXPECT_EQ(effect3.getAttribute(), 25);
	EXPECT_EQ(effect3.getMinApplied(), 10);
	EXPECT_FALSE(effect3.isUpgraded());
	damage = rand() % 100 + 41;
	EXPECT_EQ(effect3.getAppliedValue(damage), int(damage * 0.25));
	damage = rand() % 41;
	EXPECT_EQ(effect3.getAppliedValue(damage), 10);
	EXPECT_EQ(effect3.getDuration(), 6);

	effect3.upgrade();
	EXPECT_EQ(effect3.getLevel(), 3);
	EXPECT_EQ(effect3.getAttribute(), 50);
	EXPECT_EQ(effect3.getMinApplied(), 25);
	EXPECT_TRUE(effect3.isUpgraded());
	damage = rand() % 100 + 51;
	EXPECT_EQ(effect3.getAppliedValue(damage), int(damage * 0.5));
	damage = rand() % 51;
	EXPECT_EQ(effect3.getAppliedValue(damage), 25);
	EXPECT_EQ(effect3.getDuration(), 3);

	EffectAttack effect32(EffectType::WEAKNESS, 3);
	EXPECT_TRUE(effect32.isUpgraded());
	effect32.upgrade();
	EXPECT_TRUE(effect3 == effect32);
}


TEST(EffectAttackTest, EqualityOperator)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		EffectType type = static_cast<EffectType>(rand() % 3);
		int level = rand() % 3 + 1;
		EffectAttack effect1(type, level);
		EffectAttack effect2(type, level);

		EXPECT_TRUE(effect1 == effect2);
	}

	// different levels
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		EffectType type = static_cast<EffectType>(rand() % 3);
		int level1 = rand() % 3 + 1;
		int level2 = level1 % 3 + 1;
		EffectAttack effect1(type, level1);
		EffectAttack effect2(type, level2);

		EXPECT_FALSE(effect1 == effect2);
	}

	// different effect types
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int t = rand() % 3;
		EffectType type1 = static_cast<EffectType>(t);
		EffectType type2 = static_cast<EffectType>((t + 1) % 3);
		int level = rand() % 3 + 1;
		EffectAttack effect1(type1, level);
		EffectAttack effect2(type2, level);

		EXPECT_FALSE(effect1 == effect2);
	}

	// different both type and level
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int t = rand() % 3;
		EffectType type1 = static_cast<EffectType>(t);
		EffectType type2 = static_cast<EffectType>((t + 1) % 3);
		int level1 = rand() % 3 + 1;
		int level2 = level1 % 3 + 1;
		EffectAttack effect1(type1, level1);
		EffectAttack effect2(type2, level2);

		EXPECT_FALSE(effect1 == effect2);
	}
}
