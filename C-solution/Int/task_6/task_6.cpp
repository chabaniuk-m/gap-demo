#include <string>

///////////////////////////////////////////////////////////////////////////////
// Using algorithms from                                                     //
// " Handbook of applied cryptography (Menezes, Alfred J. Vanstone etc.) "   //
///////////////////////////////////////////////////////////////////////////////

#include "..\Int.h"

// перевірка чи є число простим
bool is_prime(int n);

// Jacobi symbol (and Legendre symbol) computation
int jacobi(int a, int n, int s = 0);

// extended Euclidean algorithm(Algorithm 2.142)
int euclidean(int a, int n);

// ГОЛОВНА ФУНКЦІЯ
// а - число
// n - модуль
// результат - рядок з двома числами, наприклад 8, -8
std::string number::square_root(int a, int n) {

	std::string ERROR = "There is no square root";

	if (n < 2) {
		return "Module n must be greater then 1 (n > 1)";
	}
	else if (n == 2) {
		return "1, -1";
	}
	else if (a < n) {
		int r = int(sqrt(a));
		if (a == r * r)
			return std::to_string(r).append(", ").append(std::to_string(-r));
		else
			return ERROR;
	}

	// Якщо n - просте число,
	// яке менше за а
	if (n > 2 && is_prime(n)) {
		
		// 1. Compute the Legendre symbol using Algorithm 2.149
		int lengedre_symbol = jacobi(a, n);

		if (lengedre_symbol == -1) {
			
			return ERROR;
		}

		// 2. Select integers b, 1 ≤ b ≤ n − 1, at random until one is found with 
		//    Legendre symbol for b & n = -1
		int b;
		for (b = 1; b < n; ++b) {
			if (jacobi(b, n) == -1)
				break;
		}

		// 3. By repeated division by 2, write n − 1 = 2^s * t, where t is odd
		int s = 0;
		int t = n - 1;

		while (t % 2 == 0) {
			t = t / 2;
			++s;
		}

		// 4. Compute a^(-1) mod p by the extended Euclidean algorithm (Algorithm 2.142)
		int a_inverted = euclidean(a, n);

		if (a_inverted == -1) {
			return ERROR;
		}

		// 5. Set c ← bt mod n and r ← a^(t+1) / 2 mod n (Algorithm 2.143)

		int c = (b * t) % n;

		int a_pow_t_plus_1 = 1;
		for (int i = 0; i < t + 1; ++i) {
			a_pow_t_plus_1 = a_pow_t_plus_1 * a;
		}

		int r = int(a_pow_t_plus_1 / 2) % n;

		// 6. For i from 1 to s − 1 do the following:
			// 6.1 Compute d = (r2 · a^(-1))^2^(s−i−1) mod n.
			// 6.2 If d ≡ −1 (mod n) then set r←r · c mod n.
			// 6.3 Set c ← c^2 mod n.

		for (int i = 1; i <= s - 1; ++i) {

			int d = int(pow(r * r * a_inverted, pow(2, s - i - 1))) % n;

			if (d % n == -1) {
				r = (r * c) % n;
			}

			c = (c * c) % n;
		}

		return std::to_string(r).append(", ").append(std::to_string(-r));
	}

	// TODO: solve case when n is a composite number
	// algorithm on page 101 of "C:\Users\Admin\Desktop\education\ЗА\Handbook of applied cryptography (Menezes, Alfred J. Vanstone etc.) (z-lib.org).pdf"

	return "Algorithm doesn't yet work if module is a composite number";
}