/* Generarea Combinarilor (de n luate cate p)
 * Echivalent cu generarea submultimilor de cardinal p ale unei multimi de cardinal n 
 * Ex. Sa se genereze toate posibilitatile de a forma o echipa de fotbal din p copii
 *     intr-o clasa cu n copii (ordinea intr- echipa nu conteaza)
 */ 
#include <fstream>
using namespace std;

ifstream fin("comb.in");
ofstream fout("comb.out");

int n, p;    // copii, nr copii in echipa
int x[15];   // x[k] = i ( al k-lea copil din echipa e copilul i)
int nrsol;

void Comb(int k);    // k - poz curenta in sirul x 
void Write(int k);
   
int main()
{
	fin >> n >> p;
	Comb(1);
	
	fout << nrsol << " solutii!";
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










