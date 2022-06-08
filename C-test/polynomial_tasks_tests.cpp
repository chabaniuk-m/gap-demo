#include "gtest/gtest.h"
#include "../C-solution/Polynom/Polynom.h"
#include "../C-solution/Polynom/task_17.cpp"
#include "../C-solution/const.h"

TEST(Task17, EisensteinCriterion)
{
    Polynom a = {new int[4]{4, 7, 21, 28},4};
    Polynom b = {new int[3]{3, 15, 10},3};
    Polynom c = {new int[4]{6, 7, 2, 8},4};
    Polynom d = {new int[5]{34, 14, 1, 8, 22},5};
    Polynom e = {new int[3]{1, 1, 1},3};
    Polynom g = {new int[3]{-1, -1, -1},3};

    EXPECT_EQ(check_for_irreducibility(a), true);
    EXPECT_EQ(check_for_irreducibility(b), false);
    EXPECT_EQ(check_for_irreducibility(c), false);
    EXPECT_EQ(check_for_irreducibility(d), false);
    EXPECT_EQ(check_for_irreducibility(e), false);

    //Important example, polynomial x^2 + 1 is irreducible, but does not
    //fulfil the Eisenstein criterion, since no prime number divides 1
    Polynom f = {new int[2]{1, 1},2};
    EXPECT_EQ(check_for_irreducibility(f), false);
}