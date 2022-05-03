#pragma once

#include <string>

/*
* Клас Polynom
* Реалізовано - додавання, віднімання
* Коефіцієнти зберігаються у зростаючому порядку
* 
* TO DO - множення поліномів, parse from string
*/
class Polynom {
    static std::pair<Polynom,Polynom> division(const Polynom& lhs, const Polynom& rhs); //<Quotient,Remainder> (used for operators / and %)
public:
    int len; // polynom length
    int power; // polynom power
    int* coeff; // coefficients in ascending order
    // 1*x^6+1*x^3+18*x^1+7*x^0
    explicit Polynom(std::string pol); // initialize polynom from string
    Polynom(int* coeff, int len); // initialize polynom from array
    explicit Polynom(int length); // initialize polynom of length len with empty coefficients
    Polynom(); // initialize empty polynom
    Polynom(const Polynom& toCopy); // copy constructor
    void print() const; // prints polynom to console
    // operator overloading
    friend Polynom operator + (const Polynom& lhs, const Polynom& rhs);
    friend Polynom operator - (const Polynom& lhs, const Polynom& rhs);
    friend Polynom operator * (const Polynom& lhs, const Polynom& rhs);
    //friend Polynom operator / (const Polynom& lhs, const Polynom& rhs); -- not implemented yet
    //friend Polynom operator % (const Polynom& lhs, const Polynom& rhs); -- not implemented yet
    friend bool operator == (const Polynom& lhs, const Polynom& rhs);
    friend bool operator != (const Polynom& lhs, const Polynom& rhs);
    //friend Polynom gcd (const Polynom& lhs, const Polynom& rhs); //greatest common divisor --  not implemented yet
    ~Polynom();
};