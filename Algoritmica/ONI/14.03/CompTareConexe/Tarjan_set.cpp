/* Det Componentelor tare-conexe.
 * Algoritmul lui Tarjan
 * 
 * Complexitate: 
 * 	O(m)  - timp de executare
 *  O(m)  - ca spatiu de memorie ocupat
 */ 
#include <fstream>
#include <vector>
#include <fstream>
#include <set>
#include <stack>
using namespace std;

using SI   = set<int>;
using SSI  = set<SI>;
using VI   = vector<int>;
using VVI  = vector<VI>; 
using VB   = vector<bool>;

ifstream fin("ctc.in");
ofstream fout("ctc.out");
int n, m;
VVI G;  
VI index;           // retine timpii (indecsii) de descoperire 
VI low;             // low[x] = indexul minim la care se poate ajunge dintr-un nod
                    // utilizand o singura muchie de intoarcere 
int idx;            // indexul curent                    
                   
VB v;      
SSI ctc;           // retine pe fiecare linie cate o comp tare-conexa
SI  c;             // componenta tare-conexa curenta
stack<int> stk;    // retine nodurile in ordinea timpilor de descoperire
vector<bool> inStack;

void CitesteGraf();
void Df(int x);
void Tarjan();
void ScrieCTC();

int main()
{
	CitesteGraf();
	Tarjan();
	ScrieCTC();
	
	return 0;
}

void Tarjan() // O(m)
{
	for (int node = 1; node <= n; ++node)
		if (!v[node])
			Df(node);
}

void ExtractCC(int x)
{
	c.clear();
	while (!stk.empty())
	{
		int node = stk.top();
		stk.pop();
		inStack[node] = false;
		c.insert(node);
		if (node == x)
			break;
	}
	
	ctc.insert(c);
}

void Df(int x) // O(m)
{
	v[x] = true;
	stk.push(x);
	inStack[x] = true;
	index[x] = low[x] = ++idx;
	
	for (int const& y : G[x]) 
		if (!v[y]) // dac ay este fiul lui x 
		{
			Df(y);
			low[x] = min(low[x], low[y]);
		} 
		else  
			if (inStack[y]) // daca y este stramos (back-edge)
				low[x] = min(low[x], index[y]);
				
	if (index[x] == low[x])
		ExtractCC(x);
}

void ScrieCTC()
{
	fout << ctc.size() << '\n';
	
	for (auto cc : ctc)
	{
		for (int x : cc)
			fout << x << ' ';
		fout << '\n';
	}
}

void CitesteGraf()
{
	fin >> n >> m;
	G = VVI(n + 1);
	v = inStack = VB(n + 1);
	index = low = VI(n + 1);
	int x, y;
	while (m--)
	{
		fin >> x >> y;
		G[x].push_back(y);
	}
}
