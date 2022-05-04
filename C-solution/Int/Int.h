#pragma once

#include "..\const.h"

/*
 * Функції з числами, які були потрібні для поліномів.
 * Вирішив покласти їх сюди поки що.
 * #start
*/

namespace number
{
    // Перевірка числа на простоту
    bool isPrime(int n);

    /*
     * Відновлює число в полі
     * 8 (mod=5) => 3
     * 0 (mod=5) => 0
     * -8 (mod=5) => 2
    */
    int recover(int n);

    // Створює таблицю для виконання ділення чисел в полі
    /*
     * Usage:
     * int** myTable = generateDivisionTable();
     * ...(a/b = myTable[a][b])...
     * deleteDivisionTable(myTable);
     */
    int** generateDivisionTable();
    void deleteDivisionTable(int** table);
}
// #end