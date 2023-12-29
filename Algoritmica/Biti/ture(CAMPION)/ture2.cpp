// OK
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("ture.in");
ofstream fout("ture.out");


const int Nmax = 256;
using LL = long long;

bool A[Nmax][Nmax];
bool B[Nmax][Nmax]; // transpusa lui A
int n, m, k;
LL c[1 << 16], c1[1 << 16], sol;

void Dinamica()
{
	c[0] = 1;

	for (int i = 0; i < n; ++i) // pt fiecare linie i
	{
		memcpy(c1, c, sizeof(c));
		for (int j = 0; j < (1 << m); ++j)       // pt fiecare submultime de coloane (masca j)
			for (int k = 0; k < m; ++k)          // verific daca pe linia i
				if (!A[i][k] && !((1 << k) & j)) // nu e obstacol pe col k si nu aveam deja tura pe col k
					c[j | (1 << k)] += c1[j];    // atunci putem pune tura
        for (int q = 0; q < (1 << m); ++q)
            fout << c[q] << ' ';
        fout << '\n';
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
		int aux = n; n = m; m = aux;
	}

	Dinamica();

	for (int i = 0; i < (1 << m); ++i)
		if (nbit(i) == k)
			sol += c[i];
	fout << sol << '\n';

	return 0;
}
