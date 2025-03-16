#include <gtest/gtest.h>
#include "../hpp/Cell.hpp"
#include "../hpp/Field.hpp"
#include "../gtest/TestForDefBuild.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(FieldTest, ConstructorWithoutDefBuild)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int x = rand() % 100;
		int y = rand() % 100;

		Field field(x, y);

		EXPECT_EQ(field.getX(), x);
		EXPECT_EQ(field.getY(), y);
		EXPECT_TRUE(field.isEmpty());
	}
}


TEST(FieldTest, ConstructorWithDefBuild)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int x = rand() % 100;
		int y = rand() % 100;

		TestForDefBuild* defbuild = new TestForDefBuild(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5));
		Field field(x, y, defbuild);

		EXPECT_EQ(field.getX(), x);
		EXPECT_EQ(field.getY(), y);

		EXPECT_FALSE(field.isEmpty());
		EXPECT_EQ(field.getBuild(), defbuild);
	}
}


TEST(FieldTest, SetAndGetBuild)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		Field field(0, 0);
		TestForDefBuild* defbuild = new TestForDefBuild(rand() % 150 + 50, rand() % 3 + 1, rand() % 4 + 2, rand() % 50 + 10, static_cast<AttackStrategy>(rand() % 5));

		field.setBuild(defbuild);
		EXPECT_FALSE(field.isEmpty());
		EXPECT_EQ(field.getBuild(), defbuild);
		delete defbuild;

		field.setBuild(nullptr);
		EXPECT_TRUE(field.isEmpty());
		EXPECT_EQ(field.getBuild(), nullptr);
	}
}
