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
	
    const bool operator < (const Edge &e) const
    {
        return key > e.key;
    } 
    int node, key;
};

using VI = vector<int>;
using VP = vector<pair<int, int>>;
using VVE = vector<vector<Edge>>;

VVE G;
VP apm;
VI key, t; // cheile,  predecesorii

int n;
long long cost_apm;
bitset<Nmax + 1> v;

void CitesteGraf();
void Prim (int x);
void ScrieSol();

int main()
{
	CitesteGraf();   
	Prim(1);
	ScrieSol();

    return 0;
}

void Prim (int x)
{
	priority_queue<Edge> Q;
    key = VI(n + 1, Inf);
    t = VI(n + 1);  // tati
    
    key[x] = 0;
    Q.emplace(x, 0);

    while (!Q.empty() )
    {
        x = Q.top().node;
        Q.pop();  
        if (v[x]) continue; 
        v[x] = 1;    // cost minim final pentru x (nu trebuie sa mai intre in coada)   
        apm.emplace_back(t[x], x); 
		cost_apm += key[x];    
		    
        for (auto [y, w] : G[x])      // 
        {
			if ( v[y] ) continue;    // daca muchia [x-y] face parte din  

            if ( key[y] > w )
            {
                key[y] = w;
                t[y] = x;
                Q.emplace(y, key[y]);
            }
		}		
    }
}

void CitesteGraf()
{
	int a, b, w, m;	
	fin >> n >> m;
	G = VVE(n + 1);
    while (m--)  
    {
        fin >> a >> b >> w;
        G[a].emplace_back(b, w);
        G[b].emplace_back(a, w);
    }
}

void ScrieSol()
{
	
	fout << cost_apm << '\n';
	fout << apm.size() - 1 << '\n'; // nu scriu muchia [0, sursa]
	for (size_t i = 1; i < apm.size(); ++i)
		fout <<   apm[i].first << ' ' << apm[i].second << '\n';
}
