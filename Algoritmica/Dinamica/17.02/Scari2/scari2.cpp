/* In cate moduri se poate urca o scara cu n trepte stiind ca 
 * la fiecare pas se pot sari 1, 2, ...k trepte 
 * Initial este pe treapta 1
 */
#include <fstream>
using namespace std;

ifstream fin("scari.in");
ofstream fout("scari.out");

const int Dim = 50;

int nr[Dim]; // nr[i] - nr de modalitati de a ajunge pe treapta i
int k, n; // nr de trepte ale scarii

int main()
{
	
	fin >> n >> k;
	nr[0] = 1;
	nr[1] = 1;
	
	for (int i = 2; i <= n; ++i)
		for (int j = 1; j <= k; j++)  
			if ( i >= j )
				nr[i] += nr[i - j];
		
	fout << nr[n];
	
	fin.close();
	fout.close();
	return 0;
}
