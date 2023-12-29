// nr de partitii a lui n  a.i. termenul minim in fiecare partitie este CEL PUTIN K
#include <fstream>
using namespace std;
ifstream fin("part.in");
ofstream fout("part.out");


int a[500][500];   // a[i][j] - nr de partitii a lui i a.i. termenul minim in fiecare partitie este CEL PUTIN j

int P(int n, int k)
{
	//fout << n << ' ' << k << '\n';
	if (n == k) return a[n][k] = 1;
	if (k < 0) return a[n][k] = 0;
	if (n > k) return a[n][k] = 0;
	
	return a[n][k] = P(n - k, k) + P(n, k + 1);
}


int main()
{
	
	int n, k;	
	fin >> n >> k;
	
				
	fout << P(n, k) << '\n';
 
	for (int i = 1; i <= n; ++i, fout << '\n')
		for (int j = 1; j <= n; ++j)
			fout << a[i][j] << ' ';
}
