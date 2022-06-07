/**
 * @author Vladyslav Shupliakov
 *
 * Task 17: Check whether the polynomial is irreducible.
 */

#include <vector>
#include "Polynom.h"

using namespace std;

/**
 *  Get all the primes that are less than a value,
 *  passed as the parameter.
 *
 * @param M maximum number constraint
 * @return vector of all primes less than value
 *         passed as the parameter
 */
vector<int> sieve_of_eratosthenes_primes(const int M)
{
    bool* isPrime = new bool[M + 1];
    memset(isPrime, true, sizeof(*isPrime));
    for (int p = 2; p * p <= M; p++) {
        if (isPrime[p]) {
            for (int i = p * p;
                 i <= M; i += p) {
                isPrime[i] = false;
            }
        }
    }
    vector<int> prime;
    for (int i = 2; i <= M; i++) {
        if (isPrime[i]) {
            prime.push_back(i);
        }
    }

    delete []isPrime;
    return prime;
}

/**
 * Checks the polynomial for three Eisenstein's irreducibility
 * criterion.
 *
 * @param coefficients array of polynomial coefficients
 * @param prime        passed prime number
 * @param length       length of a polynomial
 * @return true if the conditions are satisfied
 *         false - otherwise
 */
bool check_eisenstein_criterion(const int coefficients[], int prime, int length)
{
    if (coefficients[0] % prime == 0) {
        return false;
    }
    for (int i = 1; i < length; i++) {
        if (coefficients[i] % prime) {
            return false;
        }
    }
    if (coefficients[length - 1] % (prime * prime) == 0) {
        return false;
    }
    return true;
}

/**
 * Checks for polynomial's irreducibility.
 *
 * @param polynomial entered polynomial
 * @param length     length of a polynomial
 * @return true if the polynomial is irreducible
 *         false - otherwise
 */
bool check_for_irreducibility(const Polynom& polynomial, int length)
{
    int* coefficients = new int[polynomial.len + 1];
    int M = -1;
    for (int i = 0; i < polynomial.len; i++) {
        coefficients[i] = polynomial.coeff[i];
    }
    for (int i = 0; i < length; i++) {
        M = max(M, coefficients[i]);
    }
    vector<int> primes = sieve_of_eratosthenes_primes(M + 1);
    for (int prime : primes) {
        if (check_eisenstein_criterion(coefficients, prime, length)) {
            return true;
        }
    }

    delete []coefficients;
    return false;
}
