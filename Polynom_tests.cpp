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