#pragma once

#include "..\const.h"

/*
 * Функції з числами, які були потрібні для поліномів.
 * Вирішив покласти їх сюди поки що.
 * #start
*/

// перевірка числа на простоту
bool isPrime(int n);

/*
 * Нормалізувати число в полі
 * 8 (mod=5) => 3
 * 0 (mod=5) => 0
 * -8 (mod=5) => 2
*/
int normalize(int n);

// створює таблицю для виконання ділення чисел в полі
/*
 * Usage:
 * int** myTable = generateDivisionTable();
 * ...(a/b = myTable[a][b])...
 * deleteDivisionTable(myTable);
 */
int** generateDivisionTable();
void deleteDivisionTable(int** table);

// #end