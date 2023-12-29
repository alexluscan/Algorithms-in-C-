/* Generarea Tuturor Submultimilor unei multimi
 * in ordine lexicografica
 */ 
#include <fstream>
using namespace std;

ifstream fin("subm.in");
ofstream fout("subm.out");

int n;   
int x[15];  
int nrsol = 1;

void Subm(int k);    
void Write(int k);
   
int main()
{
	fin >> n;
	Subm(1);
	
	fout << nrsol << " solutii!" << '\n';
	
}

void Subm(int k)
{
	if (k > n)
		return;
	for (int i = x[k - 1] + 1; i <= n; ++i)
	{
		x[k] = i;
		Write(k);
		Subm(k + 1);
	}
}

void Write(int k)
{
	nrsol++;
	for (int i = 1; i <= k; ++i)
		fout << x[i] << ' ';
	fout << '\n';
}










