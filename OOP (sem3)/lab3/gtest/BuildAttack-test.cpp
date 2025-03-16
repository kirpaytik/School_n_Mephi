#include <gtest/gtest.h>
#include "../hpp/BuildAttack.hpp"
#include "../hpp/EffectAttack.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(BuildAttackTest, ConstructorWithDamageOnly)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int damage = rand() % 100;

		BuildAttack attack(damage);

		EXPECT_EQ(attack.getDamage(), damage);
		EXPECT_EQ(attack.getEffect(), nullptr);
	}
}


TEST(BuildAttackTest, ConstructorWithEffectOnly)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		EffectAttack* effect = new EffectAttack(static_cast<EffectType>(rand() % 3), rand() % 3 + 1);

		BuildAttack attack(effect);

		EXPECT_EQ(attack.getDamage(), 0);
		EXPECT_EQ(attack.getEffect(), effect);
	}
}


TEST(BuildAttackTest, ConstructorWithDamageAndEffect)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int damage = rand() % 100;
		EffectAttack* effect = new EffectAttack(static_cast<EffectType>(rand() % 3), rand() % 3 + 1);

		BuildAttack attack(damage, effect);

		EXPECT_EQ(attack.getDamage(), damage);
		EXPECT_EQ(attack.getEffect(), effect);
	}
}


TEST(BuildAttackTest, SetDamage)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		BuildAttack attack(0);
		int damage = rand() % 100 + 1;

		attack.setDamage(damage);

		EXPECT_EQ(attack.getDamage(), damage);
	}
}


TEST(BuildAttackTest, SetEffect)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		EffectAttack* effect1 = new EffectAttack(static_cast<EffectType>(rand() % 3), rand() % 3 + 1);
		EffectAttack* effect2 = new EffectAttack(static_cast<EffectType>(rand() % 3), rand() % 3 + 1);
		BuildAttack attack(effect1);

		attack.setEffect(effect2);

		EXPECT_EQ(attack.getEffect(), effect2);
	}
}
