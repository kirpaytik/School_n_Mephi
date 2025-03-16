#include <gtest/gtest.h>
#include "complex.hpp"
#include "simple.hpp"

#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <stdexcept>


int getRandomLength()
{
	return rand() % 20 + 1;
}


char getRandomChar()
{
	const char alphabet[4] = "01X";
	return alphabet[rand() % 3];
}


std::string getRandomString(int len)
{
	std::string str;
	for (int i = 0; i < len; ++i) {
		str += getRandomChar();
	}

	return str;
}


std::string getRandomString()
{
	return getRandomString(getRandomLength());
}


TEST(ConstructorTest, DefaultConstructor)
{
	TriVector vec;
	ASSERT_EQ(vec.getLength(), 0);
	ASSERT_EQ(vec.getVector(), nullptr);
}


TEST(ConstructorTest, ConstructorWithLength_ValidLength)
{
	int len = getRandomLength();
	TriVector vec(len);
	ASSERT_EQ(vec.getLength(), len);
	ASSERT_NE(vec.getVector(), nullptr);
}


TEST(ConstructorTest, ConstructorWithLength_InvalidLength)
{
	ASSERT_THROW(TriVector vec(-1), std::invalid_argument);
}


TEST(ConstructorTest, ConstructorWithLengthAndSignal_ValidLength)
{
	int len = getRandomLength();
	char chr = getRandomChar();
	TriSignal sig(chr);
	TriVector vec(len, sig);

	ASSERT_EQ(vec.getLength(), len);
	for (int i = 0; i < len; ++i) {
		ASSERT_EQ(vec.getSignal(i).getState(), chr);
	}
}


TEST(ConstructorTest, ConstructorWithLengthAndSignal_InvalidLength)
{
	TriSignal sig(getRandomChar());
	ASSERT_THROW(TriVector vec(-1, sig), std::invalid_argument);
}


TEST(ConstructorTest, ConstructorWithString)
{
	for (int qq = 0; qq < 50; ++qq)
	{
		std::string str = getRandomString();
		TriVector vec(str);

		int len = vec.getLength();
		ASSERT_EQ(len, str.size());
		for (int i = 0; i < len; ++i) {
			ASSERT_EQ(vec.getSignal(i).getState(), str[i]);
		}
	}
}


TEST(ConstructorTest, ConstructorWithTriSignalArray_ValidLength)
{
	for (int qq = 0; qq < 50; ++qq)
	{
		int len = getRandomLength();
		// TriSignal signals[len] = {TriSignal('X'), TriSignal('1'), TriSignal('0')};
		// сделать какую-нибудь std
		TriSignal signals[len];
		for (int i = 0; i < len; ++i) {
			signals[i] = TriSignal(getRandomChar());
		}
		TriVector vec(signals, len);

		ASSERT_EQ(vec.getLength(), len);
		for (int i = 0; i < len; ++i) {
			ASSERT_EQ(vec.getSignal(i), signals[i]);
		}
	}
}


TEST(ConstructorTest, ConstructorWithTriSignalArray_InvalidLength)
{
	TriSignal signals[1] = {TriSignal(getRandomChar())};
	ASSERT_THROW(TriVector vec(signals, -1), std::invalid_argument);
	ASSERT_THROW(TriVector vec(nullptr, 1), std::invalid_argument);
}


TEST(ConstructorTest, CopyConstructorTest)
{
	for(int qq = 0; qq < 100; ++qq)
	{
		std::string str = getRandomString();
		TriVector vec1(str);
		TriVector vec2(vec1);

		int len = vec2.getLength();
		ASSERT_EQ(len, vec1.getLength());
		for (int i = 0; i < len; ++i) {
			ASSERT_EQ(vec2.getSignal(i), vec1.getSignal(i));
		}
	}
}


TEST(ConstructorTest, MoveConstructorTest)
{
	for (int qq = 0; qq < 100; ++qq)
	{
		std::string str = getRandomString();
		TriVector vec1(str);
		TriVector vec2(std::move(vec1));

		int len = vec2.getLength();
		ASSERT_EQ(len, str.size());
		for (int i = 0; i < len; ++i) {
			ASSERT_EQ(vec2.getSignal(i), str[i]);
		}
		ASSERT_EQ(vec1.getLength(), 0);
		ASSERT_EQ(vec1.getVector(), nullptr);
	}
}


TEST(SetterTest, SetVectorWithString)
{
	for (int qq = 0; qq < 100; ++qq)
	{
		TriVector vec(getRandomString());

		std::string str = getRandomString();
		vec.setVector(str);

		int len = vec.getLength();
		ASSERT_EQ(len, str.size());
		for (int i = 0; i < len; ++i) {
			ASSERT_EQ(vec.getSignal(i).getState(), str[i]);
		}
	}
}


TEST(SetterTest, SetVectorWithSignalArray_ValidArguments)
{
	for (int qq = 0; qq < 100; ++qq)
	{
		TriVector vec(getRandomString());

		int len = getRandomLength();
		// TriSignal signals[len] = {TriSignal('X'), TriSignal('1'), TriSignal('0')};
		// сделать какую-нибудь std
		TriSignal signals[len];
		for (int i = 0; i < len; ++i) {
			signals[i] = TriSignal(getRandomChar());
		}
		vec.setVector(signals, len);

		ASSERT_EQ(vec.getLength(), len);
		for (int i = 0; i < len; ++i) {
			ASSERT_EQ(vec.getSignal(i), signals[i]);
		}
	}
}


TEST(SetterTest, SetVectorWithSignalArray_InvalidArguments)
{
	std::string str = getRandomString();
	TriVector vec(str);
	TriSignal signals[1] = {TriSignal(getRandomChar())};

	ASSERT_THROW(vec.setVector(signals, -1), std::invalid_argument);
	ASSERT_THROW(vec.setVector(nullptr, 1), std::invalid_argument);

	int len = str.size();
	ASSERT_EQ(vec.getLength(), len);
	for (int i = 0; i < len; ++i) {
		ASSERT_EQ(vec.getSignal(i).getState(), str[i]);
	}
}


TEST(SetterTest, SetSignal_ValidIndex)
{
	TriVector vec(getRandomString(getRandomLength() + 10));

	int len = vec.getLength();
	for (int i = 0; i < len; ++i) {
		char chr = getRandomChar();
		vec.setSignal(TriSignal(chr), i);

		ASSERT_EQ(vec.getSignal(i).getState(), chr);
	}
}


TEST(SetterTest, SetSignal_InvalidIndex)
{
	std::string str = getRandomString();
	TriVector vec(str);

	ASSERT_THROW(vec.setSignal(TriSignal(getRandomChar()), -1), std::out_of_range);
	ASSERT_THROW(vec.setSignal(TriSignal(getRandomChar()), vec.getLength()), std::out_of_range);
}


TEST(PrintingTest, OStreamPrinting)
{
	std::string str = getRandomString();
	TriVector vec(str);

	std::ostringstream out;
	vec.print(out);

	ASSERT_EQ(out.str(), str + "\n");
}


TEST(PrintingTest, FilePrint_ValidFilename)
{
	std::string filename = "abc.txt";
	std::string str = getRandomString();
	TriVector vec(str);
	vec.fprint(filename);

	std::ifstream fin(filename);
	ASSERT_TRUE(fin.is_open());

	std::string line;
	std::getline(fin, line);
	EXPECT_EQ(line, str);

	fin.close();
	std::remove(filename.c_str());
}


TEST(PrintingTest, FilePrint_InvalidFilename)
{
	TriVector vec(getRandomString());
	EXPECT_THROW(vec.fprint("/invalid/path/abc"), std::ios_base::failure);
}


TEST(OperatorsTest, OperatorOr_ValidArguments)
{
	TriVector vec1("000111XXX");
	TriVector vec2("01X01X01X");

	TriVector res = vec1 | vec2;

	EXPECT_EQ(res.getSignal(0).getState(), '0');
	EXPECT_EQ(res.getSignal(1).getState(), '1');
	EXPECT_EQ(res.getSignal(2).getState(), 'X');
	EXPECT_EQ(res.getSignal(3).getState(), '1');
	EXPECT_EQ(res.getSignal(4).getState(), '1');
	EXPECT_EQ(res.getSignal(5).getState(), '1');
	EXPECT_EQ(res.getSignal(6).getState(), 'X');
	EXPECT_EQ(res.getSignal(7).getState(), '1');
	EXPECT_EQ(res.getSignal(8).getState(), 'X');
}


TEST(OperatorsTest, OperatorOr_InvalidArguments)
{
	EXPECT_THROW(TriVector("1") | TriVector("11"), std::invalid_argument);
}


TEST(OperatorsTest, OperatorAnd_ValidArguments)
{
	TriVector vec1("000111XXX");
	TriVector vec2("01X01X01X");

	TriVector res = vec1 & vec2;

	EXPECT_EQ(res.getSignal(0).getState(), '0');
	EXPECT_EQ(res.getSignal(1).getState(), '0');
	EXPECT_EQ(res.getSignal(2).getState(), '0');
	EXPECT_EQ(res.getSignal(3).getState(), '0');
	EXPECT_EQ(res.getSignal(4).getState(), '1');
	EXPECT_EQ(res.getSignal(5).getState(), 'X');
	EXPECT_EQ(res.getSignal(6).getState(), '0');
	EXPECT_EQ(res.getSignal(7).getState(), 'X');
	EXPECT_EQ(res.getSignal(8).getState(), 'X');
}


TEST(OperatorsTest, OperatorAnd_InvalidArguments)
{
	EXPECT_THROW(TriVector("1") & TriVector("11"), std::invalid_argument);
}


TEST(OperatorsTest, OperatorNot)
{
	TriVector vec("01X");

	TriVector res = ~vec;

	EXPECT_EQ(res.getSignal(0).getState(), '1');
	EXPECT_EQ(res.getSignal(1).getState(), '0');
	EXPECT_EQ(res.getSignal(2).getState(), 'X');
}


// TEST(OperatorsTest, OperatorSpaceship)
// {
// 	TriVector vec01("001");
// 	TriVector vec02("11");

// 	ASSERT_EQ(vec01 <=> vec02, std::strong_ordering::greater);
// 	ASSERT_EQ(vec02 <=> vec01, std::strong_ordering::less);

// 	TriVector vec11("01X");
// 	TriVector vec12("011");

// 	ASSERT_EQ(vec11 <=> vec12, std::strong_ordering::equal);

// 	TriVector vec21("00X");
// 	TriVector vec22("0X0");
// 	TriVector vec23("01X");
// 	TriVector vec24("0X1");

// 	ASSERT_EQ(vec23 <=> vec24, std::strong_ordering::equal);
// 	ASSERT_EQ(vec24 <=> vec23, std::strong_ordering::equal);

// 	TriVector vec31("011");
// 	TriVector vec32("0X0");

// 	ASSERT_EQ(vec31 <=> vec32, std::strong_ordering::greater);
// 	ASSERT_EQ(vec32 <=> vec31, std::strong_ordering::less);
// }


TEST(OperatorsTest, OperatorEquality)
{
	TriVector vec01("1");
	TriVector vec02("11");

	ASSERT_EQ(vec01 == vec02, false);
	ASSERT_EQ(vec02 == vec01, false);

	TriVector vec11("0110011");
	TriVector vec12("0110010");

	ASSERT_EQ(vec11 == vec12, false);
	ASSERT_EQ(vec12 == vec11, false);

	TriVector vec21("0101XXX");
	TriVector vec22("01XX01X");

	ASSERT_EQ(vec21 == vec22, true);
	ASSERT_EQ(vec22 == vec21, true);
}


TEST(OperatorsTest, OperatorInequality)
{
	TriVector vec01("1");
	TriVector vec02("11");

	ASSERT_EQ(vec01 != vec02, true);
	ASSERT_EQ(vec02 != vec01, true);

	TriVector vec11("0110011");
	TriVector vec12("0110010");

	ASSERT_EQ(vec11 != vec12, true);
	ASSERT_EQ(vec12 != vec11, true);

	TriVector vec21("0101XXX");
	TriVector vec22("01XX01X");

	ASSERT_EQ(vec21 != vec22, false);
	ASSERT_EQ(vec22 != vec21, false);
}


// TEST(OperatorsTest, OperatorPlus)
// {
// 	//
// }


TEST(OperatorsTest, OperatorMinus)
{
	TriVector vec01("1");
	TriVector vec02("11");

	EXPECT_EQ(vec01 - vec02, TriVector("0"));

	TriVector vec11("000111XXX");
	TriVector vec12("01X01X01X");

	EXPECT_EQ(vec11 - vec12, TriVector("01X10XXXX"));
	EXPECT_EQ(vec12 - vec11, TriVector("01X10XXXX"));
}


TEST(OperatorsTest, OperatorPostfixIncrement)
{
	std::string str = getRandomString();
	TriVector vec(str);
	TriVector vec1(str);
	TriVector vec2 = vec1 + TriVector("1");

	EXPECT_EQ(vec++, vec1);
	EXPECT_EQ(vec, vec2);
}


TEST(OperatorsTest, OperatorPostfixDecrement)
{
	std::string str = getRandomString();
	TriVector vec(str);
	TriVector vec1(str);
	TriVector vec2 = vec1 - TriVector("1");

	EXPECT_EQ(vec--, vec1);
	EXPECT_EQ(vec, vec2);
}


TEST(OperatorsTest, OperatorPrefixIncrement)
{
	std::string str = getRandomString();
	TriVector vec(str);
	TriVector vec2 = vec + TriVector("1");

	EXPECT_EQ(++vec, vec2);
}


TEST(OperatorsTest, OperatorPrefixDecrement)
{
	std::string str = getRandomString();
	TriVector vec(str);
	TriVector vec2 = vec - TriVector("1");

	EXPECT_EQ(--vec, vec2);
}


TEST(OperatorsTest, OperatorCopyAssigment)
{
	TriVector vec1(getRandomString());
	TriVector vec2;

	vec2 = vec1;

	int len = vec2.getLength();
	EXPECT_EQ(len, vec1.getLength());
	for (int i = 0; i < len; ++i) {
		EXPECT_EQ(vec2.getSignal(i), vec1.getSignal(i));
	}

	vec2 = vec2;
	len = vec2.getLength();
	EXPECT_EQ(len, vec1.getLength());
	for (int i = 0; i < len; ++i) {
		EXPECT_EQ(vec2.getSignal(i), vec1.getSignal(i));
	}
}


TEST(OperatorsTest, OperatorMoveAssigment)
{
	std::string str = getRandomString();
	TriVector vec1(str);
	TriVector vec2;

	vec2 = std::move(vec1);

	int len = vec2.getLength();
	EXPECT_EQ(len, str.size());
	for (int i = 0; i < len; ++i) {
		EXPECT_EQ(vec2.getSignal(i).getState(), str[i]);
	}
	EXPECT_EQ(vec1.getLength(), 0);
	EXPECT_EQ(vec1.getVector(), nullptr);
}


TEST(OperatorsTest, OperatorPlusEqual)
{
	TriVector vec(getRandomString());
	TriVector vec1(vec);
	TriVector vec2(getRandomString());
	TriVector vec3;

	vec += vec2;
	vec3 = vec1 + vec2;

	int len = vec.getLength();
	EXPECT_EQ(len, vec3.getLength());
	for (int i = 0; i < len; ++i) {
		EXPECT_EQ(vec.getSignal(i), vec3.getSignal(i));
	}
}


TEST(OperatorsTest, OperatorMinusEqual)
{
	TriVector vec;
	TriVector vec1(getRandomString());
	TriVector vec2(getRandomString());
	TriVector vec3;

	if (vec1.getLength() > vec2.getLength()) {
		vec = vec1;
		vec -= vec2;
		vec3 = vec1 - vec2;
	} else {
		vec = vec2;
		vec -= vec1;
		vec3 = vec2 - vec1;
	}

	int len = vec.getLength();
	EXPECT_EQ(len, vec3.getLength());
	for (int i = 0; i < len; ++i) {
		EXPECT_EQ(vec.getSignal(i), vec3.getSignal(i));
	}
}


TEST(OperatorsTest, OperatorIndex)
{
	std::string str = getRandomString();
	TriVector vec(str);

	int len = vec.getLength();
	for (int i = 0; i < len; ++i) {
		EXPECT_EQ(vec[i].getState(), str[i]);
		vec[i]++;
		EXPECT_EQ(vec[i], TriSignal(str[i]) + TriSignal('1'));
	}

	TriSignal sig;
	EXPECT_THROW(sig = vec[-1], std::out_of_range);
	EXPECT_THROW(sig = vec[len], std::out_of_range);
}


TEST(OperatorsTest, OperatorIndexConst)
{
	std::string str = getRandomString();
	const TriVector vec(str);

	int len = vec.getLength();
	for (int i = 0; i < len; ++i) {
		EXPECT_EQ(vec[i].getState(), str[i]);
	}

	TriSignal sig;
	EXPECT_THROW(sig = vec[-1], std::out_of_range);
	EXPECT_THROW(sig = vec[len], std::out_of_range);
}


TEST(OperatorsTest, OperatorString)
{
	std::string str1 = getRandomString();
	TriVector vec(str1);

	std::string str2 = std::string(vec);

	EXPECT_EQ(str1, str2);
}


TEST(OperatorsTest, OperatorOutputStream)
{
	std::string str = getRandomString();
	TriVector vec(str);

	std::ostringstream out;
	out << vec;

	EXPECT_EQ(out.str(), str);
}


TEST(OperatorsTest, OperatorInputStream)
{
	std::string str = getRandomString();
	std::istringstream in(str);
	TriVector vec;

	in >> vec;

	EXPECT_EQ(vec.getLength(), str.size());
	EXPECT_EQ(vec, TriVector(str));
}


TEST(OtherFuncsTest, FuncRealLength)
{
	TriVector vec1("1111XXX000");
	EXPECT_EQ(vec1.real_length(), vec1.getLength());

	TriVector vec2("000111XXX");
	EXPECT_EQ(vec2.real_length(), 6);
}


TEST(OtherFuncsTest, FuncIsDefined)
{
	TriVector vec1("010100100011101001111001");
	EXPECT_EQ(vec1.isDefined(), true);

	TriVector vec2("010100100011101001111001X");
	EXPECT_EQ(vec2.isDefined(), false);
}


TEST(OtherFuncsTest, FuncToString)
{
	std::string str1 = getRandomString();
	TriVector vec(str1);

	std::string str2 = vec.toString();

	EXPECT_EQ(str1, str2);
}


TEST(VectorFuncsTest, FuncPushBack)
{
	std::string str = getRandomString();
	TriVector vec(str);

	char chr = getRandomChar();
	vec.push_back(TriSignal(chr));

	int len = vec.getLength();
	EXPECT_EQ(len, str.size() + 1);
	for (int i = 0; i < len - 1; ++i) {
		EXPECT_EQ(vec.getSignal(i).getState(), str[i]);
	}
}


TEST(VectorFuncsTest, FuncPopBack)
{
	std::string str = getRandomString();
	TriVector vec(str);

	vec.pop_back();

	int len = vec.getLength();
	EXPECT_EQ(len, str.size() - 1);
	for (int i = 0; i < len; ++i) {
		EXPECT_EQ(vec.getSignal(i).getState(), str[i]);
	}
}


TEST(VectorFuncsTest, FuncInsert)
{
	std::string str = getRandomString(getRandomLength() + 5);
	TriVector vec(str);

	int index = getRandomLength() % 5;
	TriSignal sig = TriSignal(getRandomChar());
	vec.insert(index, sig);

	int len = vec.getLength();
	EXPECT_EQ(len, str.size() + 1);
	for (int i = 0, j = 0; i < len; ++i, ++j) {
		if (i == index) ++i;
		EXPECT_EQ(vec.getSignal(i).getState(), str[j]);
	}

	EXPECT_THROW(vec.insert(-1, sig), std::out_of_range);
	EXPECT_THROW(vec.insert(len, sig), std::out_of_range);
}


TEST(VectorFuncsTest, FuncErase)
{
	std::string str = getRandomString(getRandomLength() + 5);
	TriVector vec(str);

	int index = getRandomLength() % 5;
	vec.erase(index);

	int len = vec.getLength();
	EXPECT_EQ(len, str.size() - 1);
	for (int i = 0, j = 0; i < len; ++i, ++j) {
		if (i == index) ++j;
		EXPECT_EQ(vec.getSignal(i).getState(), str[j]);
	}

	EXPECT_THROW(vec.erase(-1), std::out_of_range);
	EXPECT_THROW(vec.erase(len), std::out_of_range);
}


TEST(VectorFuncsTest, FuncClear)
{
	TriVector vec(getRandomString());

	vec.clear();

	EXPECT_EQ(vec.getLength(), 0);
	EXPECT_EQ(vec.getVector(), nullptr);
}


TEST(VectorFuncsTest, FuncSize)
{
	std::string str = getRandomString();
	TriVector vec(str);

	EXPECT_EQ(vec.size(), str.size());
}


TEST(VectorFuncsTest, FuncResize)
{
	TriVector vec(getRandomString());

	int newsize = getRandomLength();
	vec.resize(newsize);

	EXPECT_EQ(vec.size(), newsize);

	EXPECT_THROW(vec.resize(-1), std::invalid_argument);
}
