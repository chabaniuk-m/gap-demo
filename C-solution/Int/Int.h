#pragma once

#include "..\const.h"
#include <string>

// Прототипи функцій, які були потрібні для інших задач (реалізації в task_*)
int MontgPow(int a, int b, int mod);
int inverted_element(int value);
int divide(int a, int b);

// Загальні функції з числами, які були потрібні для інших задач (реалізації в Int.cpp)
namespace number
{
    // найбільший спільний дільник
    // реалізація в task_9
    long long gcd(int a, int b);

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

    // знаходить квадратний корінь числа a за модулем n
    std::string square_root(int a, int n);

    int mobius(int n);
}