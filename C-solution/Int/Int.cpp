#include "Int.h"
#include <cmath>

bool isPrime(int n)
{
    int sqrt = static_cast<int>(std::sqrt(n)) + 1;
    for(int i=2; i<=sqrt; i++)
    {
        if(n%i==0) return false;
    }
    return true;
}

int** generateDivisionTable(int size)
{

}