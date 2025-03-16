#include <gtest/gtest.h>
#include "../hpp/Cell.hpp"

#include <random>


int NUMBEROFTESTS = 20;


TEST(CellTest, DefaultConstructor)
{
	Cell cell;

	EXPECT_EQ(cell.getX(), 0);
	EXPECT_EQ(cell.getY(), 0);
}


TEST(CellTest, ParameterizedConstructor)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		int x = rand() % 100;
		int y = rand() % 100;

		Cell cell(x, y);

		EXPECT_EQ(cell.getX(), x);
		EXPECT_EQ(cell.getY(), y);
	}
}


TEST(CellTest, SettersAndGetters)
{
	for (int i = 0; i < NUMBEROFTESTS; ++i) {
		Cell cell;
		int newX = rand() % 100;
		int newY = rand() % 100;

		cell.setX(newX);
		cell.setY(newY);

		EXPECT_EQ(cell.getX(), newX);
		EXPECT_EQ(cell.getY(), newY);
	}
}
