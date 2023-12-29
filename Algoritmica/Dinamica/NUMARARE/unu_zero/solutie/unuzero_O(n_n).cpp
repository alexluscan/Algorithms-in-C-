// O(n^2)
#include <fstream>
using namespace std;

ifstream fin("unuzero.in");
ofstream fout("unuzero.out");
	
const int mod = 666013, Dim = 1000100;
int a, b, n;
int u[Dim], z[Dim];

int main()
{
	fin >> n >> a >> b;
	z[0] = 1;
	z[1] = 1;
	if (a == 1) 
		u[1] = 1;
	for (int i = 2; i <= n;++i)
	{
		z[i] = z[i - 1] + u[i - 1]; // daca punem 0
		z[i] %= mod;
		for (int j = i - b; j <= i - a; ++j) // daca punem 1
			if (j >= 0)
			{
				u[i] += z[j];
				u[i] %= mod;
			}
	}
	
	int sol = z[n] + u[n] - 1;
	if (sol < 0)
		sol += mod;
		
	fout << sol % mod << '\n';
	
	return 0;
}
