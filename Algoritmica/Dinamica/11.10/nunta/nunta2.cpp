 /*
	Sa se det suma maxima care poate fi obtinuta prin negocieri 
*/
#include <fstream.h>
#include <iomanip.h>
#include <math.h>

#define IN  "2.in"
#define OUT "nunta2.out"
#define MAX 51
#define DIM 20

#define MIC  0
#define MARE 1000

int a[MAX], n, kmax, kmin, max[MAX][MAX], min[MAX][MAX];
// E nevoie ca pt fiecare interval [i, j] sa retin atat val maxima
// in max[i,j] cat si val minima in min[i,j]
// In max[j, i] - retin pozitia k a optimului
int Max;  // inlocuieste max[i][j]
int Min;  // inlocuieste min[i][j]


void ReadData();
void Solve();
void WriteSol();


int main()
{
	ReadData();
	Solve();
	WriteSol();

	return 0;
}

void ReadData()
{
	ifstream fin(IN);

	fin >> n;

	int i = 0;

	for ( i = 1; i <= n; i++ )
		fin >> a[i];

	fin.close();
}

void Solve()
{
	int i = 0, j = 0, k = 0, nr = 0;
	for ( i = 1; i <= n; i++ ) max[i][i] = min[i][i] = a[i];

	for ( nr = 2; nr <= n; nr++ )
		for ( i = 1; i <= n - nr + 1; i++ )
		{
			j = i + nr - 1; Max = MIC; Min = MARE;
			for ( k = i; k < j; k++ )
			{
				if ( abs(max[i][k] - min[k+1][j]) > Max)
				{
					Max = abs(max[i][k] - min[k+1][j]);
					kmax = k;
				}
				if ( abs(min[i][k] - max[k+1][j]) > Max)
				{
					Max = abs(min[i][k] - max[k+1][j]);
					kmax = k;
				}

				if ( abs(max[i][k] - max[k+1][j]) < Min)
				{
					Min = abs(max[i][k] - max[k+1][j]);
					kmin = k;
				}
				if ( abs(min[i][k] - min[k+1][j]) < Min)
				{
					Min = abs(min[i][k] - min[k+1][j]);
					kmin = k;
				}

			}
			max[i][j] = Max;    max[j][i] = kmax;
			min[i][j] = Min;    min[j][i] = kmin;
		}
}

void WriteSol()
{
	ofstream fout(OUT);
	fout << max[1][n] << endl;

#define __DEBUG__
#if !defined __DEBUG__
	int i, j;
	for ( i = 1; i <= n; i++ )
	{
		for ( j = 1; j <= n; j++ )
			fout << setw(4) << max[i][j];
		fout << endl;
	}
#endif

	fout.close();
}



