#include "Polynom.h"
#include "const.h"
#include <iostream>

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
	// створюємо "1" якщо викликали пустий конструктор
	coeff = new int[1]{ 1 };
	len = 1;
	power = 0;
}

void Polynom::print()
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

Polynom::~Polynom()
{
	
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
	// remove zeroes
	// якби coeff був vector, можна було б зробити просто через pop_back()
	// 1 + 2x + 0x^2 + 3x^3 + 0x^4 +0x^5 power = 5, k = 3
	int k = result.power;
	while (result.coeff[k] == 0 && k >= 0)
	{
		k--;
	}
	if (k != result.power) // якщо є нулі в старших коефіцієнтах
	{
		int* temp = new int[k];
		for (int l = 0; l < k; l++)
			temp[l] = result.coeff[l];
		delete[] result.coeff;
		result.coeff = temp;
	}

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
	for (int i = 0; i < result.len; i++)
	{
		result.coeff[i] = result.coeff[i] % mod;
	}

	return result;
}

bool operator==(const Polynom& lhs, const Polynom& rhs)
{
	if (lhs.power != rhs.power)
		return false;

	for (int i = 0; i <= rhs.power; i++)
	{
		if (rhs.coeff[i] != lhs.coeff[i])
			return false;
	}

	return true;
}

bool operator!=(const Polynom& lhs, const Polynom& rhs)
{
	return !(lhs == rhs);
}
