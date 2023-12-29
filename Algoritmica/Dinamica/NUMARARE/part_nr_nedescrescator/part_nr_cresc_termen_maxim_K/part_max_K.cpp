// OK 
// nr de partitii crescatoare a lui n cu cel mai mare termen K
#include <fstream>
using namespace std;
ifstream fin("part.in");
ofstream fout("part_matr.out");

void Debug();

int a[500][500];   // a[i][j] - nr de partitii a lui i cu ultimul (cel mai mare) termen CEL MULT j 
int n, K;          // K - cel mai mare termen al oricarei partitii

int main()
{
	fin >> n >> K;
	
    for (int i = 1; i <= n; ++i)
    {
		a[1][i] = 1;    // clar
		a[i][1] = 1;
	}
	
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 2; j <= K; ++j)
			if ( i > j )
				a[i][j] = a[i][j - 1] + a[i - j][j]; // ok - sume partiale
			else
				a[i][j] = 1 + a[i][i - 1];  // ok dar de ce ?
	}
	fout << a[n][K] << '\n';
	
//	Debug();
	fin.close();
	fout.close();
}


void Debug()
{
	for (int i = 1; i <= n; ++i)
	{
		for ( int j = 1; j <= K; ++j)
			fout << a[i][j] <<  ' ';
		fout << '\n';
	}
}
