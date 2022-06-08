#include <iostream>
#include "..\..\const.h"
#include "..\Int.h"

using namespace std;
bool is_co_prime(int a, int b);
// головна функція  (обернений елемент)
int inverted_element(int value) {

    int result = 0;

	if (is_co_prime(mod, value)) {
		for (int i = 0; i < mod; i++) {

			result = (value * i) % mod;

			if (result == 1) {

				return i;

			}

		}
	}
	else {
		// -1 - error
		return -1;
	}
	
}
//перевірка чи mod і value взаємнопрості
bool is_co_prime(int a , int b) {
	int hcf = 0;
	//найти найбільший спільний дільник
	for (int i = 1; i <= a; i++)
	{
		if (a % i == 0 && b % i == 0)
		{
			hcf = i;
		}
	}

	if (hcf == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// головна функція  (ділення чисел)
// a/b
int divide(int a, int b) {
    if (!number::isPrime(mod))
        return -1;
    int** divTable = number::generateDivisionTable();
    a = number::recover(a);
    b = number::recover(b);
    int res = divTable[a][b];
    number::deleteDivisionTable(divTable);
    return res;
}