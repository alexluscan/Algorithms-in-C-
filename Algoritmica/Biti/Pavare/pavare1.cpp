#include<fstream>
using namespace std;

ifstream fin("pavare.in");
ofstream fout("pavare.out");
void comp();
void back(int i, int j, int next, int p, int v);
inline int pow(int x)
{
	return (1 << x);
}

int n, m, k, sol, c[152][1 << 16], mt[152]; // c[i][j] - pana la linia i, cu configuratia j, s-au folosit atatea caramizi
											//          (nu se considera mutarile facute pe linia i)
int main()
{
	fin >> n >> m >> k;
	for (int i = 0, a, b; i < k; ++i)
	{
		fin >> a >> b;
		mt[a - 1] |= (1 << (b - 1));
	}
	comp();
	fout << sol - 1 << '\n';
}

void comp()
{
	c[0][mt[0]] = 1;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < pow(m); ++j)
			if (c[i][j])
				back(i, j, mt[i + 1], 0, c[i][j]);
}

void back(int i, int j, int next, int p, int v)
{
	if (p >= m - 1)
	{
		if (c[i + 1][next] < v)
			c[i + 1][next] = v;
		if (v > sol)
			sol = v;
		return;
	}
	if ( (j & (pow(p) + pow(p + 1))) == 0 && (next & (pow(p) + pow(p + 1))) == 0 )
		back(i, j + pow(p) + pow(p + 1), next + pow(p) + pow(p + 1), p + 2, v + 1);
	back(i, j, next, p + 1, v);
}
