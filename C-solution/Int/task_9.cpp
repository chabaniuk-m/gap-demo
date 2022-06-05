#include <iostream>
#include <vector>


long long gcd(int a, int b) {
  while(b){
    long long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

long long Carmichael(long long n){
  if (n < 1) return 0;
  if (n == 1) return 1;
  std::vector<long long> factors;
  for(long long i = 2; i*i <= n; i += 2){
    long long w = 0;
    while(n % i == 0){
      w++;
      n /= i;
    }
    if (i == 2 && w >= 3)
      factors.push_back((pow(i, w-1) * (i-1))/2);
    else if(i >= 2 && w > 0)
      factors.push_back(pow(i, w-1) * (i-1));
    if(i == 2) i--;
  }
  if(n != 1) factors.push_back(n-1);
  
  long long res = 1;
    for(auto i : factors)
  res *= i/gcd(res, i);
    return res;
}

long Euler(long n)
{
    long result = 1;
    for (int i = 2; i < n; i++)
        if (gcd(i, n) == 1)
            result++;
    return result;
}