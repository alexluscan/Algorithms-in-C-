#include <fstream>
using namespace std;

#define MOD 20011

int n, k, v[100010], sol, cnt[50010], s;

unsigned long long sol1;

ifstream fin("9-calcule.in");
ofstream fout("calcule.out");

int Bs(int x);

int main()
{
	int x, t, r;
	fin >> n >> k;
	for (int i = 1; i <= n; ++i)
	{
		fin >> x;
		r = (r + x) % k;
		cnt[r]++;
		t = Bs(x);
		v[t] = x;
		if (t == sol)
			++sol;
	}
	
	sol1 = (cnt[0] % MOD);  // nr secvente x[1] .. x[i] divizibile cu k

	for (int r = 0; r < k; ++r)
	{
		sol1 += (cnt[r] % MOD) * ((cnt[r] % MOD) - 1) / 2) % MOD;  // sol1 += Comb(cnt[r], 2)
		sol1 %= MOD;
	}
	
	fout << sol << '\n' << sol1 << '\n';
	
	fout.close();
	return 0;
}

int Bs(int a)
{
	int s = 0, d = sol, m, poz;
	while (s <= d)
	{
		m = (s + d) / 2;
		if (v[m] >= a)
			poz = s = m + 1;
		else
			d = m - 1;
	}
	return poz;
}
