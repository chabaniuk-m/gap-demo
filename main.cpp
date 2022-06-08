#include "C-solution/Polynom/Polynom.h"
#include "C-solution/const.h"
#include <iostream>

int mod;

int main()
{
    Polynom a,b;

    mod = 23;
    a = Polynom("6x+2");
    b = Polynom("2");

    (a/b).print();
}