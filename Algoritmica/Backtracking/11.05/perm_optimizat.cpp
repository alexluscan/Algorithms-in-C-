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
bool s[15]; // sira caracteristic
int nrsol;

void Perm(int k);    // k - poz curenta in sirul x (scaunul curent)
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
	
	for (int i = 1; i <= n; ++i)
	{
		x[k] = i;
		if (!s[i])
		{
			s[i] = true;
			Perm(k + 1);
			s[i] = false;
		}
	}
}

void Write(int k)
{
	nrsol++;
	for (int i = 1; i <= k; ++i)
		fout << x[i] << ' ';
	fout << '\n';
}










