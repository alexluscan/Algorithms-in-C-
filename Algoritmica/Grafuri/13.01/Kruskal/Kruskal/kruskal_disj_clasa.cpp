// Det Arb Partial de Cost Minim ( Minimum Spanning Tree)
// Arb minim de acoperire
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("kruskal.in");
ofstream fout("kruskal.out");


class DS {
public:
    DS(int n): t {vector<int>(n)} 
    {
        for (int i = 0; i < n; ++i) 
            t[i] = i;
    }

    int& operator[](int x) 
    {
        int y, p;
        for (y = x; y != t[y]; y = t[y]);
        
        for (; x != y; x = p) 
        {
            p = t[x];
            t[x] = y;
        }
        return t[y];
    }
private:
    vector<int> t;
};


struct Edge {
    int from, to, w;
    Edge(int from, int to, int w) :
		from {from}, to {to}, w{w}
    {}
    bool operator < (const Edge& e) const {
        return w < e.w;
    }
};

void Read();
void Write();
void Kruskal();

vector<Edge> edges, apm;
int64_t cmin;
int n;

int main() 
{
	Read();
	Kruskal();
	Write();
}

void Kruskal()
{
    sort(edges.begin(), edges.end());    // O(m * log m)
	DS t(n + 1);
    int cnt = 0;
    for (const Edge& e : edges) // O(n)
		if (t[e.from] != t[e.to])
		{
			cmin += e.w;
			apm.push_back(e);
			cnt++;
			if ( cnt == n - 1 )
				break;
		}
}

void Read()
{
    fin >> n;
    int x, y, cost;
    while (fin >> x >> y >> cost)
        edges.push_back({x, y, cost});
    fin.close();
}

void Write()
{
    fout << "Costul minim: " << cmin << '\n';
    for (auto& e :  apm)
        fout << e.from << ' ' << e.to << ' ' << e.w << '\n';
}
