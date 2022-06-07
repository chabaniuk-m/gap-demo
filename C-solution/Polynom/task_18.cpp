#include <iostream>
#include "Polynom.h"
using namespace std;


int addModular(int a, int b, int mod)
{
    return (a + b) % mod;
}

int subtractModular(int a, int b, int mod)
{
    return (a + (mod - b)) % mod;
}

int multiplyModular(int a, int b, int mod)
{
    return (a * b) % mod;
}

// Determines degree of a polynomial
int polynomialDegree(Polynom poly)
{
    for (int i=poly.len-1; i>=0; i--)
    {
        if (poly.coeff[i]) return i;
    }

    return -1;
}

void polynomialAdd(Polynom A, Polynom B, int modulus) // S = A + B
{
    Polynom S;
    int maxlen = (A.len>B.len) ? A.len : B.len;
    int minlen = (A.len<B.len) ? A.len : B.len;

    // do the summation
    for (int i=0; i<minlen; i++)
    {
        S.coeff[i] = addModular(A.coeff[i], B.coeff[i], modulus);
    }

    for (int i=minlen; i<maxlen; i++)
    {
        if (maxlen==A.len)
            S.coeff[i] = A.coeff[i];
        else
            S.coeff[i] = B.coeff[i];
    }
}

void polynomialSubtract(Polynom A, Polynom B, int modulus) // D = A - B
{
    Polynom D;
    int maxlen = (A.len>B.len) ? A.len : B.len;
    int minlen = (A.len<B.len) ? A.len : B.len;

    // do the subtraction
    for (int i=0; i<minlen; i++)
    {
        D.coeff[i] = subtractModular(A.coeff[i], B.coeff[i], modulus);
    }

    for (int i=minlen; i<maxlen; i++)
    {
        if (maxlen == A.len)
            D.coeff[i] = A.coeff[i];
        else
            D.coeff[i] = ( (B.coeff[i]>0) ? (modulus - B.coeff[i]) : 0);
    }
}

void polynomialMultiply(Polynom A, Polynom B, int modulus) //P = A * B
{
    Polynom P;
    // get the degree of multiplicands
    int Adeg = polynomialDegree(A);
    int Bdeg = polynomialDegree(B);

    for (int i=0; i<=Adeg + Bdeg; i++)
    {
        for (int j=0; j<=i; j++)
        {
            if ( (i-j <= Bdeg) && (j <= Adeg) )
            {
                int temp = multiplyModular(A.coeff[j], B.coeff[i-j], modulus);
                P.coeff[i] = addModular(P.coeff[i], temp, modulus);
            }
        }
    }
}
