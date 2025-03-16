#include <gtest/gtest.h>
#include <itreator>
#include "Matrix.hpp"
#include "Cell.hpp"
#include "Field.hpp"
#include "DefBuild.hpp"


TEST(MatrixTest, ConstructorTest)
{
	Matrix<Cell> matr(3, 3);
}


TEST(MatrixTest, AccessTest)
{
	Matrix<Cell> matr(3, 3);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			EXPECT_EQ(matr[i][j].getX(), i);
			EXPECT_EQ(matr[i][j].getY(), j);
		}
	}

	EXPECT_THROW(matr[3], std::out_of_range);
	EXPECT_THROW(matr[2][3], std::out_of_range);
}


TEST(MatrixTest, AccessConstTest)
{
	const Matrix<Cell> matr(3, 3);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			EXPECT_EQ(matr[i][j].getX(), i);
			EXPECT_EQ(matr[i][j].getY(), j);
		}
	}

	EXPECT_THROW(matr[3], std::out_of_range);
	EXPECT_THROW(matr[2][3], std::out_of_range);
}


TEST(MatrixTest, Insertion)
{
	Matrix<Cell> matr(3, 3);
	DefBuild* build = new DefBuild(0, 0, 0, 0);
	Field field(1, 2, build);

	matr.insert(&field);

	EXPECT_EQ(matr[1][2].getX(), 1);
	EXPECT_EQ(matr[1][2].getY(), 2);
	EXPECT_EQ(matr[1][2].getBuild(), build);

	Cell cell1(3, 2);
	Cell cell2(2, 3);
	EXPECT_THROW(matr.insert(cell1), std::out_of_range);
	EXPECT_THROW(matr.insert(cell2), std::out_of_range);
}


TEST(MatrixTest, Removing)
{
	Matrix<Cell> matr(3, 3);
	DefBuild* build = new DefBuild(0, 0, 0, 0);
	Field field(1, 2, build);
	matr.insert(&field);

	matr.remove(1, 2);

	EXPECT_EQ(matr[1][2].getX(), 1);
	EXPECT_EQ(matr[1][2].getY(), 2);
	EXPECT_EQ(matr[1][2].getBuild(), nullptr);

	EXPECT_THROW(matr.remove(3, 2), std::out_of_range);
	EXPECT_THROW(matr.remove(2, 3), std::out_of_range);
}


TEST(IteratorTest, IteratorOperations)
{
	Matrix<Cell> matr(2, 2);

	// Initializtion
	Matrix<Cell>::Iterator it = matr.begin();
	ASSERT_EQ((*it).getX(), 0);
	ASSERT_EQ(it->getX(), 0);

	// Increment
	EXPECT_EQ((++it)->getX(), 0);
	EXPECT_EQ(it->getY(), 1);
	EXPECT_EQ((it++)->getX(), 0);
	EXPECT_EQ(it->getY(), 0);

	// Decrement
	EXPECT_EQ((it--)->getX(), 1);
	EXPECT_EQ(it->getY(), 1);
	EXPECT_EQ((--it)->getY(), 0);
	EXPECT_EQ(it->getX(), 0);

	// Plus number
	ASSERT_EQ((it + 2)->getX(), 1);
	ASSERT_EQ((it + 2)->getY(), 0);

	// Minus number
	EXPECT_EQ(((it + 2) - 1)->getX(), 0);
	EXPECT_EQ(((it + 2) - 1)->getY(), 1);

	// Difference between iterators
	ASSERT_EQ((it + 2) - it, 2);

	// Initialization to end
	EXPECT_EQ(matr.end() - matr.begin(), 4);

	// Access by index
	EXPECT_EQ(it[2].getX(), 1);
	EXPECT_EQ(it[2].getY(), 0);

	// Comparasions
	EXPECT_TRUE(it == matr.begin());
	EXPECT_TRUE(it != (it + 2));
	EXPECT_TRUE(it < (it + 2));
	EXPECT_TRUE(it <= (it + 2));
	EXPECT_TRUE(it <= matr.begin());
	EXPECT_TRUE((it + 2) > it);
	EXPECT_TRUE((it + 2) >= it);
	EXPECT_TRUE(it >= matr.begin());

	// for-each cycle check
	for (auto iter : matr) {
		EXPECT_EQ(iter->getX(), it->getX());
		EXPECT_EQ(iter->getY(), it->getY());
		++it;
	}
}

// Iterator's category check
static_assert(std::is_base_of_v<std::random_access_iterator_tag, 
			  typename std::iterator_traits<Matrix<Cell>::Iterator>::iterator_category>,
			  "Iterator's type is different from what it is declared");




static_assert(
    std::is_base_of_v<std::random_access_iterator_tag, 
                      typename std::iterator_traits<Iterator>::iterator_category>,
    "Iterator does not meet random access iterator requirements"
);
