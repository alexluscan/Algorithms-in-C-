/* 
   Determinarea componentelor biconexe (grafuri neorientate)
   Complexitate: O(m + n)
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
VI t;          // sirul de tati (pt arborele DFS) 
int idx;       // indexul curent 
stack<PI> stk; // plasam perechi (tata, fiu)
int n, m;

void CitesteGraf();
void CompBiConexe();
void Tarjan(int x);
void ScrieCompBiConexe();
void ExtractCBC(int x, int y);

int main()
{
	CitesteGraf();
	CompBiConexe();
	ScrieCompBiConexe();
	
	return 0;
}

void CompBiConexe()
{
	for (int x = 1; x <= n; ++x)
		if (!v[x])
			Tarjan(x);
}

void Tarjan(int x)
{
	v[x] = true;
	index[x] = low[x] = ++idx;
	
	for (const int& y : G[x])
	{
		if (y == t[x]) continue; // daca y este tatal lui x, atunci x-t nu este muchie de intoarcere
		
		if (!v[y]) // daca y este fiul lui x
		{
			t[y] = x;
			stk.emplace(x, y);
			
			Tarjan(y);
			low[x] = min(low[x], low[y]);
			
			if (low[y] >= index[x])  // daca x este punct de articulatie
				ExtractCBC(x, y);    // extragem o noua componenta bi-conexa
		}
		else  // daca y este stramos al lui x
			low[x] = min(low[x], index[y]);	
	}	
}

void ExtractCBC(int x, int y)
{
	c.clear();
	while (!stk.empty())
	{
		//tie(a, b) = stk.top();
		auto [a, b] = stk.top();  // Structured binding (C++17)
		stk.pop();
		c.insert(a); c.insert(b);
		if (a == x && b == y)
			break;
	}
	
	cbc.insert(c);
}

void CitesteGraf()
{
	fin >> n >> m;
	G = VVI(n + 1); 
	v = VB(n + 1);
	index = low = t = VI(n + 1);
	int x, y;
	while (m--)
	{
		fin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
}

void ScrieCompBiConexe()
{
	fout << cbc.size() << '\n';
	for (auto c : cbc)
	{
		for (int nod : c)
			fout << nod << ' ';
		fout << '\n';
	}
}
