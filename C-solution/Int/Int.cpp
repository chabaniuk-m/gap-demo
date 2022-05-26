#include "Int.h"
#include <cmath>

bool number::isPrime(int n)
{
    if(n<2) return false;
    int sqrt = static_cast<int>(std::sqrt(n)) + 1;
    for(int i=2; i<=sqrt; i++)
    {
        if(n%i==0) return false;
    }
    return true;
}

int number::recover(int n)
{
    return n>=0 ? n%mod : (mod-std::abs(n)%mod);
}

int** number::generateDivisionTable()
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

void number::deleteDivisionTable(int** table)
{
    for(int i=0; i<mod; i++)  delete [](table[i]);
    delete []table;
}

int number::mobius(int n) {
    if (n == 1)
        return 1;
    int p = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && number::isPrime(i)) {
            if (n % (i * i) == 0)
                return 0;
            else
                p++;
        }
    }
    return (p % 2 != 0) ? -1 : 1;
}