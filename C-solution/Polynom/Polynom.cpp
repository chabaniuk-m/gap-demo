#include "Polynom.h"
#include "..\const.h"
#include "..\Int\Int.h"
#include <iostream>
#include <cassert>

Polynom::Polynom(std::string pol)
{
	// TO DO - parse from string	
}

Polynom::Polynom(int* coeff, int len)
{
	//this->coeff = new int[len];
	this->coeff = coeff;

	this->len = len;
	this->power = len - 1;
}

Polynom::Polynom(int length)
{
	coeff = new int[length];
	this->len = length;
	this->power = length - 1;

	for (int i = 0; i < length; i++)
		coeff[i] = 0;
}

Polynom::Polynom()
{
	// створюємо "0" якщо викликали пустий конструктор
	coeff = new int[1]{ 0 };
	len = 1;
	power = 0;
}

Polynom::Polynom(const Polynom& toCopy)
{
    this->len = toCopy.len;
    this->power = len - 1;
    coeff = new int[len];

    for (int i = 0; i < len; i++)
        coeff[i] = toCopy.coeff[i];
}

void Polynom::print() const
{
	for (int i = 0; i <= power; i++)
	{
		if (coeff[power - i] != 0)
		{
			if (coeff[power - i] != 1 && i != power)
			{
				std::cout << coeff[power - i] << "x^" << power - i;
			}
			else
			{
				if (i != power)
					std::cout << "x^" << power - i;
				else
				{
					std::cout << coeff[power - i];
				}
			}
			if (i < power)
				std::cout << " + ";
		}
	}
	std::cout << "\n";
}

void Polynom::recover()
{
    // remove zeroes
    // якби coeff був vector, можна було б зробити просто через pop_back()
    // 1 + 2x + 0x^2 + 3x^3 + 0x^4 +0x^5 power = 5, k = 3
    for (int l = 0; l <= power; l++)
    {
        coeff[l] = number::recover(coeff[l]);
    }

    int newPower = power;
    while (coeff[newPower] == 0 && newPower > 0)
    {
        newPower--;
    }
    if (newPower != power) // якщо є нулі в старших коефіцієнтах
    {
        int* temp = new int[newPower+1];
        for (int l = 0; l <= newPower; l++)
            temp[l] = coeff[l];
        delete[] coeff;

        coeff = temp;
        power = newPower;
        len = newPower+1;
    }
}

Polynom::~Polynom()
{
    delete []coeff;
}

Polynom& Polynom::operator = (const Polynom& toCopy)
{
    if(this == &toCopy)
        return *this;
    delete []coeff;

    this->len = toCopy.len;
    this->power = len - 1;
    coeff = new int[len];

    for (int i = 0; i < len; i++)
        coeff[i] = toCopy.coeff[i];

    return *this;
}

Polynom operator+(const Polynom& lhs, const Polynom& rhs)
{
	Polynom result;
	result.power = std::max(lhs.power, rhs.power);
	result.coeff = new int[result.power + 1];
	int i = 0, j = 0;
	while (i <= lhs.power && j <= rhs.power)
	{
		result.coeff[i] = (lhs.coeff[i] + rhs.coeff[j]) % mod;
		i++;
		j++;
	}
	while (i <= lhs.power)
	{
		result.coeff[i] = lhs.coeff[i];
		i++;
	}
	while (j <= rhs.power)
	{
		result.coeff[j] = rhs.coeff[j];
		j++;
	}

	return result;
}

Polynom operator-(const Polynom& lhs, const Polynom& rhs)
{
	Polynom result;
	result.power = std::max(lhs.power, rhs.power); // reserve max power
	result.coeff = new int[result.power + 1];
	int i = 0, j = 0;
	while (i <= lhs.power && j <= rhs.power)
	{
		int coefficient = lhs.coeff[i] - rhs.coeff[j];
		if (coefficient < 0)
			coefficient += mod;

		result.coeff[i] = coefficient;
		i++;
		j++;
	}
	while (i <= lhs.power)
	{
		result.coeff[i] = lhs.coeff[i];
		i++;
	}
	while (j <= rhs.power)
	{
		result.coeff[j] = rhs.coeff[j];
		j++;
	}
    result.recover();
	return result;
}

Polynom operator*(const Polynom& lhs, const Polynom& rhs)
{
	/*
	* Спочатку множимо лівий многочлен на правий, після
	* цього результат ділимо на лівий многочлен і повертаємо остачу
	* Приклад: (2x^2 + x + 2)*(x^2+2x+1) = 2x^4 + x^2 + 2 (mod 5)
	* Ділимо 2x^4 + x^2 + 2 на 2x^2 + x + 2 і повертаємо остачу (не реалізовано)
	*/
	Polynom result(lhs.power + rhs.power + 1);
	for (int i = 0; i <= lhs.power; i++)
	{
		for (int j = 0; j <= rhs.power; j++)
		{
			result.coeff[result.power - (i + j)] += (lhs.coeff[lhs.power - i] * rhs.coeff[rhs.power - j]);
		}
	}
	result.recover();

	return result;
}

std::pair<Polynom,Polynom> Polynom::division(const Polynom& lhs, const Polynom& rhs)
{
    /*
     * Вважається, що:
     * - mod - просте число (!Обов'язкова умова для кільця многочленів!)
    */
    assert(number::isPrime(mod));
    assert(rhs != Polynom());

    Polynom lhsC(lhs), rhsC(rhs);
    lhsC.recover();
    rhsC.recover();

    int currQuotientPower = lhsC.power - rhsC.power;
    int currRemainderPower = lhsC.power;
    int** divTable = number::generateDivisionTable();

    Polynom quotient(currQuotientPower+1);
    Polynom remainder = lhsC;

    for(int i=lhsC.power; remainder!=Polynom() && currRemainderPower>=rhsC.power; i--, currQuotientPower--, currRemainderPower--)
    {
        if(remainder.coeff[i]==0)
        {
            quotient.coeff[currQuotientPower] = 0;
            continue;
        }

        int newCoeff = divTable[remainder.coeff[i]][rhsC.coeff[rhsC.power]];
        quotient.coeff[currQuotientPower] = newCoeff;

        for(int j=i; j>=currQuotientPower; j--)
        {
            remainder.coeff[j] = remainder.coeff[j] - number::recover(newCoeff * rhsC.coeff[rhsC.power - (i - j)]);
            remainder.coeff[j] = number::recover(remainder.coeff[j]);
        }
    }
    number::deleteDivisionTable(divTable);

    quotient.recover();
    remainder.recover();

    return {quotient, remainder};
}

bool operator==(const Polynom& lhs, const Polynom& rhs)
{
	for (int i = 0; i <= std::min(lhs.power, rhs.power); i++)
	{
		if (rhs.coeff[i] != lhs.coeff[i])
			return false;
	}
    if(lhs.power == rhs.power)
        return true;

    const Polynom* longer = lhs.power>rhs.power ? &lhs : &rhs;
    const Polynom* shorter = lhs.power>rhs.power ? &rhs : &lhs;
    for(int i = shorter->power+1; i <= longer->power; i++)
    {
        if(longer->coeff[i] != 0)
            return false;
    }
	return true;
}

bool operator!=(const Polynom& lhs, const Polynom& rhs)
{
	return !(lhs == rhs);
}
