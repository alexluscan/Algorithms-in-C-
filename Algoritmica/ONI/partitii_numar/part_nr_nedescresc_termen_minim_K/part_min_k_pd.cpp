// nr de partitii a lui n  a.i. termenul minim in fiecare partitie este CEL PUTIN K
#include <fstream>
using namespace std;
ifstream fin("part.in");
ofstream fout("part.out");


int n, K;

int main()
{
	int a[500][500];   // a[i][j] - nr de partitii a lui i a.i. termenul minim in fiecare partitie este CEL PUTIN j
	fin >> n >> K;
	for (int i = 1; i <= n; ++i)
		a[i][i] = 1;
		
	for (int i = 2; i <= n; i++)
		for (int j = i - 1; j >= 1; --j)
				a[i][j] = a[i - j][j] + a[i][j + 1]; // cate incep cu j + cate incep cu val mai mari ca j
				
	fout << a[n][K] << '\n';
 
}
