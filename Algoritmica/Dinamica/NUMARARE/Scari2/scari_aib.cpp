/* In cate moduri se poate urca o scara cu n trepte stiind ca 
 * la fiecare pas se pot sari 1, 2, ...k trepte .
 * Initial este pe treapta 1
 */
#include <fstream>
using namespace std;

ifstream fin("scari.in");
ofstream fout("scari.out");

const int Dim = 100000, Mod = 9001;
int aib[Dim], d;
int nr[Dim]; // nr[i] - nr de modalitati de a ajunge pe treapta i
int k, n; // nr de trepte ale scarii

void Update(int x, int val)
{
	for ( int i = x; i <= n; i += i & -i)
		aib[i] = (aib[i] + val) % Mod;
}

int Query(int x)
{
	int sum = 0;
	for ( int i = x; i > 0; i -= i & - i)
		sum = (sum + aib[i]) % Mod;
	return sum;
}


int main()
{
	fin >> n >> k;
	
	nr[1] = 1;
	Update(1, 1);
	
	nr[2] = 1;
	Update(2, 1);
	
	for (int i = 3; i <= n; ++i)
	{
		d = Query(i - 1);
		if ( i > k  )
		{
			 d -= Query(i - k - 1);
			 if ( d < 0 )
				d += Mod;
		}
		nr[i] = (nr[i] + d) % Mod;
		Update(i, d);
	}
			
		
	fout << nr[n]; 
	
	fin.close();
	fout.close();
	return 0;
}
