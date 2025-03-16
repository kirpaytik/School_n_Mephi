#include <gtest/gtest.h>
#include "simple.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <stdexcept>


class OneObjTest : public ::testing::Test
{
protected:
	TriSignal sig;
};


class DiffObjTest : public ::testing::Test
{
protected:
	TriSignal sig0;
	TriSignal sig1;
	TriSignal sigX;

	void SetUp()
	{
		sig0.setState('0');
		sig1.setState('1');
		sigX.setState('X');
	}
};


TEST(ConstructorsTest, DefaultCOnstructor)
{
	TriSignal sig;
	ASSERT_EQ(sig.getState(), '0');
}


TEST(ConstructorsTest, ParameterizedConstructor_ValidState)
{
	TriSignal sig1('0');
	ASSERT_EQ(sig1.getState(), '0');

	TriSignal sig2('1');
	ASSERT_EQ(sig2.getState(), '1');

	TriSignal sig3('X');
	ASSERT_EQ(sig3.getState(), 'X');
}


TEST(ConstructorsTest, ParameterizedConstructor_InvalidState)
{
	TriSignal sig('A');
	ASSERT_EQ(sig.getState(), '0');
}


TEST_F(OneObjTest, SetState_ValidState)
{
	sig.setState('0');
	ASSERT_EQ(sig.getState(), '0');

	sig.setState('1');
	ASSERT_EQ(sig.getState(), '1');

	sig.setState('X');
	ASSERT_EQ(sig.getState(), 'X');
}


TEST_F(OneObjTest, SetState_InvalidState)
{
	ASSERT_THROW(sig.setState('A'), std::invalid_argument);
}


TEST_F(OneObjTest, PrintMethod)
{
	std::ostringstream oss;
	sig.setState('1');
	sig.print(oss);
	EXPECT_EQ(oss.str(), "1\n");
}


TEST_F(OneObjTest, FprintMethod_ValidFile)
{
	const std::string filename = "test_file.txt";
	sig.setState('1');
	sig.fprint(filename);

	std::ifstream fin(filename);
	ASSERT_TRUE(fin.is_open());

	std::string line;
	std::getline(fin, line);
	EXPECT_EQ(line, "1");

	fin.close();
	std::remove(filename.c_str()); // remove the unneccessary file
}


TEST_F(OneObjTest, FprintMethod_InvalidFile)
{
	EXPECT_THROW(sig.fprint("/invalid/path/abc"), std::ios_base::failure);
}


TEST_F(DiffObjTest, OrOperator)
{
	EXPECT_EQ((sig0 || sig0).getState(), '0');
	EXPECT_EQ((sig0 || sig1).getState(), '1');
	EXPECT_EQ((sig1 || sig0).getState(), '1');
	EXPECT_EQ((sig1 || sig1).getState(), '1');

	EXPECT_EQ((sig0 || sigX).getState(), 'X');
	EXPECT_EQ((sigX || sig0).getState(), 'X');
	EXPECT_EQ((sig1 || sigX).getState(), '1');
	EXPECT_EQ((sigX || sig1).getState(), '1');
	EXPECT_EQ((sigX || sigX).getState(), 'X');
}


TEST_F(DiffObjTest, AndOperator)
{
	EXPECT_EQ((sig0 && sig0).getState(), '0');
	EXPECT_EQ((sig0 && sig1).getState(), '0');
	EXPECT_EQ((sig1 && sig0).getState(), '0');
	EXPECT_EQ((sig1 && sig1).getState(), '1');

	EXPECT_EQ((sig0 && sigX).getState(), '0');
	EXPECT_EQ((sigX && sig0).getState(), '0');
	EXPECT_EQ((sig1 && sigX).getState(), 'X');
	EXPECT_EQ((sigX && sig1).getState(), 'X');
	EXPECT_EQ((sigX && sigX).getState(), 'X');
}


TEST_F(DiffObjTest, XorOperator)
{
	EXPECT_EQ((sig0 ^ sig0).getState(), '0');
	EXPECT_EQ((sig0 ^ sig1).getState(), '1');
	EXPECT_EQ((sig1 ^ sig0).getState(), '1');
	EXPECT_EQ((sig1 ^ sig1).getState(), '0');

	EXPECT_EQ((sig0 ^ sigX).getState(), 'X');
	EXPECT_EQ((sigX ^ sig0).getState(), 'X');
	EXPECT_EQ((sig1 ^ sigX).getState(), 'X');
	EXPECT_EQ((sigX ^ sig1).getState(), 'X');
	EXPECT_EQ((sigX ^ sigX).getState(), '0');
}


TEST_F(DiffObjTest, NotOperator)
{
	EXPECT_EQ((!sig0).getState(), '1');
	EXPECT_EQ((!sig1).getState(), '0');
	EXPECT_EQ((!sigX).getState(), 'X');
}


TEST_F(DiffObjTest, EqualityOperator)
{
	EXPECT_TRUE(sig0 == sig0);
	EXPECT_TRUE(sig1 == sig1);
	EXPECT_TRUE(sig0 == sigX);
	EXPECT_TRUE(sig1 == sigX);
	EXPECT_TRUE(sigX == sig0);
	EXPECT_TRUE(sigX == sig1);
	EXPECT_TRUE(sigX == sigX);

	EXPECT_FALSE(sig0 == sig1);
	EXPECT_FALSE(sig1 == sig0);
}


TEST_F(DiffObjTest, InequalityOperator)
{
	EXPECT_FALSE(sig0 != sig0);
	EXPECT_FALSE(sig1 != sig1);

	EXPECT_TRUE(sig0 != sigX);
	EXPECT_TRUE(sig1 != sigX);
	EXPECT_TRUE(sigX != sig0);
	EXPECT_TRUE(sigX != sig1);
	EXPECT_TRUE(sigX != sigX);
	EXPECT_TRUE(sig0 != sig1);
	EXPECT_TRUE(sig1 != sig0);
}


TEST_F(DiffObjTest, GreaterThanOperator)
{
	EXPECT_TRUE(sig1 > sig0);
	EXPECT_TRUE(sigX > sigX);
	EXPECT_TRUE(sigX > sig0);
	EXPECT_TRUE(sig1 > sigX);

	EXPECT_FALSE(sig0 > sig1);
	EXPECT_FALSE(sig0 > sig0);
	EXPECT_FALSE(sig1 > sig1);
	EXPECT_FALSE(sig0 > sigX);
	EXPECT_FALSE(sigX > sig1);
}


TEST_F(DiffObjTest, LessThanOperator)
{
	EXPECT_TRUE(sig0 < sig1);
	EXPECT_TRUE(sigX < sigX);
	EXPECT_TRUE(sig0 < sigX);
	EXPECT_TRUE(sigX < sig1);

	EXPECT_FALSE(sig1 < sig0);
	EXPECT_FALSE(sig0 < sig0);
	EXPECT_FALSE(sig1 < sig1);
	EXPECT_FALSE(sigX < sig0);
	EXPECT_FALSE(sig1 < sigX);
}


TEST_F(DiffObjTest, GreaterThanEqualOperator)
{
	EXPECT_TRUE(sig0 >= sig0);
	EXPECT_TRUE(sig1 >= sig1);
	EXPECT_TRUE(sig1 >= sig0);
	EXPECT_TRUE(sig0 >= sigX);
	EXPECT_TRUE(sig1 >= sigX);
	EXPECT_TRUE(sigX >= sig0);
	EXPECT_TRUE(sigX >= sig1);
	EXPECT_TRUE(sigX >= sigX);

	EXPECT_FALSE(sig0 >= sig1);
}


TEST_F(DiffObjTest, LessThanEqualOperator)
{
	EXPECT_TRUE(sig0 <= sig0);
	EXPECT_TRUE(sig1 <= sig1);
	EXPECT_TRUE(sig0 <= sig1);
	EXPECT_TRUE(sig0 <= sigX);
	EXPECT_TRUE(sig1 <= sigX);
	EXPECT_TRUE(sigX <= sig0);
	EXPECT_TRUE(sigX <= sig1);
	EXPECT_TRUE(sigX <= sigX);

	EXPECT_FALSE(sig1 <= sig0);
}


TEST_F(DiffObjTest, PlusOperator)
{
	EXPECT_EQ((sig0 + sig0).getState(), '0');
	EXPECT_EQ((sig0 + sig1).getState(), '1');
	EXPECT_EQ((sig1 + sig0).getState(), '1');
	EXPECT_EQ((sig1 + sig1).getState(), '0');

	EXPECT_EQ((sig0 + sigX).getState(), 'X');
	EXPECT_EQ((sig1 + sigX).getState(), 'X');
	EXPECT_EQ((sigX + sig0).getState(), 'X');
	EXPECT_EQ((sigX + sig1).getState(), 'X');
	EXPECT_EQ((sigX + sigX).getState(), 'X');
}


TEST_F(DiffObjTest, MinusOperator)
{
	EXPECT_EQ((sig0 - sig0).getState(), '0');
	EXPECT_EQ((sig0 - sig1).getState(), '1');
	EXPECT_EQ((sig1 - sig0).getState(), '1');
	EXPECT_EQ((sig1 - sig1).getState(), '0');

	EXPECT_EQ((sig0 - sigX).getState(), 'X');
	EXPECT_EQ((sig1 - sigX).getState(), 'X');
	EXPECT_EQ((sigX - sig0).getState(), 'X');
	EXPECT_EQ((sigX - sig1).getState(), 'X');
	EXPECT_EQ((sigX - sigX).getState(), 'X');
}


TEST_F(DiffObjTest, PrefixIncrementOperator)
{
	EXPECT_EQ((++sig0).getState(), '1');
	EXPECT_EQ((++sig1).getState(), '0');
	EXPECT_EQ((++sigX).getState(), 'X');
}


TEST_F(DiffObjTest, PrefixDecrementOperator)
{
	EXPECT_EQ((--sig0).getState(), '1');
	EXPECT_EQ((--sig1).getState(), '0');
	EXPECT_EQ((--sigX).getState(), 'X');
}


TEST_F(DiffObjTest, PostfixIncrementOperator)
{
	EXPECT_EQ((sig0++).getState(), '0');
	EXPECT_EQ(sig0.getState(), '1');

	EXPECT_EQ((sig1++).getState(), '1');
	EXPECT_EQ(sig1.getState(), '0');

	EXPECT_EQ((sigX++).getState(), 'X');
	EXPECT_EQ(sigX.getState(), 'X');
}


TEST_F(DiffObjTest, PostfixDecrementOperator)
{
	EXPECT_EQ((sig0--).getState(), '0');
	EXPECT_EQ(sig0.getState(), '1');

	EXPECT_EQ((sig1--).getState(), '1');
	EXPECT_EQ(sig1.getState(), '0');

	EXPECT_EQ((sigX--).getState(), 'X');
	EXPECT_EQ(sigX.getState(), 'X');
}


TEST_F(DiffObjTest, AssigmentOperator)
{
	TriSignal sig('0');
	sig = sig0; // 0 -> 0
	EXPECT_EQ(sig.getState(), '0');
	sig.setState('1');
	sig = sig0; // 1 -> 0
	EXPECT_EQ(sig.getState(), '0');
	sig.setState('X');
	sig = sig0; // X -> 0
	EXPECT_EQ(sig.getState(), '0');

	sig.setState('0');
	sig = sig1; // 0 -> 1
	EXPECT_EQ(sig.getState(), '1');
	sig.setState('1');
	sig = sig1; // 1 -> 1
	EXPECT_EQ(sig.getState(), '1');
	sig.setState('X');
	sig = sig1; // X -> 1
	EXPECT_EQ(sig.getState(), '1');

	sig.setState('0');
	sig = sigX; // 0 -> X
	EXPECT_EQ(sig.getState(), 'X');
	sig.setState('1');
	sig = sigX; // 1 -> X
	EXPECT_EQ(sig.getState(), 'X');
	sig.setState('X');
	sig = sigX; // X -> X
	EXPECT_EQ(sig.getState(), 'X');
}


TEST_F(DiffObjTest, PlusEqualsOperator)
{
	TriSignal sig('0');
	sig += sig0; // 0 += 0
	EXPECT_EQ(sig.getState(), '0');
	sig.setState('1');
	sig += sig0; // 1 += 0
	EXPECT_EQ(sig.getState(), '1');
	sig.setState('X');
	sig += sig0; // X += 0
	EXPECT_EQ(sig.getState(), 'X');

	sig.setState('0');
	sig += sig1; // 0 += 1
	EXPECT_EQ(sig.getState(), '1');
	sig.setState('1');
	sig += sig1; // 1 += 1
	EXPECT_EQ(sig.getState(), '0');
	sig.setState('X');
	sig += sig1; // X += 1
	EXPECT_EQ(sig.getState(), 'X');

	sig.setState('0');
	sig += sigX; // 0 += X
	EXPECT_EQ(sig.getState(), 'X');
	sig.setState('1');
	sig += sigX; // 1 += X
	EXPECT_EQ(sig.getState(), 'X');
	sig.setState('X');
	sig += sigX; // X += X
	EXPECT_EQ(sig.getState(), 'X');
}


TEST_F(DiffObjTest, MinusEqualsOperator)
{
	TriSignal sig('0');
	sig -= sig0; // 0 -= 0
	EXPECT_EQ(sig.getState(), '0');
	sig.setState('1');
	sig -= sig0; // 1 -= 0
	EXPECT_EQ(sig.getState(), '1');
	sig.setState('X');
	sig -= sig0; // X -= 0
	EXPECT_EQ(sig.getState(), 'X');

	sig.setState('0');
	sig -= sig1; // 0 -= 1
	EXPECT_EQ(sig.getState(), '1');
	sig.setState('1');
	sig -= sig1; // 1 -= 1
	EXPECT_EQ(sig.getState(), '0');
	sig.setState('X');
	sig -= sig1; // X -= 1
	EXPECT_EQ(sig.getState(), 'X');

	sig.setState('0');
	sig -= sigX; // 0 -= X
	EXPECT_EQ(sig.getState(), 'X');
	sig.setState('1');
	sig -= sigX; // 1 -= X
	EXPECT_EQ(sig.getState(), 'X');
	sig.setState('X');
	sig -= sigX; // X -= X
	EXPECT_EQ(sig.getState(), 'X');
}


TEST_F(DiffObjTest, ChrMethod)
{
	EXPECT_EQ(sig0.chr(), '0');
	EXPECT_EQ(sig1.chr(), '1');
	EXPECT_EQ(sigX.chr(), 'X');
}


TEST_F(DiffObjTest, CharConversionOperator)
{
	EXPECT_EQ(char(sig0), '0');
	EXPECT_EQ(char(sig1), '1');
	EXPECT_EQ(char(sigX), 'X');
}


TEST_F(DiffObjTest, OutputOperator)
{
	std::ostringstream oss;
	oss << sig0;
	EXPECT_EQ(oss.str(), "0");

	oss.str("");
	oss << sig1;
	EXPECT_EQ(oss.str(), "1");

	oss.str("");
	oss << sigX;
	EXPECT_EQ(oss.str(), "X");
}


TEST_F(OneObjTest, InputOperator)
{
	std::istringstream iss("1");
	iss >> sig;
	EXPECT_EQ(sig.getState(), '1');

	iss.str("X");
	iss >> sig;
	EXPECT_EQ(sig.getState(), 'X');

	iss.str("0");
	iss >> sig;
	EXPECT_EQ(sig.getState(), '0');
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
