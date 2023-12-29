/* In cate moduri se poate urca o scara cu n trepte stiind ca 
 * la fiecare pas se pot sari 1, 2, ...k trepte 
 */
#include <fstream>
using namespace std;

ifstream fin("scari.in");
ofstream fout("scari.out");

const int Dim = 50;
int x[100]; // x[k] = 1, 2, ..., k
int p, n, nrsol;     // nr de trepte ale scarii

void Write(int k)
{
	nrsol++;
/*	for (int i = 1; i <= k; ++i)
		fout << x[i] << ' ';
	fout << '\n'*/
}

void Back(int k, int sp)
{
	if ( sp == n )
	{
		Write(k - 1);
		return;
	}

	if ( k > n) return;
	
	
	for (int i = 1; i <= p && sp + i <= n; ++i)
	{
		x[k] = i;
		Back(k + 1, sp + i);
	}
}

int main()
{
	
	fin >> n >> p;
	Back(1, 0);
	fout << nrsol;
	fin.close();
	fout.close();
	return 0;
}
