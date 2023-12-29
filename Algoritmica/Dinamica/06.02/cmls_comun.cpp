#include <fstream>
using namespace std;

ifstream fin ("cmls_comun.in");
ofstream fout ("cmls_comun.out");

int n, m;
int a[100], b[100];
int c[100][100];

void read();
void solve();

int main ()
{
	read();
	solve();
	fout << c[n][m];
}

void read()
{
	int i;
	fin >> n >> m;
	for (i = 1; i <= n; i++)
		fin >> a[i];
	for (i = 1; i <= m; i++)
		fin >> b[i];
}

void solve()
{
	int i, j;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
		{
			if (a[i] == b[j])
				c[i][j] = c[i - 1][j - 1] + 1;
			else
				c[i][j] = max(c[i - 1][j], c[i][j - 1]);
		}
}
