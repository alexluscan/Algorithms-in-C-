/* 
   Determinarea componentelor biconexe (grafuri neorientate)
   Algoritmul lui Tarjan
   Complexitate: O(m)
*/
#include <vector>
#include <set>
#include <fstream>
#include <stack>
using namespace std;

ifstream fin("biconex.in");
ofstream fout("biconex.out");

using PI  = pair<int, int>;
using SI  = set<int>;
using SSI  = set<SI>;
using VB  = vector<bool>;
using VI  = vector<int>;
using VVI = vector<VI>;

VVI G;   // graful
SSI cbc;  // retine componentele bi-conexe
SI c;    // componenta conexa curenta
VB v;
VI index, low; // indexul / indexul minim pt fiecare nod 
VI niv;
int nr;
VI t;          // sirul de tati (pt arborele DFS) 
int idx;       // indexul curent 
stack<PI> stk; // plasam perechi (tata, fiu)
SI artic;
int n, m;

void CitesteGraf();
void CompBiConexe();
void Tarjan(int x);

int main()
{
	CitesteGraf();
	CompBiConexe();
	for (int x : artic)
		fout << x << ' ';
	return 0;
}

int root;
void CompBiConexe()
{
	for (int x = 1; x <= n; ++x)
		if (!v[x])
		{
			root = x;
			nr = 0;
			Tarjan(x);
			if (x == root && nr > 1)
				artic.insert(x);
		}
}

void Tarjan(int x)
{
	v[x] = true;
	index[x] = low[x] = ++idx;
	niv[x] = niv[t[x]] + 1;
	if (niv[x] == 2) 
		nr++;
	for (const int& y : G[x])
	{
		if (y == t[x]) continue; // daca y este tatal lui x, atunci x-t nu este muchie de intoarcere
		
		if (!v[y]) // daca y este fiul lui x
		{
			t[y] = x;
			stk.emplace(x, y);
			
			Tarjan(y);
			low[x] = min(low[x], low[y]);
			
			if (low[y] >= index[x] && x != root)  // daca x este punct de articulatie
			{
				
				artic.insert(x);   
			}
		}
		else  // daca y este stramos al lui x
			low[x] = min(low[x], index[y]);	
	}	
}


void CitesteGraf()
{
	fin >> n >> m;
	G = VVI(n + 1); 
	v = VB(n + 1);
	index = low = t = niv = VI(n + 1);
	int x, y;
	while (m--)
	{
		fin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}
