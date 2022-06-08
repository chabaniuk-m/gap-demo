#include <cmath>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>

int mod;

using namespace std;

namespace number 
{
  bool MillerRabinTest(int n, int t);
  int MontgPow(int a, int b, int mod = 13);
  bool is_co_prime(int a , int b);
  int pollardRho(int number);

  bool isPrime(int n) {
    return MillerRabinTest(n, 20);
    // Original way:
    /*
    if(n<2) return false;
    int sqrt = static_cast<int>(std::sqrt(n)) + 1;
    for(int i=2; i<=sqrt; i++)
    {
        if(n%i==0) return false;
    }
    return true;
    */
  }

  int recover(int n) {
    if (n >= 0)
      return n % mod;
    else 
      return mod - std::abs(n) % mod;
  }

  int** generateDivisionTable() {
    int** table = new int*[mod];
    for (int i = 0; i < mod; i++)
      table[i] = new int[mod];
    for (int i = 0; i < mod; i++) {
      table[0][i] = 0;  // 0/a = 0
      table[i][0] = -1; // a/0 = error(-1)
    }

    for (int i = 1; i < mod; i++) {
      for (int j = 1; j < mod; j++) {
        int res = (i * j) % mod;
        table[res][i] = j;
        table[res][j] = i;
      }
    }

    return table;
  }

  void deleteDivisionTable(int** table) {
    for(int i = 0; i < mod; i++)  
      delete [](table[i]);
      
    delete []table;
  }

  int mobius(int n) {
    if (n == 1)
      return 1;
    int p = 0;
    for (int i = 1; i <= n; i++) {
      if (n % i == 0 && isPrime(i)) {
        if (n % (i * i) == 0)
          return 0;
        else
          p++;
      }
    }
    return (p % 2 != 0) ? -1 : 1;
  }

//------------------------------------------------------------------------------
  // Task 10 - Authors = Havryluk & Shuplyakov
  /*
  Miller Rabin's primacy test
  if n - probably primary - return TRUE
  if n is compounded - return FALSE
  the probability of error is 0.25 ^ t
  int n is the number to check, int t is the confidence level
  */
  bool MillerRabinTest(int n, int t)
  {
    srand(time(0));
    if (n == 2)
      return true;
    if (n < 2 || n % 2 == 0)
      return false;
    if (t < 1)
      t = 1;
    // break the n-1 to the form r*2^s
    int r = n - 1;
    int s = 0;
    while(r % 2 == 0) {
      r /= 2;
      s++;
    }
    for (int i = 0; i < t; i++) {
      // random item from [2, n-2]
      int a = rand() % (n - 4) + 2;
      // calculate y = a^r mod n;
      int y = MontgPow(a, r, n);
      if (y != 1 && y != n - 1) {
        for (int j = 0; j < s && y != n - 1; j++) {
          // calculate y = y^2 mod n;
          y = MontgPow(y, 2, n);
          if(y == 1)
            return false;
        }
        if (y != n - 1)
          return false;
      }
    }
    return true;
  }

//------------------------------------------------------------------------------
  // Task 9 - Author = Polozhenets

  long long gcd(int a, int b) {
    while(b) {
      long long t = a % b;
      a = b;
      b = t;
    }
    return a;
  }

  long long Carmichael(long long n) {
    if (n < 1)
      return 0;
    if (n == 1)
      return 1;
    std::vector<long long> factors;
    for (long long i = 2; i * i <= n; i += 2) {
      long long w = 0;
      while (n % i == 0) {
        w++;
        n /= i;
      }
      if (i == 2 && w >= 3)
        factors.push_back((pow(i, w - 1) * (i - 1)) / 2);
      else if(i >= 2 && w > 0)
        factors.push_back(pow(i, w - 1) * (i - 1));
      if (i == 2)
        i--;
    }
    if (n != 1)
      factors.push_back(n - 1);
    
    long long res = 1;
    for (auto i : factors)
      res *= i / gcd(res, i);
    return res;
  }

  long Euler(long n)
  {
    long result = 1;
    for (int i = 2; i < n; i++) {
      if (gcd(i, n) == 1)
        result++;
    }
    return result;
  }

//------------------------------------------------------------------------------
  // Task 3 - Author = Rudenko & Poliakov

  // обернений елемент
  int inverted_element(int value) {
    int result = 0;
    if (is_co_prime(mod, value)) {
      for (int i = 0; i < mod; i++) {
        result = (value * i) % mod;
        if (result == 1)
          return i;
      }
    }

    // -1 - error
    return -1;
  }

  // перевірка чи mod і value взаємнопрості
  bool is_co_prime(int a , int b) {
    int hcf = 0;
    // найти найбільший спільний дільник
    for (int i = 1; i <= a; i++) {
      if (a % i == 0 && b % i == 0)
        hcf = i;
    }

    if (hcf == 1)
      return true;
    else
      return false;
  }

  // ділення чисел (a/b)
  int divide(int a, int b) {
    if (!number::isPrime(mod))
      return -1;
    return number::recover(a*inverted_element(b));
  }

//------------------------------------------------------------------------------
  // Task 4 - Author = Medvedchuk

  unsigned int bitLength(unsigned int n) {
    unsigned int count = 0;
    while (n) {
      count++;
      n >>= 1;
    }
    return count;
  }

  class Montgomery 
  {
  private:
    unsigned long long  mod;
    unsigned long long  rrm;
    int BLn;

    unsigned long long  reduce(Montgomery mont, unsigned long long  t) {
      unsigned long long  a = t;
      int i;

      for (i = 0; i < mont.BLn; i++) {
        if ((a & 1) == 1)
          a += mont.mod;
        a = a >> 1;
      }

      if (a >= mont.mod)
        a -= mont.mod;

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
    unsigned long long  MontPow(unsigned long long  x,
                                unsigned long long  pow,
                                unsigned long long  mod) {
      Montgomery M = Montg(mod);

      unsigned long long  p = reduce(M, M.rrm);
      unsigned long long  main = reduce(M, x * M.rrm);
      unsigned long long  exp = pow;
      while (bitLength(exp) > 0) {
        if ((exp & 1) == 1)
          p = reduce(M, p * main);

        exp >>= 1;
        main = reduce(M, main * main);
      }
      return reduce(M, p);
    }
  };

  int MontgPow(int a, int b, int mod) {
    Montgomery x{};
    return x.MontPow(a, b, mod);
  }

//------------------------------------------------------------------------------
  // Task 5 - Author = Kuharchuk

  /// Наївний алгоритм
  vector<int> naive(int num) {
    vector<int> result;
    int curNum = num;
    int probe = 2;
    
    while (curNum != 1) {
      if(curNum % probe != 0) {
        probe++;
      } else {
        curNum /= probe;
        result.push_back(probe);
      }
    }

    return result;
  }

  /// Алгоритм Поларда
  vector<int> pollard(int num) {
    vector<int> result;
    int cur;
    
    while(num != 1) {
      cur = pollardRho(num);
      result.push_back(cur);
      num = num / cur;
    }

    return result;
  }

  int customFunct (int param, int mod) {
    return ((param * param + 1) % mod);
  }

  int pollardRho (int number) {
    int a = 2, b = 2, tmp;
    while (true) {
      a = customFunct(a, number);
      b = customFunct(customFunct(b, number), number);
      tmp = number::gcd(abs(b - a), number);
      if (tmp > 1)
        break;
    }
    return tmp;
  }

//------------------------------------------------------------------------------
  // Task 8 - Author = Motrych 
  // вертає порядок елемента мультиплікативної групи
  // в іншому випадку вертає 0
  int elementOrder(int a, int mod) 
  {
    if (gcd(a, mod) != 1)
      return 0;

    int result=1;
    int K = 1;
    
    while (mod > K)
    {
      result = (result * a) % mod;

      if (result == K)
        return K;

      K = K + 1;
    }

    return 0;
  }
  // Other realisation - Author = Kilko
  int element_order(int a, int mod) {
    if (!is_co_prime(a, mod))
      return -1; // Error 

    vector<int> fact = naive(mod);
    for (int i = 0; i < fact.size(); i++) {
      int e = 1;
      for (int j = 0; j < fact[i]; j++) {
        e *= a;
        e %= mod;
      }
      if (e == 1)
        return fact[i];
    }

    return -1; // Not found
  }

  bool generator(int a, int mod) {
    if (!is_co_prime(a, mod))
      return false; // Error
  }
}


