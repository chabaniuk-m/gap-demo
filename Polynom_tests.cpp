#include "gtest/gtest.h"
#include "C-solution/Polynom/Polynom.h"
#include "C-solution/const.h"

int mod;

TEST(Polynom, division)
{
    Polynom a, b;
    std::pair<Polynom,Polynom> res;

    mod = 5;
    a = {new int[5]{2,0,1,3,4},5};
    b = {new int[3]{1,3,3},3};
    res = {Polynom(new int[3]{3,3,3},3), Polynom(new int[2]{4,3},2)};
    EXPECT_EQ(Polynom::division(a,b), res);

    mod = 3;
    a = {new int[5]{2,0,1,3,0},5};
    b = {new int[3]{1,0,3},3};
    res = {Polynom(new int[3]{2,0,1},3), Polynom()};
    EXPECT_EQ(Polynom::division(a,b), res);

    mod = 7;
    a = {new int[7]{6,0,1,3,6,0,0},7};
    b = {new int[6]{3,1,3,0,5,0},6};
    res = {Polynom(new int[1]{4},1), Polynom(new int[4]{1,3,3,3},4)};
    EXPECT_EQ(Polynom::division(a,b), res);
}