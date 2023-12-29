// OK
#include <fstream>
#include <vector>
#include <tuple>
#include <bitset>
#include <stack>
using namespace std;

ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

const int MaxE = 500001;

using VI   = vector<int>;
using VT   = vector<tuple<int, int>>;
using IT   = VT::iterator;
using VIT  = vector<IT>;
using VVT  = vector<VT>;

bitset<MaxE> v;
VVT G;   // G[x] - vector de muchii
VI ce;   // ciclul eulerian
int n, m;

void CitesteGraf();
void AfiseazaCiclu();
bool EsteEulerian();
void DfsIter(int x);

int main()
{
	CitesteGraf();
	if (!EsteEulerian())
		fout << "-1";
	else
	{
		DfsIter(1);
		AfiseazaCiclu();
	}
}

void CitesteGraf()
{
	fin >> n >> m;
	G = VVT(n + 1);
	for (int i = 1, a, b; i <= m; ++i)
	{
		fin >> a >> b;
		G[a].emplace_back(b, i);
		G[b].emplace_back(a, i);
	}
}


void DfsIter(int x)
{
	VIT p = VIT(n + 1);
	for (int i = 1; i <= n; ++i)
		p[i] = G[i].begin();
		
	int y, e;
	stack<int> stk;  
	stk.push(x);
	
	while (!stk.empty())
	{
		x = stk.top();
		if (p[x] == G[x].end())
		{
			ce.emplace_back(x);
			stk.pop();
		}
		else
		{
			tie(y, e) = *p[x]++;
			if (v[e]) continue;
			v[e] = 1;
			stk.push(y);
		}	
	}	
}

void AfiseazaCiclu()
{
	for (size_t i = 0; i < ce.size() - 1; ++i)
		fout << ce[i] << ' ';
}

bool EsteEulerian()
{
	for (int x = 1; x <= n; ++x)
		if (G[x].size() % 2 == 1)
			return false;
	return true;
}









