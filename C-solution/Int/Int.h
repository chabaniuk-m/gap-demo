#pragma once

#include "..\const.h"

/*
 * Функції з числами, які були потрібні для поліномів.
 * Вирішив покласти їх сюди поки що.
 * #start
*/

// перевірка числа на простоту
bool isPrime(int n);

// створює таблицю для виконання ділення чисел в кільці (і полі?)
/*
 * Usage:
 * int** myTable = generateDivisionTable();
 * ...(a/b = myTable[a][b])...
 * deleteDivisionTable(myTable);
 */
int** generateDivisionTable();
void deleteDivisionTable(int** table);

// #end