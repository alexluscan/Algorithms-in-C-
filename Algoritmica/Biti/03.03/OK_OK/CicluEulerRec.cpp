#include <fstream>
#include <vector>
#include <bitset>
using namespace std;

ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

const int MaxN = 100001;
const int MaxE = 500001;

struct Edge {
	int a, b;
};

using VI   = vector<int>;
using VVI  = vector<VI>;
using VE   = vector<Edge>;

bitset<MaxE> v;
VVI G;   // G[x] - vector de muchii
VE  E;
VI ce;   // ciclul eulerian
int n, m;

void CitesteGraf();
void AfiseazaCiclu();
bool EsteEulerian();
inline void Df(int x);

int main()
{
	CitesteGraf();
	if (!EsteEulerian())
		fout << "-1";
	else
	{
		Df(1);
		AfiseazaCiclu();
	}
}

void CitesteGraf()
{
	fin >> n >> m;
	G = VVI(n + 1);
	E = VE(m + 1);
	for (int i = 1, a, b; i <= m; ++i)
	{
		fin >> a >> b;
		G[a].emplace_back(i);
		G[b].emplace_back(i);
		E[i] = {a, b};
	}
}

inline void Df(int x)
{
	for (const int& e : G[x]) // pt fiecare muchie incidenta lui x
	{
		if (v[e]) continue;
		v[e] = 1;
		if (E[e].a == x)
			Df(E[e].b);
		else
			Df(E[e].a);
	}
	ce.emplace_back(x);
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









