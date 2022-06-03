#include <iostream>
#include <cassert>


const int BASE = 2;


unsigned int bitLength(unsigned int n)
{
    unsigned int count = 0;
    while (n)
    {
        count++;
        n >>= 1;
    }
    return count;
}

class Montgomery {
private:
    unsigned long long  mod;
    unsigned long long  rrm;
    int BLn;

    unsigned long long  reduce(Montgomery mont, unsigned long long  t) {
        unsigned long long  a = t;
        int i;

        for (i = 0; i < mont.BLn; i++) {
            if ((a & 1) == 1) {
                a += mont.mod;
            }
            a = a >> 1;
        }

        if (a >= mont.mod) {
            a -= mont.mod;
        }
        return a;
    }

    Montgomery Montg(unsigned long long  mod) {
        Montgomery res;

        if (mod == 0 || (mod & 1) == 0) {
            std::cout << ("Mod should be more than zero and odd");
            exit(1);
        }

        res.mod = mod;
        res.BLn = bitLength(mod);
        res.rrm = (1ULL << (res.BLn * 2)) % mod;

        return res;

    }
public:
    unsigned long long  MontPow(unsigned long long  x, unsigned long long  pow, unsigned long long  mod) {
        Montgomery M = Montg(mod);

        unsigned long long  p = reduce(M, M.rrm);
        unsigned long long  main = reduce(M, x * M.rrm);
        unsigned long long  exp = pow;
        while (bitLength(exp) > 0) {
            if ((exp & 1) == 1) {
                p = reduce(M, p * main);
            }
            exp >>= 1;
            main = reduce(M, main * main);
        }
        return reduce(M, p);
    }
  
};



int MontgPow(int a, int b, int mod = 13) {
    Montgomery x{};
    return x.MontPow(a, b, mod);
}

void Test() {
    assert(MontgPow(2, 4, 13) == 3);
    assert(MontgPow(2, 4) == 3);
    assert(MontgPow(5, 2) == 12);
    assert(MontgPow(5, 2, 51) == 25);
    assert(MontgPow(8, 9) == 8);
    assert(MontgPow(8, 9, 17) == 8);
    assert(MontgPow(18201, 2, 77681) == 44617);
    std::cout << "Tests successful!\n";
}

int main() {
    char m;
    std::cout << "To run tests write: T/t.\nTo try it yourself write: M/m.\n";
    std::cin >> m;
    if (m == 'T' || m == 't') {
        Test();
    }
    else if (m == 'M' || m == 'm') {
        int a, b, mod;

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