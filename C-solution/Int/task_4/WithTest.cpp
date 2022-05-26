#include <iostream>
#include <cassert>

int bitLength(int n) {
    int result = 0;
    while (n > 0) {
        n >>= 1;
        result++;
    }
    return result;
}


class Montgomery {
private: int mod, rrm, bLn;
       Montgomery MontgF(int mod) {
           Montgomery result;

           if (mod == 0 || (mod & 1) == 0) {
               std::cout << ("Mod should be more than zero and odd");
               exit(1);
           }

           result.mod = mod;
           result.bLn = bitLength(mod);
           result.rrm = (1 << (result.bLn * 2)) % mod;

           return result;
       }

       int reduce(Montgomery Montg, int t) {
           int a = t;
           for (int i = 0; i < Montg.bLn; i++) {
               if ((a & 1) == 1) {
                   a += Montg.mod;
               }
               a = a >> 1;
           }

           if (a >= Montg.mod) {
               a -= Montg.mod;
           }
           return a;
       }

public:int MontPow(int x, int pow, int mod) {
    Montgomery Montg = MontgF(mod);

    int p = reduce(Montg, Montg.rrm);
    int main = reduce(Montg, x * Montg.rrm);
    int exp = pow;
    while (bitLength(exp) > 0) {
        if ((exp & 1) == 1) {
            p = reduce(Montg, p * main);
        }
        exp >>= 1;
        main = reduce(Montg, main * main);
    }
    return reduce(Montg, p);

}

};


int MontgPow(int a, int b, int mod = 13) {
    Montgomery x{};
    return x.MontPow(a, b, mod);
}

void Test() {
    assert(MontgPow(2,4,13)==3);
    assert(MontgPow(2, 4) == 3);
    assert(MontgPow(5, 2) == 12);
    assert(MontgPow(5, 2, 51) == 25);
    assert(MontgPow(8, 9) == 8);
    assert(MontgPow(8, 9,17) == 8);
    std::cout << "Tests successful!\n";
}

int main() {
    char m;
    std::cout << "To run tests write: T/t.\nTo try it yourself write: M/m.\n";
    std::cin >> m;
    if (m == 'T' || m == 't') {
        Test();
    }
    else if(m=='M' || m=='m') {
        int a, b,mod ;

        std::cout << "Enter base: ";
        std::cin >> a;
        std::cout << "Enter pow: ";
        std::cin >> b;
        std::cout << "Enter mod, but mod must be greater than zero and not even : ";
        std::cin >> mod;
        std::cout << MontgPow(a, b, mod);

    }
    
    return 0;
}