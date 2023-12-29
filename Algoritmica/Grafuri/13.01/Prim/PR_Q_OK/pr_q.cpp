// ok - infoarena
#include <fstream>
#include <queue>
#include <bitset>
#include <tuple>
using namespace std;

const int Nmax = 200001, Inf = 1 << 30;

ifstream fin("apm.in");
ofstream fout("apm.out");

struct Edge {
	
	Edge(int node, int key) : node {node}, key {key}
	{}
	Edge() : node {0}, key {0}
	{}
    const bool operator < (const Edge &e) const
    {
        return key > e.key;
    } 
    int node, key;
};

using VI = vector<int>;
using VP = vector<pair<int, int>>;
using VVE = vector<vector<Edge>>;

vector<vector<Edge>> G;
VP apm;
VI key, t; // cheile,  predecesorii

int n;
long long cost_apm;
bitset<Nmax + 1> v;

void Prim (int x)
{
	priority_queue<Edge> Q;
    key = VI(n + 1, Inf);
    t = VI(n + 1);
    
    int y, ky;  // vecinul lui k si costul muchiei
    key[x] = 0;
    Q.push({x, 0});

    while (!Q.empty() )
    {
        x = Q.top().node;
        v[x] = 1;    // cost minim final pentru x (nu trebuie sa mai intre in coada)
       
            
        for (const auto& e : G[x])
        {
			y = e.node; ky = e.key;
			if ( v[y] ) continue;

            if( key[y] > ky )
            {
                key[y] = ky;
                t[y] = x;
                Q.push({y, key[y]});
            }
		}
		
		apm.push_back({t[x], x}); 
		cost_apm += key[x];    
		
		while (!Q.empty() && v[Q.top().node])
            Q.pop();   
    }
}

int main()
{
   
    int a, b, w, m;
	
	fin >> n >> m;
	G = VVE(n + 1);
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
