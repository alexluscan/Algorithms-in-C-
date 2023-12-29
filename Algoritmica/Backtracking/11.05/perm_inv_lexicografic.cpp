/* Generarea Permutarilor
 * Ex. Sa se genereze toate posibilitatile de a plasa n copii
 *     pe n scaune
 */ 
#include <fstream>
using namespace std;

ifstream fin("perm.in");
ofstream fout("perm.out");

int n;
int x[15]; // x[k] = i (pe scaunul k plasez copilul i)
int nrsol;

void Perm(int k);    // k - poz curenta in sirul x (scaunul curent)
bool Ok(int k); 
void Write(int k);
   
int main()
{
	fin >> n;
	Perm(1);
	
	fout << nrsol << " solutii!";
}

void Perm(int k)
{
	if (k > n)
	{
		Write(n);
		return;
	}
	
	for (int i = n; i >= 1; --i)
	{
		x[k] = i;
		if (Ok(k))
			Perm(k + 1);
	}
}

bool Ok(int k)
{
	for (int i = 1; i < k; ++i)
		if (x[i] == x[k])
			return false;
	return true;
}

void Write(int k)
{
	nrsol++;
	for (int i = 1; i <= k; ++i)
		fout << x[i] << ' ';
	fout << '\n';
}










