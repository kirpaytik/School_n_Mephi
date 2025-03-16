#include <gtest/gtest.h>
#include "../hpp/Landscape.hpp"

#include <random>

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


class LandscapeTestClass : public ::testing::Test {
protected:
	Landscape* landscape;
	Castle* castle;
	Lair* lair1;
	Lair* lair2;
	std::vector<std::tuple<Lair*, int, int>> lairs;
	std::vector<Field*> fields;
	std::vector<Road*> roads;

	void SetUp() override {
		int width = 20;
		int height = 9;
		castle = new Castle(getRandomString(), rand() % 10000 + 1000, rand() % 1000 + 50);

		lair1 = new Lair(getRandomString()+"_1", 1);
		lair2 = new Lair(getRandomString()+"_2", 2);
		lairs.push_back(std::make_tuple(lair1, 1, 1));
		lairs.push_back(std::make_tuple(lair2, 3, 3));

		fields.push_back(new Field(0, 0));
		fields.push_back(new Field(2, 2));

		roads.push_back(new Road(1, 0));
		roads.push_back(new Road(1, 1));

		landscape = new Landscape(5, 5, std::make_tuple(castle, 4, 4), lairs, fields, roads);
	}

	void TearDown() override {
		delete landscape;
	}
};


TEST(LandscapeTest, ConstructorDefault)
{
	Landscape land();

	EXPECT_EQ(land.getWidth(), 0);
	EXPECT_EQ(land.getHeight(), 0);
	EXPECT_EQ(land.getCastle(), nullptr);
	EXPECT_EQ(land.getCastleX(), 0);
	EXPECT_EQ(land.getCastleY(), 0);
	EXPECT_TRUE(land.getLairs().empty());
	EXPECT_TRUE(land.getFields().empty());
	EXPECT_TRUE(land.getRoads().empty());
}








TEST_F(LandscapeTestClass, TestGetters) {
	EXPECT_EQ(landscape->getWidth(), 5);
	EXPECT_EQ(landscape->getHeight(), 5);
	EXPECT_EQ(landscape->getCastle(), castle);
	EXPECT_EQ(landscape->getCastleX(), 4);
	EXPECT_EQ(landscape->getCastleY(), 4);
	EXPECT_EQ(landscape->getLair(0), lair1);
	EXPECT_EQ(landscape->getLair(1), lair2);
	EXPECT_EQ(landscape->getFields().size(), fields.size());
	EXPECT_EQ(landscape->getRoads().size(), roads.size());
}

TEST_F(LandscapeTestClass, TestAreEnemiesLeft) {
	EXPECT_FALSE(landscape->areEnemiesLeft());
	lair1->spawnEnemy();
	EXPECT_TRUE(landscape->areEnemiesLeft());
}

TEST_F(LandscapeTestClass, TestGetFieldAndRoad) {
	EXPECT_EQ(landscape->getField(0), fields[0]);
	EXPECT_EQ(landscape->getField(2, 2), fields[1]);
	EXPECT_EQ(landscape->getRoad(1, 1), roads[1]);
	EXPECT_EQ(landscape->getRoad(0, 0), nullptr);
}

TEST_F(LandscapeTestClass, TestSpawnEnemyAtLair) {
	Road* road = landscape->getEmptyRoad(lairs[0]);
	EXPECT_NE(road, nullptr);

	landscape->spawnEnemyAtLair(lairs[0]);
	EXPECT_NE(road->getEnemy(), nullptr);
}

TEST_F(LandscapeTestClass, TestMoveEnemy) {
	Enemy* enemy = lair1->spawnEnemy();
	Road* road = landscape->getEmptyRoad(lairs[0]);
	road->setEnemy(enemy);

	EXPECT_TRUE(landscape->moveEnemy(enemy));
	EXPECT_EQ(road->getEnemy(), nullptr);
}

TEST_F(LandscapeTestClass, TestDealDamageAndKillEnemy) {
	Enemy* enemy = lair1->spawnEnemy();
	enemy->setHealth(10);
	BuildAttack* attack = new BuildAttack(15, nullptr);

	landscape->dealDamage(enemy, attack);
	EXPECT_FALSE(enemy->isAlive());

	landscape->killEnemy(enemy);
	EXPECT_EQ(landscape->areEnemiesLeft(), false);

	delete attack;
}

TEST_F(LandscapeTestClass, TestAttackStrategies) {
	DefBuild* defbuild = new DefBuild();
	defbuild->setRadius(2);
	defbuild->setStrategy(AttackStrategy::NearestToTower);

	Enemy* enemy1 = lair1->spawnEnemy();
	Enemy* enemy2 = lair2->spawnEnemy();

	roads[0]->setEnemy(enemy1);
	roads[1]->setEnemy(enemy2);

	EXPECT_EQ(landscape->attack_nearest_to_tower(defbuild), enemy1);
	delete defbuild;
}

TEST_F(LandscapeTestClass, TestProcessBuildsReadiness) {
	DefBuild* defbuild = new DefBuild();
	fields[0]->setBuild(defbuild);
	defbuild->setUnready();

	landscape->processBuildsReadiness();
	EXPECT_TRUE(defbuild->isReady());
	delete defbuild;
}

TEST_F(LandscapeTestClass, TestIsCastleReached) {
	Enemy* enemy = lair1->spawnEnemy();
	roads[1]->setEnemy(enemy);
	EXPECT_FALSE(landscape->isCastleReached(enemy));

	Road* road = new Road(4, 4);
	road->setEnemy(enemy);
	EXPECT_TRUE(landscape->isCastleReached(enemy));
	delete road;
}
