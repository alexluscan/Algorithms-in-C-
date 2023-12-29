/* Generarea Produsului Cartezian a n multimi
 * 
 * Ex.
 * Sa se genereze toate meniurile distincte care pot fi comandate la restaurant,
 * cunoscand multimea de Supe, multimea de Felul II, si multimea de deserturi
 * 
 */ 
#include <fstream>
using namespace std;

ifstream fin("cartez.in");
ofstream fout("cartez.out");

int n; // numarul de multimi
int card[15];  // cardinalelel multimiloe
int x[15];  
int nrsol;

void Cartez(int k);    
void Write(int k);
   
int main()
{
	fin >> n;
	for (int i = 1; i <= n; ++i)
		fin >> card[i];
		
	Cartez(1);
	
	fout << nrsol << " solutii!" << '\n';

}

void Cartez(int k) // k - multimea curenta
{
	if (k > n)
	{
		Write(n);
		return;
	}
	
	for (int i = 1; i <= card[k]; ++i)
	{
		x[k] = i;
		Cartez(k + 1);
	}
}

void Write(int k)
{
	nrsol++;
	for (int i = 1; i <= k; ++i)
		fout << x[i] << ' ';
	fout << '\n';
}










