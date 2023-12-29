/* Generarea Permutarilor
 * Ex. Sa se genereze toate pemrutarile unui sir,
 *     in ordine lexicografica
 */ 
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin("perm2.in");
ofstream fout("perm2.out");

int n;
int x[15]; // generam pozitii sdin sirul a[]
int a[15];
bool s[15]; // sir caracteristic
int nrsol;

void Perm(int k);    // k - poz curenta in sirul x (scaunul curent)
void Write(int k);
   
int main()
{
	fin >> n;
	for (int i = 1; i <= n; ++i)
		fin >> a[i];
	
	sort(a + 1, a + n + 1);
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
		fout << a[x[i]] << ' ';
	fout << '\n';
}










