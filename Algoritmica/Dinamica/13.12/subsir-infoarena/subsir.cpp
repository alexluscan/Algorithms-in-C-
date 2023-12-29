#include<cstring>
#include<fstream>
using namespace std;

const int MOD = 666013;

#define asize strlen(a)
#define bsize strlen(b)
#define a(i) a[i - 1]
#define b(i) b[i - 1]
#define elif else if

void comp();

int d[501][501], r[501][501];
char a[501], b[501];

int main()
{
	ifstream fin("subsir.in");
	ofstream fout("subsir.out");
	fin >> a >> b;
	comp();
	fout << r[asize][bsize];
}

void comp()
{
	for (int i = 1; i <= (int)asize; ++i)
		for (int j = 1; j <= (int)bsize; ++j)
			if (a(i) == b(j))
			{
				d[i][j] = d[i - 1][j - 1] + 1;
				r[i][j] = r[i - 1][j - 1];
				if (!r[i][j])
					++r[i][j];
			}
			elif (d[i - 1][j] > d[i][j - 1])
			{
				d[i][j] = d[i - 1][j];
				r[i][j] = r[i - 1][j];
			}
			elif (d[i][j - 1] > d[i - 1][j])
			{
				d[i][j] = d[i][j - 1];
				r[i][j] = r[i][j - 1];
			}
			else
			{
				d[i][j] = d[i - 1][j];
				r[i][j] = r[i - 1][j] + r[i][j - 1];
				r[i][j] %= MOD;
				if (d[i - 1][j] == d[i - 1][j - 1])
				{
					r[i][j] -= r[i - 1][j - 1];
					r[i][j] += MOD, r[i][j] %= MOD;
				}
			}
}
