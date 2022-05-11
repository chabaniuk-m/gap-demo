#include <iostream>
#include "..\..\const.h"

using namespace std;

int inverted_element(int value) {

    int result = 0;


    for (int i = 0; i < mod; i++) {

        result = (value * i) % mod;

        if (result == 1) {

            return i;

        }

    }

}