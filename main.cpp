#include "C-solution/Polynom/Polynom.h"
#include "C-solution/const.h"
#include <iostream>

int mod;

int main()
{
    Polynom a,b, res;
    std::string p1, p2;


    /*
    while(true)
    {
        std::cout<<"Modulus: ";
        std::cin>>mod;
        std::cout<<"Polynomial 1: ";
        std::cin>>p1;
        a = Polynom(p1);
        std::cout<<"Polynomial 2: ";
        std::cin>>p2;
        b = Polynom(p2);

        std::cout<<"a/b = ";
        res = a/b;
        res.print();
        std::cout<<std::endl;

        std::cout<<"a%b = ";
        res = a%b;
        res.print();
        std::cout<<std::endl;
    }
     */


    while(true)
    {
        std::cout<<"Modulus: ";
        std::cin>>mod;
        std::cout<<"Polynomial 1: ";
        std::cin>>p1;
        a = Polynom(p1);
        std::cout<<"Polynomial 2: ";
        std::cin>>p2;
        b = Polynom(p2);

        std::cout<<"GCD(a,b) = ";
        res = gcd(a,b);
        res.print();
        std::cout<<std::endl;
    }

}