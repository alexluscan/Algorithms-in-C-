#include <fstream.h>

#define INFILE "nunta.in"
#define OUTFILE "nunta.out"
#define MAX 51
#define DIM 20

int a[MAX];        // nr pietre pretioase pt fiecare petitor
int n;
int m[MAX][MAX];  // m[i][j] nr sume diferite care se pot obtine la negocieri intre petitorii [i, j]
int huge v[MAX][MAX][DIM + 1]; // v[i][j][k] = 1 poate fi obtinuta suma k prin negocieri intre [i, j]

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

	fin >> n;

	int i = 0;

	for ( i = 1; i <= n; i++ )
	{
		fin >> a[i];
		v[i][i][a[i]] = 1;
		m[i][i] = 1;
	}

	fin.close();
}

void Solve()
{
	int i = 0, j = 0, k = 0, nr = 0, v1 = 0, v2 = 0;

	for ( nr = 2; nr <= n; nr++ )
		for ( i = 1; i <= n - nr + 1; i++ )
		{
			j = i + nr - 1;
			for ( k = i; k < j; k++ )
				for ( v1 = 0; v1 <= DIM; v1++ )
					if ( v[i][k][v1] )                   // s-a putut obtine suma v1 prin negocieri intre [i, k]
						for ( v2 = 0; v2 <= DIM; v2++ )
							if ( v[k+1][j][v2] )        // si suma v2 int [k+1, j]
								if ( !v[i][j][(v1 > v2) ? v1 - v2 : v2 - v1] )
								{
									m[i][j]++; // un nou mod de a obtine o suma prin negocieri intre [i..j]
									v[i][j][(v1 > v2) ? v1 - v2 : v2 - v1] = 1;
								}
		}
}

void Print()
{
	ofstream fout(OUTFILE);

	fout << m[1][n] << endl; // nr valori distincte ce pot fi obt prin negocieri intre petitorii [1, n]

	int i = 0;

	for ( i = 0; i <= DIM; i++ )
		if ( v[1][n][i] ) fout << i << " "; // sumele i care p fi obtinute prin negocieri intre[1, n]

	fout << endl;

	fout.close();
}



