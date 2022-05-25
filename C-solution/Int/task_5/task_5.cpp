#include <iostream>
#include <vector>
//#include "..\..\const.h"
using namespace std;

///факторизація числа

///Наївний алгоритм
vector<int> naive(int num){
    vector<int> result;
    int curNum = num;
    int probe = 2;
    
    while(curNum!=1){
        if(curNum%probe != 0){
            probe++;
        } else {
            curNum /= probe;
            result.push_back(probe);
        }
        
    }

    return result;
}

///Алгоритм Поларда
vector<int> pollard(int num){
    vector<int> result;
    int cur;
    
    while(num != 1){
        cur = pollardRho(num);
        result.push_back(cur);
        num = num/cur;
    }

    return result;
}

int customFunct(int param, int mod){
    return ((param * param + 1) % mod);
}

int pollardRho(int number){
     int a = 2, b = 2, tmp;
    while (true)
    {
        a = customFunct(a, number);
        b = customFunct(customFunct(b, number), number);
        tmp = gcd(abs(b - a), number);
        if (tmp > 1)
            break;
    }
    return tmp;
}



