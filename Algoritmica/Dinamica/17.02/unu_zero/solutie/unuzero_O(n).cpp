// O(n)
#include <fstream>
using namespace std;

ifstream fin("unuzero.in");
ofstream fout("unuzero.out");
	
const int mod = 666013, Dim = 1000100;
int a, b, n;
int s[Dim], u[Dim], z[Dim]; // s[i] = z[0] + z[1] + ... + z[i]

int main()
{	
	fin >> n >> a >> b;
	z[0] = 1;
	s[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		z[i] = z[i - 1] + u[i - 1]; // daca punem 0
		z[i] %= mod;
		
		if (i - a >= 0)
		{
			if (i - b - 1 >= 0)
				u[i] = s[i - a] - s[i - b - 1];
			else
				u[i] = s[i - a];
		}
		
		if (u[i] < 0) 
			u[i] += mod;
		u[i] %= mod;
		
		s[i] = s[i - 1] + z[i];
		s[i] %= mod;
	}
	
	int sol = z[n] + u[n] - 1;
	if (sol < 0)
		sol += mod;
		
	fout << sol % mod << '\n';
	
	return 0;
}

