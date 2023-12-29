/* Problema Reginelor
 * Sa se genereze toate posibilitatile de a plasa n regine pe o tabla
 * de sah n x n
 */ 
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin("regine.in");
ofstream fout("regine.out");

int n;       // nr de regine  
int x[15];   // x[k] = i (plasam o regina pe linia i si coloana k)
int nrsol = 1;

void Regine(int k);    
void Write(int k);
bool Ok(int k);

int main()
{
	fin >> n;
	Regine(1);
	
	fout << nrsol << " solutii!" << '\n';
	 
}

void Regine(int k) 
{
	if (k > n)
	{
		Write(n);
		return;
	}
	
	for (int i = 1; i <= n; ++i) // i - linia 
	{
		x[k] = i;
		if (Ok(k))
			Regine(k + 1);
	}
}

void Write(int k)
{
	nrsol++;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			if (x[i] == j)
				fout << "R";
			else
				fout << "*";
		fout << '\n';
	}
	fout << '\n';
}

bool Ok(int k)
{
	for (int i = 1; i < k; ++i)
		if (x[i] == x[k]  // atac pe orizontala
			|| (abs(x[k] - x[i]) == k - i )) // atac pe diagonala
			return false;
	return true;
}







