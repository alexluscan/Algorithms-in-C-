/* Generarea Tuturor Submultimilor unei multimi
 */ 
#include <fstream>
using namespace std;

ifstream fin("subm.in");
ofstream fout("subm.out");

int n, p;   
int x[15];  
int nrsol = 1;

void Subm();
void Comb(int k);    
void Write(int k);
   
int main()
{
	fin >> n;
	Subm();
	
	fout << nrsol << " solutii!" << '\n';
	
	fout << (1 << n);
}

void Subm()
{
	fout << "Multimea vida\n";
	for (p = 1; p <= n; ++p)
		Comb(1);
}

void Comb(int k)
{
	if (k > p)
	{
		Write(p);
		return;
	}
	
	for (int i = x[k - 1] + 1; i <= n - p + k; ++i)
	{
		x[k] = i;
		Comb(k + 1);
	}
}

void Write(int k)
{
	nrsol++;
	for (int i = 1; i <= k; ++i)
		fout << x[i] << ' ';
	fout << '\n';
}










