#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream fin("ture.in");
ofstream fout("ture.out");
const int Nmax = 256;

using LL = long long;

bool A[Nmax][Nmax];
bool B[Nmax][Nmax]; // transpusa lui A
int c[256][256];    // c[i][j] - nr de posibilitati pt o matrice cu i linii
                    // daca pana linia i inclusiv, sunt ture pe coloanele din masca j

int n, m, k;
LL  sol;

void Debug()
{
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j < (1 << m); ++j)
           fout << c[i][j] << ' ';
        fout << '\n';
    }

}

void Dinamica()
{
    c[0][0] = 1;

	for (int i = 1; i <= n; ++i)                       // pt fiecare linie i
        for (int j = 0; j < (1 << m); ++j)             // pt fiecare submultime de coloane (masca)
        {
            c[i][j] += c[i - 1][j];
            for (int k = 0; k < m; ++k)                // verific daca pe linia i
                if (!A[i - 1][k] && !((1 << k) & j))   // nu e obstacol pe col k si nu aveam deja tura pe col k
                    c[i][j | (1 << k)] += c[i - 1][j]; // atunci putem pune tura pe linia i si col k
        }
}

int nbit(int x)
{
	return x ? 1 + nbit(x&(x-1)) : 0;
}

int main()
{
	fin >> n >> m >> k;

	int P, x, y;
	fin >> P;
	while (P--)
	{
		fin >> x >> y;
		x--, y--;
		A[x][y] = true;
	}

	if ( n < m)
	{
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				B[j][i] = A[i][j];
		memcpy(A, B, sizeof(B));
		swap(n, m);
	}

	Dinamica();
    Debug();
	for (int i = 0; i < (1 << m); ++i)
		if (nbit(i) == k)
			sol += c[n][i];

	fout << sol << '\n';

	return 0;
}
