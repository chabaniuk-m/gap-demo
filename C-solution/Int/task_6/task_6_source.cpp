

bool is_prime(int n) {

	int flag = 0;

	if (n == 0 || n == 1)
		flag = 1;

	for (int i = 2; i < n / 2; ++i) {
		if (n % i == 0) {
			flag = 1;
			break;
		}
	}

	return flag == 0;
}

int jacobi(int a, int n, int s) {

	// Algorithm 2.149

	// 1.  If a = 0 then return(0)
	if (a == 0) return 0;
	// 2. If a = 1 then return(1)
	if (a == 1) return 1;

	// 3. Write a = 2^e * a1, where a1 is odd
	int e = 0;
	int a1 = a;
	while (a1 % 2 == 0) {
		++e;
		a1 = a1 / 2;
	}

	int n_mod8 = n % 8;
	int n_mod4 = n % 4;
	int a1_mod4 = a1 % 4;

	// 4. If e is even then set s←1. , 
	if (e % 2 == 0) {
		s = 1;
	}
	// Otherwise set s←1 if n ≡ 1 or 7 (mod 8)
	else if (n_mod8 == 1 || n_mod8 == 7) {
		s = 1;
	}
	// or set s← − 1, if n ≡ 3 or 5 (mod 8).
	else if (n_mod8 == 3 or n_mod8 == 5) {
		s = -1;
	}
	// 5. If n ≡ 3 (mod 4) and a1 ≡ 3 (mod 4) then set s← − s
	else if (n_mod4 == 3 && a1_mod4 == 3) {
		s = -s;
	}
	// 6. Set n1←n mod a1.
	int n1 = n % a1;

	// 7.  If a1 = 1 then return(s);
	if (a1 == 1) {
		return s;
	}
	// otherwise return(s · JACOBI(n1,a1))
	else {
		return s * jacobi(n1, a1, s);
	}
}

struct Euclid {
	int d;
	int x;
	int y;
};

// a >= b
Euclid extended_euclidean(int a, int b);

int gcd(int, int);

int euclidean(int a, int n) {
	
	Euclid euclid = extended_euclidean(a, n);

	if (euclid.d > 1)
		return -1;
	else
		return euclid.x;
}

// Algorithm 2.107 Extended Euclidan algorithm
Euclid extended_euclidean(int a, int b) {

	Euclid res;

	if (b == 0) {
		res.d = a;
		res.x = 1;
		res.y = 0;

		return res;
	}
	
	int x2 = 1;
	int x1 = 0;
	int y2 = 0;
	int y1 = 1;

	while (b > 0) {
		int q = int(a / b);
		int r = a - q * b;
		res.x = x2 - q * x1;
		res.y = y2 - q * y1;

		a = b;
		b = r;
		x2 = x1;
		x1 = res.x;
		y2 = y1;
		y1 = res.y;
	}

	res.d = a;
	res.x = x2;
	res.y = y2;

	return res;
}

int gcd(int a, int b)
{
	// Everything divides 0
	if (a == 0)
		return b;
	if (b == 0)
		return a;

	// base case
	if (a == b)
		return a;

	// a is greater
	if (a > b)
		return gcd(a - b, b);
	return gcd(a, b - a);
}
