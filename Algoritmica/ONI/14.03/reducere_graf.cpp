/* Reducere la Directed Acyclic Graph (DAG)
 * Colapsarea componentelor tare conexe in noduri.
 * Se obtine un nou graf orientat aciclic,
 */ 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

using VI  = vector<int>;
using VVI = vector<VI>;
using VB  = vector<bool>;

VVI G;
VVI dag;
VI  lv, low;
VI c;            // c[x] = nodul din noul graf (componenta tare conexa) care include nodul x din graful initial
stack<int> stk;  // stiva din care extragem ctc
VB inStack, v;

int n, m;
int N;         //  N - nr noduri dag
int idx;


void CitesteGraf();
void Tarjan(int x);
void CreazaDAG();
void ScrieDag();

int main()
{
	CitesteGraf();
	for (int i = 1; i <= n; ++i)
		if (lv[i] == 0)
			Tarjan(i);

	CreazaDAG();
	ScrieDag();
}

int y;

void Tarjan(int x)
{
	low[x] = lv[x] = ++idx; 
	stk.push(x);
	inStack[x] = true;
	
	for (const int& y : G[x])
	{
		if (lv[y] == 0)
		{
			Tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else
			if (inStack[y])
				low[x] = min(low[x], lv[y]);
	}
	
	if (low[x] == lv[x])
	{
		N++;
		while (true)
		{
			y = stk.top();
			c[y] = N;
			stk.pop();
			inStack[y] = false;
			if (y == x)
				break;
		}
	}
}

void CreazaDAG()
{
	dag = VVI(N + 1);
	for (int x = 1; x <= n; ++x)
		for (const int& y : G[x])
			if (c[x] != c[y])
				dag[c[x]].push_back(c[y]);
}

void ScrieDag()
{
	fout << "N = " << N << '\n';
	for (int i = 1; i <= N; ++i)
	{
		fout << "Dag " << i << " : ";
		for (int y : dag[i])
			fout << y << ' ';
		
		fout << '\n';
	}
	
	fout << "Ce contin nodurile DAG:\n";
	for (int i = 1; i <= N; ++i)
	{
		fout << "Colaps " << i << " contine nodurile : ";
		for (int j = 1; j <= n; ++j)
			if (c[j] == i)
				fout << j << ' ';
		fout << '\n';
	}
}

void CitesteGraf()
{
	fin >> n >> m;
	G = VVI(n + 1);
	lv = low = VI(n + 1);
	inStack = v = VB(n + 1);
	c = VI(n + 1);
	int x, y; 
	while (m--) 
	{
		fin >> x >> y; 
		G[x].push_back(y);
	}
}

