#pragma once
#include "../task_4/task_4.cpp"
#include <time.h>

/*
Miller Rabin's primacy test
if n - probably primary - return TRUE
if n is compounded - return FALSE
the probability of error is 0.25 ^ t
int n is the number to check, int t is the confidence level
*/
bool MiillerRabinTest(int n, int t)
{
    srand(time(0));
    t = t >= 1 ? t : 1;
    //break the n-1 to the form r*2^s
    int r = n - 1;
    int s = 0;
    while(r%2 == 0)
    {
        r /= 2;
        s++;
    }
    for(int i = 0; i < t; i++)
    {
        //random item from [2, n-2]
        int a = rand()%(n-4) + 2;
        //calculate y = a^r mod n;
        int y = MontgPow(a, r, n);
        if(y != 1 && y != n-1)
        {
            for(int j = 0; j < s && y != n - 1; j++)
            {
                //calculate y = y^2 mod n;
                y = MontgPow(y, 2, n);
                if(y == 1)
                    return false;
            }
            if(y != n-1)
                return false;
        }  
    }
    return true;
}
