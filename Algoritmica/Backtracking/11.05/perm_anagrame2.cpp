/* Generarea Permutarilor
 * Ex. Sa se genereze toate ANAGRAMELE unui cuvant
 *     format din litere distincte
 */ 
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream fin("anagrame.in");
ofstream fout("anagrame.out");

int n;
int x[15]; // generam pozitii sdin sirul a[]
char cuv[15];
bool s[15]; // sir caracteristic
int nrsol;

void Anagrame(int k);    // k - poz curenta in sirul x (scaunul curent)
void Write(int k);
   
int main()
{
	fin >> (cuv + 1);
	n = strlen(cuv + 1);
	sort(cuv + 1, cuv + n + 1);
	Anagrame(1);
	
	fout << nrsol << " solutii!";
}

void Anagrame(int k)
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
			Anagrame(k + 1);
			s[i] = false;
		}
	}
}

void Write(int k)
{
	nrsol++;
	for (int i = 1; i <= k; ++i)
		fout << cuv[x[i]];
	fout << '\n';
}










