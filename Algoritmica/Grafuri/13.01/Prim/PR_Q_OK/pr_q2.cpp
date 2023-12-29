// ok - infoarena
#include <fstream>
#include <queue>
#include <bitset>
#include <tuple>
using namespace std;

const int Nmax = 200001, Inf = 1 << 30;

ifstream fin("apm.in");
ofstream fout("apm.out");

struct Node {
    int node, key;
    const bool operator < (const Edge &e) const
    {
        return key > e.key;
    }
};

vector<Node> G[Nmax + 1];
vector<pair<int, int>> apm;
priority_queue<Node> Q;
vector<int> key, t; // cheile,  predecesorii
int n;
long long cost_apm;
bitset<Nmax + 1> v;

void Prim (int x)
{
    key = vector<int>(n + 1, Inf);
    t = vector<int>(n + 1);
    int y, w;  // vecinul lui k si costul muchiei
    
    key[x] = 0;
    Q.push({x, 0});
	int cost;
    while (!Q.empty() )
    {

        x = Q.top().node;
        cost = Q.top().key;
        Q.pop();
        if (cost > key[x])
			continue;

        for (const auto& e : G[x])
        {
			y = e.node;
			w = e.key;

            if( key[y] > w )
            {
                key[y] = w;
                t[y] = x;
                Q.push({y, key[y]});
            }
		}

		apm.push_back({t[x], x});
		cost_apm += key[x];
    }
}

int main()
{
    int a, b, w, m;

	fin >> n >> m;
    while (m--)  // sar peste muchie [t[k], k]
    {
        fin >> a >> b >> w;
        G[a].emplace_back(b, w);
        G[b].emplace_back(a, w);
    }

    Prim(1);
	fout <<  cost_apm << '\n';
	fout << apm.size() - 1 << '\n'; // nu scriu sursa
	for (size_t i = 1; i < apm.size(); ++i)
		fout <<   apm[i].first << ' ' << apm[i].second << '\n';


    return 0;
}
