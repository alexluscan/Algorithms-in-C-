/*
 * Comb(n, k) = n! / k!* (n - k) !
 * 
 * Comb(n, k) = (n - k + 1) * ... * n / k!
 * 
 * 
 */ 
#include <iostream>
using namespace std;

const int N = 100000, Mod = 900001;

int pw[N]; // pw[x] = exp la care apare x in descomp

void DescNumarator(int x) // < O(sqrt(x))
{
	int d = 2, e = 0;
	
	while (x != 1)
	{
		e = 0;
		while (x % d == 0)
		{
			x /= d;
			e++;
		}
		
		pw[d] += e;
		d++;
		if (d * d > x)
			d = x;
	}
}

void DescNumitor(int x) // < O(sqrt(x))
{
	int d = 2, e = 0;
	
	while (x != 1)
	{
		e = 0;
		while (x % d == 0)
		{
			x /= d;
			e++;
		}
		
		pw[d] -= e;
		d++;
		if (d * d > x)
			d = x;
	}
}

int Comb(int n, int k) // O(1)
{
	for (int x = n - k + 1; x <= n; ++x)
		DescNumarator(x);
	for (int x = 2; x <= k; ++x)
			DescNumitor(x);
			
	int cmb = 1;
	for (int p = 2; p <= n; ++p)
		while (pw[p]--)
		{
			cmb = (1LL * cmb * p) % Mod;
		}
	 
	return cmb;
}

int main()
{
	int n, k;
	cin >> n >> k;

	cout << Comb(n, k);
}
