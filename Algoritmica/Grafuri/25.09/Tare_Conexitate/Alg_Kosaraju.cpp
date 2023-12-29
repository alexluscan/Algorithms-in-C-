/* Determinarea componentelor Tare-Conexe
 * pr un Graf Orientat
 * Algoritmul lui Kosaraju
 * O(n + m) (de 2 ori) - Time Complexity
 * O(m) de 2 ori       - Memory Complexity 
 */ 
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

using VI  = vector<int>;
using VVI = vector<VI>;
using VB  = vector<bool>;

VVI G, GT;  // graful, graful transpus
VB v;       // marcam nodurile vizitate
stack<int> stk; // retine nodurile la parcurgerea Df
                // in ordinea terminarii lor
VI c;           // comp tare conexa curenta
VVI ctc;        // retine ca vectori toate comp tare conexe  

int n, m;            // noduri, arce

void CitesteGraf();
void Kosaraju();     // det comp tare conexe
void Df(int x);
void DfT(int x);     // parcurgere pe graful Transpus
void AfiseazaCompTareConexe();


int main()
{
	CitesteGraf();
	Kosaraju();
	AfiseazaCompTareConexe();
}  

void CitesteGraf()
{
	fin >> n >> m;
	G = GT = VVI(n + 1);
	v = VB(n + 1);
	int x, y;
	for (int i = 1; i <= m; ++i)
	{
		fin >> x >> y;
		G[x].emplace_back(y);
		GT[y].emplace_back(x);
	}
}

void Kosaraju()
{
	for (int x = 1; x <= n; ++x)
		if (!v[x])
			Df(x);
	
	v.assign(n + 1, false);
	//v = VB(n + 1);
	int x;
	while (!stk.empty())
	{
		x = stk.top(); stk.pop();
		if (v[x]) continue;
		c.clear();
		DfT(x);
		ctc.emplace_back(c);
	}
}

void Df(int x)
{
	v[x] = true;
	for (const int y : G[x])
	{
		if (v[y]) continue;
		Df(y);
	}
	stk.push(x);
}

void DfT(int x)     // parcurgere pe graful Transpus
{
	v[x] = true;
	c.emplace_back(x);
	
	for (const int& y : GT[x])
	{
		if (v[y]) continue;
		DfT(y);
	} 
}

void AfiseazaCompTareConexe()
{
	fout << ctc.size() << '\n';
	
	for (const auto& comp : ctc)
	{
		for (const int& x : comp)
			fout << x << ' ';
		fout << '\n';
	}
}
