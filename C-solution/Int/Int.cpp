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

int recover(int n)
{
    return n>=0 ? n%mod : (mod-std::abs(n)%mod);
}

int** generateDivisionTable()
{
    int** table = new int*[mod];
    for(int i=0; i<mod; i++) table[i] = new int[mod];
    for(int i=0; i<mod; i++)
    {
        table[0][i] = 0;  // 0/a = 0
        table[i][0] = -1; // a/0 = error(-1)
    }

    for (int i=1; i<mod; i++)
    {
        for (int j=1; j<mod; j++)
        {
            int res = (i*j) % mod;
            table[res][i] = j;
            table[res][j] = i;
        }
    }

    return table;
}

void deleteDivisionTable(int** table)
{
    for(int i=0; i<mod; i++)  delete [](table[i]);
    delete []table;
}