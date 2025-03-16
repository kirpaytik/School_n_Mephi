#include <gtest/gtest.h>
#include "../hpp/Enemy.hpp"
#include "../hpp/EffectAttack.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(EnemyTests, ConstructorTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int health = rand() % 100 + 10;
		int speed = rand() % 3 + 1;
		int gold = rand() % 100 + 10;
		EnemyType type = static_cast<EnemyType>(rand() % 4);

		Enemy enemy(health, speed, gold, type);

		EXPECT_EQ(enemy.getMaxHealth(), health);
		EXPECT_EQ(enemy.getHealth(), health);
		EXPECT_EQ(enemy.getSpeed(), speed);
		EXPECT_EQ(enemy.getGold(), gold);
		EXPECT_EQ(enemy.getType(), type);
	}
}


TEST(EnemyTests, SettersAndGettersTests)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int maxhealth = rand() % 100 + 10;
		EnemyType type = static_cast<EnemyType>(rand() % 4);
		Enemy enemy(maxhealth, rand() % 3 + 1, rand() % 100 + 10, type);

		EXPECT_EQ(enemy.getType(), type);

		// max hp tests
		int newhealth = maxhealth / 2;
		enemy.setMaxHealth(newhealth); // less than current maxhealth
		EXPECT_EQ(enemy.getMaxHealth(), newhealth);
		EXPECT_EQ(enemy.getMaxHealth(), newhealth);

		enemy.setMaxHealth(maxhealth); // more than current maxhealth
		EXPECT_EQ(enemy.getMaxHealth(), maxhealth);
		EXPECT_EQ(enemy.getHealth(), newhealth);

		// current hp tests
		enemy.setMaxHealth(maxhealth);
		enemy.setHealth(maxhealth);
		EXPECT_EQ(enemy.getHealth(), maxhealth);

		newhealth = rand() % (maxhealth - 9) + 10;
		enemy.setHealth(newhealth);
		EXPECT_EQ(enemy.getMaxHealth(), maxhealth);
		EXPECT_EQ(enemy.getHealth(), newhealth);

		newhealth = maxhealth + rand() % 50 + 10;
		enemy.setHealth(newhealth); // Exceeds maxhealth
		EXPECT_EQ(enemy.getMaxHealth(), maxhealth);
		EXPECT_EQ(enemy.getHealth(), maxhealth);

		newhealth = 0;
		enemy.setHealth(newhealth);
		EXPECT_EQ(enemy.getMaxHealth(), maxhealth);
		EXPECT_EQ(enemy.getHealth(), 0);

		newhealth = -(rand() % (maxhealth - 9) + 10);
		enemy.setHealth(newhealth); // Negative
		EXPECT_EQ(enemy.getMaxHealth(), maxhealth);
		EXPECT_EQ(enemy.getHealth(), 0);

		// speed tests
		int speed = rand() % 3 + 1;
		enemy.setSpeed(speed);
		EXPECT_EQ(enemy.getSpeed(), speed);

		speed = -(rand() % 3 + 1);
		enemy.setSpeed(speed); // Negative
		EXPECT_EQ(enemy.getSpeed(), 1);

		// gold tests
		int gold = rand() % 100 + 10;
		enemy.setGold(gold);
		EXPECT_EQ(enemy.getGold(), gold);

		gold = -(rand() % 100 + 10);
		enemy.setGold(gold); // Negative
		EXPECT_EQ(enemy.getGold(), 0);

	}
}


TEST(EnemyTests, EffectProcessingTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {

		// increasing the applied effect's level (without changing its type) replaces the effect
		for (int j = 0; j < 3; ++j) {
			Enemy enemy(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));

			EffectAttack* effect = new EffectAttack(static_cast<EffectType>(j), 1);
			enemy.applyEffect(effect);
			EXPECT_EQ(enemy.getEffects()[0], effect);

			effect = new EffectAttack(static_cast<EffectType>(j), 2);
			enemy.applyEffect(effect);
			EXPECT_EQ(enemy.getEffects()[0], effect);

			effect = new EffectAttack(static_cast<EffectType>(j), 3);
			enemy.applyEffect(effect);
			EXPECT_EQ(enemy.getEffects()[0], effect);
		}

		// applying same effect (by both type and level) restores its duration
		for (int j = 0; j < 3; ++j) {
			Enemy enemy(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));
			int level = rand() % 3 + 1;

			EffectAttack* effect = new EffectAttack(static_cast<EffectType>(j), level);
			enemy.applyEffect(effect);
			EXPECT_EQ(enemy.getEffects()[0], effect);

			effect = new EffectAttack(static_cast<EffectType>(j), level);
			int duration = effect->getDuration();
			enemy.applyEffect(effect);
			EXPECT_EQ(enemy.getEffects()[0]->getDuration(), duration);

			enemy.getEffects()[0]->setDuration(0);
			ASSERT_EQ(enemy.getEffects()[0]->getDuration(), 0);
			effect = new EffectAttack(static_cast<EffectType>(j), level);
			duration = effect->getDuration();
			enemy.applyEffect(effect); // restore duration
			EXPECT_EQ(enemy.getEffects()[0]->getDuration(), duration);

			duration = enemy.getEffects()[0]->getDuration();
			effect = new EffectAttack(static_cast<EffectType>(j), level);
			effect->setDuration(0);
			enemy.applyEffect(effect); // applying effect with less duration should not change current enemy's effect duration
			EXPECT_EQ(enemy.getEffects()[0]->getDuration(), duration);
		}

		// applying different effects (by their type) should not interfere each other
		Enemy enemy(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));
		EffectAttack* effect = new EffectAttack(EffectType::POISON, 3);
		enemy.applyEffect(effect);
		EXPECT_EQ(enemy.getEffects().size(), 1);
		EXPECT_TRUE(enemy.hasEffect(EffectType::POISON));
		EXPECT_FALSE(enemy.hasEffect(EffectType::SLOWNESS));
		EXPECT_FALSE(enemy.hasEffect(EffectType::WEAKNESS));

		EffectAttack* effect2 = new EffectAttack(EffectType::SLOWNESS, 3);
		enemy.applyEffect(effect2);
		EXPECT_EQ(enemy.getEffects().size(), 2);
		EXPECT_EQ(enemy.getEffects()[0], effect); // and previous one didn't change
		EXPECT_TRUE(enemy.hasEffect(EffectType::POISON));
		EXPECT_TRUE(enemy.hasEffect(EffectType::SLOWNESS));
		EXPECT_FALSE(enemy.hasEffect(EffectType::WEAKNESS));

		EffectAttack* effect3 = new EffectAttack(EffectType::WEAKNESS, 3);
		enemy.applyEffect(effect3);
		EXPECT_EQ(enemy.getEffects().size(), 3);
		EXPECT_EQ(enemy.getEffects()[0], effect);
		EXPECT_EQ(enemy.getEffects()[1], effect2);
		EXPECT_TRUE(enemy.hasEffect(EffectType::POISON));
		EXPECT_TRUE(enemy.hasEffect(EffectType::SLOWNESS));
		EXPECT_TRUE(enemy.hasEffect(EffectType::WEAKNESS));

		// processing effects
		int dur0 = 2;
		int dur1 = 3;
		int dur2 = 3;
		enemy.getEffects()[0]->setDuration(dur0);
		enemy.getEffects()[1]->setDuration(dur1);
		enemy.getEffects()[2]->setDuration(dur2);
		EffectAttack eff(EffectType::POISON, 3);
		int expectedhealth = enemy.getHealth() - eff.getAppliedValue(enemy.getHealth());
		expectedhealth = expectedhealth > 0 ? expectedhealth : 0;

		enemy.processEffects();

		EXPECT_EQ(enemy.getHealth(), expectedhealth);
		EXPECT_EQ(enemy.getEffects().size(), 3);
		EXPECT_EQ(enemy.getEffects()[0]->getDuration(), dur0 - 1);
		EXPECT_EQ(enemy.getEffects()[1]->getDuration(), dur1 - 1);
		EXPECT_EQ(enemy.getEffects()[2]->getDuration(), dur2 - 1);

		// first effect is over
		enemy.processEffects();
		EXPECT_EQ(enemy.getEffects().size(), 2);
		EXPECT_EQ(enemy.getEffects()[0]->getDuration(), dur1 - 2);
		EXPECT_EQ(enemy.getEffects()[1]->getDuration(), dur2 - 2);

		// all effects are over
		enemy.processEffects();
		EXPECT_TRUE(enemy.getEffects().empty());
	}
}


TEST(EnemyTests, MoveTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int speed = rand() % 20 + 1;
		Enemy enemy(rand() % 100 + 10, speed, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));
		EXPECT_EQ(enemy.move(), speed);

		EffectAttack* slowEff = new EffectAttack(EffectType::SLOWNESS, 1);
		enemy.applyEffect(slowEff);
		int expectedMove = speed - slowEff->getAppliedValue(speed);
		expectedMove = expectedMove > 0 ? expectedMove : 0;
		EXPECT_EQ(enemy.move(), expectedMove);

		slowEff = new EffectAttack(EffectType::SLOWNESS, 2);
		enemy.applyEffect(slowEff);
		expectedMove = speed - slowEff->getAppliedValue(speed);
		expectedMove = expectedMove > 0 ? expectedMove : 0;
		EXPECT_EQ(enemy.move(), expectedMove);

		slowEff = new EffectAttack(EffectType::SLOWNESS, 3);
		enemy.applyEffect(slowEff);
		expectedMove = speed - slowEff->getAppliedValue(speed);
		expectedMove = expectedMove > 0 ? expectedMove : 0;
		EXPECT_EQ(enemy.move(), expectedMove);
	}
}


TEST(EnemyTests, DamageTakenTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int maxhealth = rand() % 100 + 10;
		Enemy enemy(maxhealth, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));

		int damage = rand() % maxhealth;
		EXPECT_EQ(enemy.damageTaken(damage), damage);
	}
}


TEST(EnemyTests, IsAliveTest)
{
	Enemy enemy1(rand() % 100 + 10, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));
	Enemy enemy2(0, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));

	EXPECT_TRUE(enemy1.isAlive());
	EXPECT_FALSE(enemy2.isAlive());
}



TEST(EnemyTests, AttackTest)
{
	int health = rand() % 100 + 10;
	Enemy enemy(health, rand() % 3 + 1, rand() % 100 + 10, static_cast<EnemyType>(rand() % 4));

	EXPECT_EQ(enemy.attack(), health);

	EffectAttack* weakEff = new EffectAttack(EffectType::WEAKNESS, 1);
	enemy.applyEffect(weakEff);

	int expectedAttack = health - weakEff->getAppliedValue(health);
	EXPECT_EQ(enemy.attack(), expectedAttack);
}
