/* Det Componentelor tare-conexe.
 * Algoritmul lui Kosaraju
 * 
 * Complexitate: 
 * 	O(2 * m) adica O(m)  - timp de executare
 *  O(2 * m) adica O(m)  - ca spatiu de memorie ocupat
 */ 
#include <fstream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

using VI  = vector<int>;
using VVI = vector<VI>; 
using VB  = vector<bool>;

ifstream fin("ctc.in");
ofstream fout("ctc.out");
int n, m;
VVI G, Gt; // graful / graful transpus
VB v;      
VVI ctc;  // retine pe fiecare linie cate o comp tare-conexa
VI  c;    // componenta tare-conexa curenta
stack<int> stk;  // retine nodurile in ordinea timpilor de terminare la parcurgerea Dfs

void CitesteGraf();
void Df(int x);
void Dft(int x); // pe graful transpus
void Kosaraju();
void ScrieCTC();

int main()
{
	CitesteGraf();
	Kosaraju();
	ScrieCTC();
	
	return 0;
}

void Kosaraju() // O(2 * m) = O(m)
{
	for (int nod = 1; nod <= n; ++nod)  // O(m)
		if (!v[nod])
			Df(nod);
	
	v = VB(n + 1);
	while (!stk.empty())  // O(m)
	{
		int x = stk.top();
		stk.pop();
		if (v[x]) continue;
		
		c.clear();
		Dft(x);
		ctc.push_back(c);
	}
}

void Df(int x) // O(m)
{
	v[x] = true;
	
	for (int const& y : G[x])
	{
		if (v[y]) continue;
		Df(y);
	}
	
	stk.push(x);
}

void Dft(int x) // O(m)
{
	v[x] = true;
	c.push_back(x);
	for (const int& y : Gt[x])
	{
		if (v[y]) continue;
		Dft(y);
	}
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
	G = Gt = VVI(n + 1);
	v = VB(n + 1);
	int x, y;
	while (m--)
	{
		fin >> x >> y;
		G[x].push_back(y);
		Gt[y].push_back(x);
	}
}
