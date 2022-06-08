#include "gtest/gtest.h"
#include "../C-solution/Int/Int.h"
#include "../C-solution/const.h"

TEST(Int, inverted_element)
{
    int a;
    int res;

    a = 5;
    mod = 23;
    res = 14;
    EXPECT_EQ(inverted_element(a), res);

    a = 6;
    mod = 29;
    res = 5;
    EXPECT_EQ(inverted_element(a), res);

    a = 478;
    mod = 657;
    res = 334;
    EXPECT_EQ(inverted_element(a), res);

    a = 478;
    mod = 888;
    res = -1;
    EXPECT_EQ(inverted_element(a), res);

    a = 4785;
    mod = 10061;
    res = 8934;
    EXPECT_EQ(inverted_element(a), res);

    a = 9875;
    mod = 10039;
    res = 4591;
    EXPECT_EQ(inverted_element(a), res);
}

TEST(Int, divide)
{
    int a, b;
    int res;

    a = 7;
    b = 2;
    mod = 13;
    res = 10;
    EXPECT_EQ(divide(a,b), res);

    a = 7784;
    b = 2154;
    mod = 10039;
    res = 6398;
    EXPECT_EQ(divide(a,b), res);

    a = 1;
    b = 1;
    mod = 10039;
    res = 1;
    EXPECT_EQ(divide(a,b), res);

    a = 8934;
    b = 4785;
    mod = 10061;
    res = 2443;
    EXPECT_EQ(divide(a,b), res);
}