#include <fstream.h>
#include <ctype.h>
#define INFILE "cod.in"
#define OUTFILE "cod.out"
#define MAX 201

int a[MAX], b[MAX], huge s[MAX][MAX], huge c[MAX][MAX], m, n, result[MAX], nr;

void ReadData();
void Solve();
void Print();

int main()
{
	ReadData();
	Solve();
	Print();

	return 0;
}

void ReadData()
{
	ifstream fin(INFILE);

	char ch = NULL;

	m = 0;

	while ( (ch = fin.get()) != '\n' )
		if ( isdigit(ch) ) a[++m] = ch - '0';

	while ( (ch = fin.get()) != EOF )
		if ( isdigit(ch) ) b[++n] = ch - '0';

	fin.close();
}

void Solve()
{
	int h = 0, k = 0;

	for ( h = 1; h <= m; h++ )
		for ( k = 1; k <= n; k++ )
			 if ( a[h] == b[k] )
			 {
				c[h][k] = c[h-1][k-1] + 1;
				s[h][k] = s[h-1][k-1] + a[h]; // suma cifrelor ?!? secventei comune
			 }
				else if ( c[h-1][k] > c[h][k-1] )
				{
					c[h][k] = c[h-1][k];
					s[h][k] = s[h-1][k];
				}
					else if ( c[h][k-1] > c[h-1][k] )
					{
						c[h][k] = c[h][k-1];
						s[h][k] = s[h][k-1];
					}
					else
					{
                    	c[h][k] = c[h-1][k];
						if ( s[h-1][k] > s[h][k-1] ) s[h][k] = s[h-1][k];
							else s[h][k] = s[h][k-1];
					}
}

void Print()
{
	ofstream fout(OUTFILE);

	int h = 0, k = 0, i = 0;

	for ( h = m, k = n; h && k; )
		if ( a[h] == b[k] )
		{
			result[++nr] = a[h];
			h--;
			k--;
		}
		else if ( c[h-1][k] > c[h][k-1] ) h--;
			else if ( c[h][k-1] > c[h-1][k] ) k--;
				else if ( s[h-1][k] > s[h][k-1] ) h--;
					else if ( s[h][k-1] > s[h-1][k] ) k--;
						else h--;

    cout << c[m][n] << endl;

	for ( i = nr; i >= 1; i-- )
		fout << result[i];

	fout << endl;

	fout.close();
}
