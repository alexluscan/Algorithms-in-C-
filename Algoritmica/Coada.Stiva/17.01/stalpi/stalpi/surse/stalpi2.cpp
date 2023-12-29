#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

#define MAXD 10001
#define MAXN 51
#define INT_MAX 0x3f3f3f3f

int n;
int a[2][MAXD];
int R;
int p[MAXN];
int D;
int E;

int Test(int r);

ifstream fin("stalpi.in");
ofstream fout("stalpi.out");

int main()
{
	fin >> n >> E;

	p[0] = 0;
	for ( int i = 1; i < n; ++i )
		fin >> p[i];
	D = p[n-1];
	int m = 0;
	int lo = 0, hi = D;
	while ( lo <= hi )
	{
		m = (lo + hi) / 2;
	
		if ( Test(m) )
			hi = m - 1;
		else
			lo = m + 1;
	}
	R = hi + 1;
	fout << R << '\n';
	
	fin.close();
	fout.close();
}

int Test(int r)
{
	
	for ( int i = 0; i < 2; ++i )
		for  ( int j = 0; j <= D; ++j )
			a[i][j] = INT_MAX;	
	
	for ( int j = 0; j <= D; ++j )
	{
		if ( j > r ) 
			continue;		
		if ( j == p[1] )  
			a[1][j] = 0;  
		else
			a[1][j] = abs(j - p[1]);  
	}
	
	int cr = 0, pr = 1; 
	for ( int i = 2; i < n - 1; ++i, cr = !cr, pr = !pr ) 
		for ( int j = 0; j <= D; ++j )
			for ( int k = 0; k <= r && k <= j; ++k )
				if ( j - k >= 0 && a[pr][j-k] != INT_MAX )
					a[cr][j] = min(a[cr][j], a[pr][j-k] + abs(j - p[i]));
	
	for (int j = D - r; j <= D; ++j )
		if ( a[pr][j] <= E )  
			return true;
	return false;
}
