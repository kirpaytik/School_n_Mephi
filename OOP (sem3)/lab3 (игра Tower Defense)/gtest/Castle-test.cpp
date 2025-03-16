#include <gtest/gtest.h>
#include "../hpp/Castle.hpp"

#include <random>
#include <string>
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


TEST(CastleTests, ConstructorsTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		std::string name = getRandomString();
		int maxHealth = rand() % 1000 + 100;
		int gold = rand() % 250;

		Castle castle1(name, maxHealth);
		Castle castle2(name, maxHealth, gold);

		EXPECT_EQ(castle1.getName(), name);
		EXPECT_EQ(castle1.getMaxHealth(), maxHealth);
		EXPECT_EQ(castle1.getCurrentHealth(), maxHealth);
		EXPECT_EQ(castle1.getGold(), 0);

		EXPECT_EQ(castle2.getName(), name);
		EXPECT_EQ(castle2.getMaxHealth(), maxHealth);
		EXPECT_EQ(castle2.getCurrentHealth(), maxHealth);
		EXPECT_EQ(castle2.getGold(), gold);
	}
}


TEST(CastleTests, GoldShenanigansTests)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int gold = rand() % 250;
		Castle castle(getRandomString(), rand() % 1000 + 100, gold);

		int goldToAdd = rand() % 100;
		castle.addGold(goldToAdd);

		EXPECT_EQ(castle.getGold(), gold + goldToAdd);

		int goldToTake = rand() % 100;
		castle.reduceGold(goldToTake);

		EXPECT_EQ(castle.getGold(), gold + goldToAdd - goldToTake);
	}
}


TEST(CastleTests, DamageTakenTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int maxHealth = rand() % 1000 + 100;
		Castle castle(getRandomString(), maxHealth);

		int damage = rand() % maxHealth;
		EXPECT_EQ(castle.damageTaken(damage), damage);

		damage = maxHealth + rand() % 1000;  // More than current health
		EXPECT_EQ(castle.damageTaken(damage), maxHealth);
	}
}


TEST(CastleTests, SetHealth)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int maxhealth = rand() % 1000 + 100;
		Castle castle(getRandomString(), maxhealth);

		int newhealth = rand() % (maxhealth - 99) + 100;
		castle.setHealth(newhealth);
		EXPECT_EQ(castle.getCurrentHealth(), newhealth);

		newhealth = maxhealth + rand() % 1000 + 100; // Exceeds max health
		castle.setHealth(newhealth);
		EXPECT_EQ(castle.getCurrentHealth(), maxhealth);

		newhealth = -(rand() % 1000 + 100); // Negative health
		castle.setHealth(newhealth);
		EXPECT_EQ(castle.getCurrentHealth(), 0);
	}
}


TEST(CastleTests, IsAliveTest)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		Castle castle(getRandomString(), rand() % 1000 + 100);
		EXPECT_TRUE(castle.isAlive());

		castle.setHealth(0);
		EXPECT_FALSE(castle.isAlive());

		castle.setHealth(1);
		EXPECT_TRUE(castle.isAlive());

		castle.setHealth(-(rand() % 1000 + 100));
		EXPECT_FALSE(castle.isAlive());
	}
}
