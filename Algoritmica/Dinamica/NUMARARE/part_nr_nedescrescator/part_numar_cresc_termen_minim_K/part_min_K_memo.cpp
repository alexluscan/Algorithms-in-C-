// OK - merge
// nr de partitii crescatoare a lui n cu cel mai mic termen K
#include <fstream>
#include <iostream>
using namespace std;

ifstream fin("part.in");
ofstream fout("part.out");

int a[500][500];   // a[i][j] - nr de partitii a lui i cu primul (cel mai mic) termen j
int n, K = 1;

int P(int i, int j)
{
	int& r = a[i][j];
	if ( r ) return r;
	if (i == j  || i == 2 * j) // ambele conditii trebuie
		return r = 1;
	if (i < 2 * j )       // si asta e obligatorie
		return r = 0;
	
	r = 1;                // pentru cazul i = j + [i - j]  (nu mai descompun diferenta [i - j])
	for (int k = j; k <= i / 2; ++k)
		r += P(i - j, k);
	return r; 
}

int main()
{
	fin >> n >> K;
	
	P(n, K);
	fout << "memo: " << a[n][K] << '\n';
/*	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			fout << a[i][j] << ' ';
		fout << '\n';
	}
*/	
	fin.close();
	fout.close();
}
