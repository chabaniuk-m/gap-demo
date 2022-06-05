#include "gtest/gtest.h"
#include "../C-solution/Polynom/Polynom.h"
#include "../C-solution/Polynom/task_17.cpp"
#include "../C-solution/const.h"

TEST(Task17, PolynomialIrreducibility)
{
    Polynom a = {new int[5]{4, 7, 21, 28},4};
    Polynom b = {new int[4]{3, 15, 10},3};
    Polynom c = {new int[5]{6, 7, 2, 8},4};
    Polynom d = {new int[5]{34, 14, 1, 8, 22},5};
    Polynom e = {new int[5]{2, 1},2};

    EXPECT_EQ(check_for_irreducibility(a, 4), true);
    EXPECT_EQ(check_for_irreducibility(b, 4), false);
    EXPECT_EQ(check_for_irreducibility(c, 4), false);
    EXPECT_EQ(check_for_irreducibility(d, 4), false);
    EXPECT_EQ(check_for_irreducibility(e, 4), false);
}