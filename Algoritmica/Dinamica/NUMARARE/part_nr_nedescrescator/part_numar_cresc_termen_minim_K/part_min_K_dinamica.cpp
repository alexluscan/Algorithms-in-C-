// OK 
// nr de partitii crescatoare a lui n cu cel mai mic termen K
#include <fstream>
using namespace std;
ifstream fin("part.in");
ofstream fout("part.out");

int a[500][500];   // a[i][j] - nr de partitii a lui i cu primul (cel mai mic) termen j
int n, K;

int main()
{
	fin >> n >> K;
	
	a[1][1] = 1;
    for (int i = 2; i <= n; ++i)
    {
		a[i][i] = 1;
		for (int j = 1; j <= i; ++j)
		{ 
			if ( i < 2 * j)
				a[i][j] = 0;
			else
			{
				a[i][j] = 1; // pentru cazul i = j + [i - j]  (nu mai descompun diferenta [i - j])
				for ( int k = j; k <= i / 2; ++k)
					a[i][j] += a[i - j][k];
			}
		}
	}
	fout << "dyn: " << a[n][K] << '\n';
/*	
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= K; ++j)
			fout << a[i][j] << ' ';
		fout << '\n';
	}
*/
	fin.close();
	fout.close();
}
