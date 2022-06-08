#include "Polynom.h"
#include "..\const.h"
#include "..\Int\Int.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <map>
#include <vector>

/*
	* Парсить рядок pol у многочлен.
	* Вимоги до pol:
		* Одночлени формату ax^b, розділені знаком  "+", де a, b - коефіцієнт і степінь
		* Байдуже на пробіли
		* Одночлени степені 1 можуть бути у вигляді "ax^1" або "ax"
		* Одночлени степені 0 можуть бути у вигляді "ax^0" або "a"
		* Одночлени однакових степенів можуть повторюватись
		* Одночлени можна вводити в довільному порядку
	*
	* Examples:
	* 3x^2 + 7x^5 + 4 - ok
	* 2x^0 + 3x^1 + 4x^2 - ok
	* 3x^1 + 3x + 2x^0 + 2 - ok (буде 6x + 4)
	* 3x^3 + + 3x - не ок(зайвий плюс)
*/
Polynom::Polynom(std::string pol)
{
	std::map<int, int> values; // використовуємо map для збереження степені і коефіцієнту
	pol.erase(std::remove_if(pol.begin(), pol.end(), isspace), pol.end()); // видаляємо пробіли
	std::vector<std::string> monomials;

	int pos = 0;
	while ((pos = pol.find("+")) != std::string::npos) // розбиваємо на одночлени
	{
		monomials.push_back(pol.substr(0, pos));
		pol.erase(0, pos + 1);
	}
	monomials.push_back(pol.substr(0, pos));
	for (auto m : monomials)
	{
		int power_pos = m.find("^"), coef, power;
		if (power_pos != std::string::npos)
		{
			std::string coef_s = m.substr(0, power_pos - 1);
			std::string power_s = m.substr(power_pos + 1, std::string::npos);

			coef = std::stoi(coef_s);
			power = std::stoi(power_s);
		}
		else
		{
			int x_pos = m.find("x");
			std::string coef_s;
			if (x_pos != std::string::npos)
			{
				power = 1;
				coef_s = m.substr(0, m.size() - 1);
			}
			else
			{
				power = 0;
				coef_s = m.substr(0, m.size());
			}
			
			coef = std::stoi(coef_s);
		}
		// якщо такий степінь вже був - додаємо коефіцієнт, інакше створюємо нову пару
		if (values.count(power) == 0)
			values.insert(std::make_pair(power, coef));
		else
			values[power] += coef;
	}

	int max_power = (values.rbegin())->first; // get max key in map
	this->len = max_power + 1;
	this->power = max_power;
	coeff = new int[len];
	for (int i = 0; i < len; i++)
		coeff[i] = 0;
	for (auto value : values)
		coeff[value.first] = value.second % mod;	
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

Polynom gcd(const Polynom& lhs, const Polynom& rhs)
{
    Polynom x(lhs), y(rhs);
    while(y != Polynom())
    {
        Polynom r = x%y;
        x = y;
        y = r;
    }
    return x;
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
	result.len = result.power + 1;
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
	result.recover();
	return result;
}

Polynom operator-(const Polynom& lhs, const Polynom& rhs)
{
	Polynom result;
	result.power = std::max(lhs.power, rhs.power); // reserve max power
	result.len = result.power + 1;
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
	* Множимо лівий многочлен на правий у кільці, беручи коефіцієнти по модулю
	* Приклад: (2x^2 + x + 2)*(x^2+2x+1) = 2x^4 + x^2 + 2 (mod 5)
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
    if(!number::isPrime(mod) || rhs == Polynom())
        return {Polynom("-1"),Polynom("-1")};

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

Polynom operator / (const Polynom& lhs, const Polynom& rhs)
{
    return Polynom::division(lhs,rhs).first;
}

Polynom operator % (const Polynom& lhs, const Polynom& rhs)
{
    return Polynom::division(lhs,rhs).second;
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

Polynom cyclotomic(int n) {
    int m = n / 2;
    Polynom result(1);
    result.coeff[0] = 1;
    if (n % 2 == 0 && number::isPrime(m) && m % 2 != 0 && m != 1) {
        if (number::isPrime(m)) {
            int *keys = new int[m];
            for (int i = 0; i < m; i++) {
                if (i % 2 != 0)
                    keys[i] = -1;
                else
                    keys[i] = 1;
            }
            return Polynom(keys, m);
        }
        for (int i = 1; i <= m; i++) {
            if (m % i == 0 && number::mobius(m / i) == 1) {
                int *keys = new int[i + 1];
                if (i % 2 != 0)
                    keys[i] = -1;
                else
                    keys[i] = 1;
                keys[0] = -1;
                Polynom multiplier(keys, i + 1);
                result = result * multiplier;
            }
        }
        for (int i = 1; i <= m; i++) {
            if (m % i == 0 && number::mobius(m / i) == -1) {
                int *keys = new int[i + 1];
                keys[i] = 1;
                keys[0] = -1;
                Polynom divider(keys, i + 1);
                result = result / divider;
            }
        }
    }
    else {
        if (number::isPrime(n))
        {
            int *keys = new int[n];
            for (int i = 0; i < n; i++)
                keys[i] = 1;
            return Polynom(keys, n);
        }

        for (int i = 1; i <= n; i++) {
            if (n % i == 0 && number::mobius(n / i) == 1) {
                int *keys = new int[i + 1];
                keys[i] = 1;
                keys[0] = -1;
                Polynom multiplier(keys, n);
                result = result * multiplier;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (n % i == 0 && number::mobius(n / i) == -1) {
                int *keys = new int[i + 1];
                keys[i] = 1;
                keys[0] = -1;
                Polynom divider(keys, n);
                result = result / divider;
            }
        }
    }
    return result;
}

Polynom Polynom::derivative() {
    assert(number::isPrime(mod));
	Polynom result; //створюємо поліном, який буде результатом знаходження похідної
	/*
	  Встановлюємо значення степеня полінома-похідної
	   * якщо початковий поліном був числом, то степінь результуючого полінома = 0
	   * інакше присвоїти йому зменшений на одиницю степінь поточного полінома
	*/
	result.power = (this->power > 0) ? (this->power - 1) : this->power;
	result.len = result.power + 1;
	result.coeff = new int[result.len]; //створюємо масив коефіцієнтів при степенях змінної х
	int i = 0;
	if (result.power == 0) {
		//якщо шукаємо похідну від полінома-числа, то у комірку старшого степеня похідної
		//заносимо значення 0 і закінчуємо виконання функції.
		result.coeff[result.power] = 0;
		return result;
	}
	//переглядаємо коефіцієнти при відповідних степенях початкового полінома і 
	//обчислюємо нові при степенях похідних
	while (i < this->power) {
		result.coeff[i] = (this->coeff[i + 1] * (i + 1)) % mod;
		i++;
	}
	return result;
}
int Polynom::valueAtPoint(int point) {
	int result = 0;
	for (int i = 0; i < this->len; i++) {
		result += (this->coeff[i] * MontgPow(point, i, mod)) % mod;
	}
	result = result % mod;
	return result;
}
