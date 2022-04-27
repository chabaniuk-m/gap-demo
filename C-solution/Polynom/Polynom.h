#ifndef POLYNOM_H
#define POLYNOM_H

#include <string>


class Polynom {
    int len;
    int* coeff;

public:
    // 1*x^6+1*x^3+18*x^1+7*x^0
    Polynom(std::string pol);

    ~Polynom();
};

#endif
