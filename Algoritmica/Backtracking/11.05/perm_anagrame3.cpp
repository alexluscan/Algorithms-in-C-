/* Generarea Permutarilor
 * Ex. Sa se genereze toate ANAGRAMELE DISTINCTE ale unui cuvant
 *     format din litere nu neaparat distincte
 */ 
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream fin("anagrame2.in");
ofstream fout("anagrame2.out");

int n;
int x[15]; // generam pozitii sdin sirul a[]
char cuv[15];
bool s[15]; // sir caracteristic
int nrsol;

void Anagrame(int k);    // k - poz curenta in sirul x (scaunul curent)
void Write(int k);
bool Ok(int k);
   
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
		if (Ok(k))
			Anagrame(k + 1);
	}
}

void Write(int k)
{
	nrsol++;
	for (int i = 1; i <= k; ++i)
		fout << cuv[x[i]];
	fout << '\n';
}

bool Ok(int k)
{
	for (int i = 1; i < k; ++i)
		if (x[i] == x[k] ||         //nu tr sa se repete pozitiile generate
			(cuv[x[k]] == cuv[x[i]] && x[k] < x[i]))
				return false;
	return true;
}








