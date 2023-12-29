// punctaj maxim numai pe compilatoare pe 32 biti
// BC 3.1 nu aloca corect memorie in HEAP pt toate testele
#include <fstream.h>
#include <iomanip.h>
#define DIM 10000000
#define FIN "entries0.in"

ofstream fout("entries.out");

long int N;
long int n;

long int *p, *h;

void Solve();
void Citire();
void Union(long int x, long int y);
long int Find(long int x);

int main()
{
	Citire();	  // citeste numai pt determinarea lui n ( nr de noduri)
	Solve();
	fout.close();
	return 0;
}

void Solve()
{
	ifstream fin(FIN);	  // reciteste
	long int v1, v2, tip, r1, r2, i;
	fin >> N;
	p = new long int[n+1];
	h = new long int[n+1];

	for (i = 1; i <= n; i++)
	{
		p[i] = i;     // n arbori cu 1 varf
		h[i] = 0;  // adincime 0 in arbore
	}

	for ( i = 1; i <= N; i++ )	 // N intrari
	{
		fin >> v1 >> v2 >> tip;
		r1 = Find(v1); r2 = Find(v2);
		if ( tip == 1 )
			Union(r1, r2);		     // comanda
		if ( tip == 2 )
			if (r1 == r2)
				fout << 1 << endl;	 // intrebare (interogare)
			else
				fout << 0 << endl;
	}
	fin.close();


}

void Union(long int x, long int y)
{
	if (h[x] > h[y]) p[y] = x;
		else
		{
			p[x] = y;
			if (h[x] == h[y]) ++h[y];
		}
}

long int Find(long int x)      // cautare cu compresie
{
	if ( x != p[x] ) p[x] = Find(p[x]);
	return p[x];
}

void Citire()
{
	ifstream fin(FIN);
	long int i, j, t;
	fin >> N;
	while (fin >> i >> j >> t)
	{
		if ( i > n ) n = i;
		if ( j > n ) n = j;
	}
	fin.close();
}
