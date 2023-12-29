#include <fstream>
#include <vector>
using namespace std;

ifstream fin("critice.in");
ofstream fout("critice.out");

using VI  = vector<int>;
using VVI = vector<VI>;
using VB  = vector<bool>;

VVI G; 
VB critic;
VI niv, low;
int n, m, ma; // nr de muchii de arbore incidente nodului 1

void CitesteGraf();
void Tarjan(int x, int nv, int t);

int main()
{
	CitesteGraf();
	Tarjan(1, 1, 0);
	if (ma == 1)
		critic[1] = false;
		
	for (int i = 1; i <= n; ++i)
		fout << critic[i] << ' ';
	fout.close();
}

void Tarjan(int x, int nv, int t)
{
	niv[x] = low[x] = nv;
	if (nv == 2)
		ma++;
	for (const int& y : G[x])
	{
		if (y == t)
			continue;
		if (!niv[y]) // muchie de arbore
		{
			Tarjan(y, nv + 1, x);
			low[x] = min(low[x], low[y]);
			if (low[y] >= niv[x])
				critic[x] = true;
		}
		else        // muchie de intoarcere
			low[x] = min(low[x], niv[y]);	
	}
}

void CitesteGraf()
{
	fin >> n >> m;
	G = VVI(n + 1);
	critic = VB(n + 1);
	niv = low = VI(n + 1);
	int x, y;
	while (m--)
	{
		fin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}


