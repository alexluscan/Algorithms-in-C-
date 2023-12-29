#include <fstream>
using namespace std;

ifstream fin("8-calcule.in");
ofstream fout("calcule.out");

#define MOD 20011
int n, k, v[100010], sol, x, t, cnt[50010], s;

unsigned long long sol1;

int Bs(int a);

int main()
{
	fin >> n >> k;
    cnt[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fin >> x;

		r = (r + x) % k;      // r = (x[1] + ... x[i]) % k   - suma partiala % k
		sol1  = (sol1 + cnt[r]) % MOD;
		cnt[r]++;             // nr de resturi de val r (nr de secv x[1] .. x[i] cu suma % k = r 
	
		t = Bs(x);
		v[t] = x;
		if (t == sol)
			++sol;
	}

	fout << sol << '\n' << sol1 << '\n';
	
	fout.close();
	return 0;
}

int Bs(int a)
{
	int s = 0, d = sol, m, poz;
	while ( s <= d )
	{
		m = (s + d) / 2;
		if (v[m] >= a)
			s = poz = m + 1;
		else
			d = m - 1;
	}
	return s;
}
