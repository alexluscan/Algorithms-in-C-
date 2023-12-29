#include <fstream>
#include <vector>
#include <fstream>
using namespace std;

ifstream fin ("karb.in");
ofstream fout ("karb.out");

const int Nmax = 1e5 + 5;

int n, m, c, i, x, y, K, t[Nmax];

vector< pair<int,int> > edges[4];

void Init()
{
    for(int i = 1; i <= n; ++i)
		t[i] = i;
}

int Find(int x)
{
    if (x == t[x]) return x;
    return t[x] = Find(t[x]);
}

bool Union(int x, int y)
{
    x = Find(x); y = Find(y);
    if(x == y) return false;
    t[x] = y;
    return true;
}


int main()
{
    fin >> n >> m >> K;

    for(int i = 1; i <= m; ++i)
    {
        fin >> x >> y >> c;
        edges[c].push_back({x, y});
    }

    Init();
    // grupeaza muchiile de cost 0 în componente conexe
    for (auto e : edges[0])
		Union(e.first, e.second);
		
	// caută muchiile de cost 1 care unesc aceste componente, astfel încât să nu se formeze un ciclu între acestea
    for (auto e : edges[1])
        if (Union(e.first, e.second))
        {
            --K;
            fout << e.first << ' ' << e.second << '\n';
            edges[2].push_back(e);
        }
        else
			edges[3].push_back(e);

	// reinitializeaza padurea de multimi disjuncte
    Init();
    
	// consideră doar muchiile de cost 1 de la pasul anterior 
    for (auto e : edges[2])
		Union(e.first, e.second);
		
    // la care adaugă altele de cost 1 până ce vor fi în număr de K
    for (auto e : edges[3])
    {
        if (!K) break;

        if (Union(e.first, e.second))
        {
            --K;
            fout << e.first << ' ' << e.second << '\n';
        }
    }
    
	// adaugă muchii de cost 0 până ce se formează un arbore de acoperire
    for (auto e : edges[0])
        if (Union(e.first, e.second))
            fout << e.first << ' ' << e.second << '\n';

    return 0;
}
