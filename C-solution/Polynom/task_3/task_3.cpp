#include <iostream>
using namespace std;

class Polynomial {

private:
    int const mod = 45;

public:
    int inverted_element(int value) {

        int modul = mod;

        int result = 0;

        for (int i = 0; i < modul; i++) {

            result = (value * i) % modul;

            if (result == 1) {

                return i;

            }

        }

    }

};