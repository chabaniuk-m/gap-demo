#include "gtest/gtest.h"
#include "C-solution/Polynom/Polynom.h"
#include "C-solution/const.h"

int mod;

TEST(Polynom, operatorQuotient)
{
    Polynom a, b;
    Polynom res;

    mod = 5;
    a = {new int[5]{2,0,1,3,4},5};
    b = {new int[3]{1,3,3},3};
    res = Polynom(new int[3]{3,3,3},3);
    EXPECT_EQ(a/b, res);

    mod = 3;
    a = {new int[5]{2,0,1,3,0},5};
    b = {new int[3]{1,0,3},3};
    res = Polynom(new int[3]{2,0,1},3);
    EXPECT_EQ(a/b, res);

    mod = 7;
    a = {new int[7]{6,0,1,3,6,0,0},7};
    b = {new int[6]{3,1,3,0,5,0},6};
    res = Polynom(new int[1]{4},1);
    EXPECT_EQ(a/b, res);
}

TEST(Polynom, operatorRemainder)
{
    Polynom a, b;
    Polynom res;

    mod = 5;
    a = {new int[5]{2,0,1,3,4},5};
    b = {new int[3]{1,3,3},3};
    res = Polynom(new int[2]{4,3},2);
    EXPECT_EQ(a%b, res);

    mod = 3;
    a = {new int[5]{2,0,1,3,0},5};
    b = {new int[3]{1,0,3},3};
    res = Polynom();
    EXPECT_EQ(a%b, res);

    mod = 7;
    a = {new int[7]{6,0,1,3,6,0,0},7};
    b = {new int[6]{3,1,3,0,5,0},6};
    res = Polynom(new int[4]{1,3,3,3},4);
    EXPECT_EQ(a%b, res);
}

TEST(Polynom, gcd)
{
    Polynom a, b;
    Polynom res;

    mod = 7;
    a = {new int[7]{6,0,1,3,6,0,0},7};
    b = {new int[6]{3,1,3,0,5,0},6};
    res = Polynom(new int[1]{1},1);
    EXPECT_EQ(gcd(a,b), res);

    mod = 7;
    a = {new int[12]{18,6,21,10,39,28,18,30,14,21,14,2},12};
    a.recover();
    b = {new int[7]{6,0,1,3,8,4,2},7};
    b.recover();
    res = Polynom(new int[7]{6,0,1,3,1,4,2},7);
    EXPECT_EQ(gcd(a,b), res);
}

TEST(Polynom, AddOperator) 
{
	mod = 5
	Polynom a, b, expected, actual;

	// a = 1 + 2x + 3x^2 +4x^3
	// b = 2 + 2x + 2x^2 + 2x^3
	// a + b = 3 + 4x + x^3
	a = { new int[4]{1, 2, 3, 4}, 4 };
	b = { new int[4]{2, 2, 2, 2}, 4 };
	expected = { new int[4] {3, 4, 0, 1}, 4 };
	actual = a + b;
	EXPECT_EQ(expected.power, 3);
	EXPECT_EQ(expected.len, 4);
	EXPECT_EQ(expected, actual);

	// a = 1 + 2x + 3x^2 +4x^3
	// b = 0;
	// a + b = 1 + 2x + 3x^2 +4x^3
	a = { new int[4]{1, 2, 3, 4}, 4 };
	b = { new int[1]{0}, 1 };
	expected = { new int[4]{1, 2, 3, 4}, 4 };
	actual = a + b;
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected.power, 3);
	EXPECT_EQ(expected.len, 4);

	// a = 4 + 4x + 4x^2 + 4x^3 + 4x^4 + 4x^5 + 4x^6 + 4x^7 + 4x^8 + 4x^9 + 4x^10 + 4x^11 + 4x^12 + 4x^13 + 4x^14 + 4x^15;
	// b = 4 + 4x + 4x^2 + 4x^3 + 4x^4 + 4x^5 + 4x^6 + 4x^7 + 4x^8 + 4x^9 + 4x^10 + 4x^11 + 4x^12 + 4x^13 + 4x^14 + 4x^15;
	// a + b = 3 + 3x + 3x^2 + 3x^3 + 3x^4 + 3x^5 + 3x^6 + 3x^7 + 3x^8 + 3x^9 + 3x^10 + 3x^11 + 3x^12 + 3x^13 + 3x^13 + 3x^15
	a = { new int[16]{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, 16 };
	b = { new int[16]{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, 16 };
	expected = { new int[16]{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, 16 };
	actual = a + b;
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected.power, 15);
	EXPECT_EQ(expected.len, 16);

	// a = 1 + 2x + 3x^2
	// b = 4 + 3x + 2x^2
	// a + b = 0
	a = { new int[3]{1, 2, 3}, 3 };
	b = { new int[3]{4, 3, 2}, 3 };
	actual = a + b;
	expected = { new int[1]{0}, 1 };
	EXPECT_EQ(actual, expected);
	EXPECT_EQ(expected.power, 0);
	EXPECT_EQ(expected.len, 1);
}
TEST(Polynom, SubtractOperator)
{
	mod = 5
	Polynom a, b, expected, actual;

	// a = 1 + 2x + 3x^2
	// b = 1 + 2x +3x^2
	// a - b = 0
	a = { new int[3] {1, 2, 3}, 3 };
	b = { new int[3] {1, 2, 3}, 3 };
	expected = { new int[1] {0}, 1 };
	actual = a - b;
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected.power, 0);
	EXPECT_EQ(expected.len, 1);

	// a = 3 + 4x + 2x^2 + 4x^3 + x^8
	// b = 4 + 4x + x^2 + 2x^3 + x^4 + 3x^ 5
	// a - b = 4 + x^2 + 2x^3 + 4x^4 + 2x^5 + x^8
	a = { new int[9]{3, 4, 2, 4, 0, 0, 0, 0, 1}, 9 };
	b = { new int[6]{4, 4, 1, 2, 1, 3}, 6 };
	expected = { new int[9] {4, 0, 1, 2, 4, 2, 0, 0, 1 }, 9 };
	actual = a - b;
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected.power, 8);
	EXPECT_EQ(expected.len, 9);

	// a = 2 + 2x + 2x^2 + 4x^3
	// b = 3x + 2x^2 + 4x^3
	// a - b = 2 + 4x;
	a = { new int[4]{2, 2, 2, 4}, 4 };
	b = { new int[4]{0, 3, 2, 4}, 4 };
	expected = { new int[2]{2, 4}, 2 };
	actual = a - b;
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected.len, 2);
	EXPECT_EQ(expected.power, 1);
}
TEST(Polynom, MultiplyOperator)
{
	mod = 5
	Polynom a, b, expected, actual;

	// a = 1 + 2x + 2x^2 + 3x^3 + 4x^4
	// b = 0
	// a * b = 0
	a = { new int[5]{1, 2, 2, 3, 4}, 5 };
	b = { new int[1]{0}, 1 };
	actual = a * b;
	expected = { new int[1]{0}, 1 };
	EXPECT_EQ(actual, expected);
	EXPECT_EQ(expected.power, 0);
	EXPECT_EQ(expected.len, 1);

	// a = 1 + 2x + 2x^2 + 3x^3 + 4x^4
	// b = 1
	// a * b = 1 + 2x + 2x^2 + 3x^3 + 4x^4
	a = { new int[5]{1, 2, 2, 3, 4}, 5 };
	b = { new int[1]{1}, 1 };
	actual = a * b;
	expected = { new int[5]{1, 2, 2, 3, 4}, 5 };
	EXPECT_EQ(actual, expected);
	EXPECT_EQ(expected.power, 4);
	EXPECT_EQ(expected.len, 5);

	// a = 6 + 4x + x^2 +3x^3 + 2x^4 +3x^5
	// b = 4 + 2x +x^2 + 2x^4 +4x^5
	// a * b = 12x^10 + 14x^9 + 16x^8 +13x^7 + 26x^6 + 51x^5 + 27x^4 + 18x^3 + 18x^2 + 28x + 24 (mod 5) =
	// = 2x^10 + 4x^9 + x^8 +3x^7 + x^6 + x^5 + 2x^4 + 3x^3 + 3x^2 + 3x + 4
	a = { new int[6]{6, 4, 1, 3, 2, 3}, 6 };
	b = { new int[6]{4, 2, 1, 0, 2, 4}, 6 };
	expected = { new int[11]{4, 3, 3, 3, 2, 1, 1, 3, 1, 4, 2}, 11 };
	actual = a * b;
	EXPECT_EQ(actual, expected);
	EXPECT_EQ(expected.power, 10);
	EXPECT_EQ(expected.len, 11);
}