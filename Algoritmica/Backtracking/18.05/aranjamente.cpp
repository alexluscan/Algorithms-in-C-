/* Generarea Aranjamentelor
 * Ex. Sa se genereze toate posibilitatile de a acorda p premii intr-o clasa cu n copii
 */
#include <fstream>
using namespace std;

ifstream fin("aranj.in");
ofstream fout("aranj.out");

int n, p;    // copii, premii
int x[15];   // x[k] = i (se acorda premiul k elevului i)
bool s[15];  // sir caracteristic
int nrsol;

void Aranj(int k);    // k - poz curenta in sirul x (scaunul curent)
void Write(int k);

int main()
{
	fin >> n >> p;
	Aranj(1);

	fout << nrsol << " solutii!";
}

void Aranj(int k)
{
	if (k > p)
	{
		Write(p);
		return;
	}

	for (int i = 1; i <= n; ++i)
	{
		x[k] = i;
		if (!s[i])
		{
			s[i] = true;
			Aranj(k + 1);
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










