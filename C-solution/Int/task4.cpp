#include <iostream>

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
              std::cout<<("Mod should be more than zero and odd");
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


int MontgPow(int a,int b, int mod=13) {
    Montgomery x{};
     return x.MontPow(a, b, mod);
}
