#include <fstream.h>
#define IN "entries0.in"
#define OUT "entries.out"

long int n, *t, *h;
long int m;

ofstream fout(OUT);

void Read();
void Aloc( int k );
void Union( long int x, long int y );
long int Find( long int nod );

int main()
{
	ifstream fin(IN);
	long int x, y, q;
	fin >> m;
	long int i;
	for ( i = 1; i <= m; i++ )
	{
		fin >> x >> y >> q;
		if ( n < x ) n = x;
		if ( n < y ) n = y;
	}
	fin.close();
	Aloc(1);
	for ( i = 1; i <= n; i++ )
	{
		t[i] = i;
		h[i] = 0;
	}
	Read();
	Aloc(0);
	fout.close();
	return 0;
}

void Aloc( int k )
{
	if ( k )
	{
		t = new long int[n+1];
		h = new long int[n+1];
	}
	else
	{
		delete [] t;
		delete [] h;
	}
}

void Union( long int x, long int y )
{
	if ( h[x] > h[y] ) t[y] = x;
	else
	{
		t[x] = y;
		if ( h[x] == h[y] )
			h[y]++;
	}
}

long int Find( long int nod )
{
/*	long int rad = nod;
	while( rad != t[rad] )
		rad = t[rad];
	long int f;
	while( nod != rad )
	{
		f = t[nod];
		t[nod] = rad;
		nod = f;
	}
	return rad; */
	if ( nod != t[nod] ) t[nod] = Find(t[nod]);
	return t[nod];
}

void Read()
{
	ifstream fin(IN);
	long int x, y, q, r1, r2;
	fin >> m;
	for ( long int i = 1; i <= m; i++ )
	{
		fin >> x >> y >> q;
		r1 = Find(x);
		r2 = Find(y);
		if ( q == 2 )
			if ( r1 == r2 ) fout << "1\n";
			else fout << "0\n";
		else Union(r1, r2);
	}
	fin.close();
}




