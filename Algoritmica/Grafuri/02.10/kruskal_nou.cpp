// ok infoarena
// Algoritmul lui Kruskal
// Det arborelui partial de cost minim intr-un graf
// (Minimum spanning tree (arborele minim de acoperire)

#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
ofstream fout("apm.out");


struct Edge {
	int x, y, w;
/*	Edge(int a = 0, int b = 0, int c = 0)
        : x {a}, y {b}, w {c}
    {}
  */  
    bool operator < (const Edge& e) const
    {
        return w < e.w;
    }
};

vector<Edge> g;     // memoreaza graful
vector<int> h, t;
int cost_min;      // costul APM - MST (arb part de cost min)

vector<Edge> arb;   // APM
int n, m;

void Union(int x, int y);
int Find(int x);
void ReadGraph();
void Kruskal();
void Print();

int main()
{
	ReadGraph();
	Kruskal();
	Print();

	return 0;
}

void ReadGraph()
{
	ifstream fin("apm.in");
	fin >> n >> m;
	h = vector<int>(n + 1);
	t = vector<int>(n + 1);
	for ( int i = 1; i <= n; ++i )
        t[i] = i, h[i] = 0;
	int v1, v2, cost;
	for (int i = 0; i < m; ++i)
	{
		fin >> v1 >> v2 >> cost;
        g.push_back({v1, v2, cost});
	}
	fin.close();
}

void Kruskal() // O(m * log m)
{
	sort(g.begin(), g.end());     // O(m * log2(m))
	int k = 0;  // nr muchii in APM
	int c1, c2; // componetele conexe ale varfurilor muchiei


	for (const auto& e : g)  // O(m)
	{
        c1 = Find(e.x); c2 = Find(e.y); // O(1)
		if ( c1 != c2)  // daca nu formeaza ciclu
		{
			cost_min += e.w;
			arb.push_back(e);   // adaug muchia e in APM
			Union(c1, c2);      // O(1)

			if ( k == n - 1 )  break;
		}
    }
}

void Print()
{

	fout << cost_min << '\n';
	fout << n - 1 << '\n';
	for(const auto& e : arb)
		fout << e.x << " " << e.y << '\n';
	fout.close();
}

void Union(int x, int y)
{
    t[x] = y;
}

int Find(int x)
{
    if ( x == t[x] ) return x;
    return t[x] = Find(t[x]);
}



