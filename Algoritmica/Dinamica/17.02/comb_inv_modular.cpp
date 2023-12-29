#include <iostream>
using namespace std;

const int N = 100000, Mod = 900001;

int I[N]; // I[i] = inv modular al lui i!
int F[N]; // F[i] = i! % Mod

int Pow(int x, int n)
{
	int r = 1, p = x;
	
	while (n)
	{
		if (n & 1)
			r = (1LL * r * p) % Mod;
		p = (1LL * p * p) % Mod;
		
		n >>= 1;
	}
	return r;
}

void Calc(int n, int k)
{
	F[0] = I[0] = 1;
	for (int i = 1; i <= n; ++i) // O(n)
	{
		F[i] = ( 1LL * i * F[i - 1]) % Mod;
	//	I[i] = Pow(F[i], Mod - 2);
	}
	
	I[n - k] = Pow(F[n - k], Mod - 2); // 18
	I[k] = Pow(F[k], Mod - 2);
}

int Comb(int n, int k) // O(1)
{
	int cmb = F[n];
	cmb = ((long long)cmb * I[n - k]) % Mod;
	cmb = ((long long)cmb * I[k]) % Mod;
	return cmb;
}

int main()
{
	int n, k;
	cin >> n >> k;
	Calc(n, k);
	cout << Comb(n, k);
}
