#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream is("urgenta.in");
ofstream os("urgenta.out");

struct Edge{
    int x, y, cost;
    bool v;
    bool operator < ( const Edge& c ) const
    {
        return cost < c.cost;
    }
};

vector<Edge> g;
vector<int> h;
vector<int> p;
int n, m, k;
int gravmax;
int cnt;
void Read();
int Find(int x);
void Kruskal();
void Union(int x, int y);


int main()
{
    Read();
    Kruskal();
    os << gravmax << '\n' << m  - n + cnt << '\n';
    for ( auto& a : g )
        if ( Find(a.x) != Find(a.y) )
        {
			a.v = true;
            os << a.x << ' ' << a.y << '\n';
		}
	for ( auto& a : g )
		if ( a.v == false )
			os << a.x << ' ' << a.y << '\n';
     
    is.close();
    os.close();
    return 0;
}

void Read()
{
    int x, y, cost;
    is >> n >> m >> k;
    cnt = n;
    h = vector<int>(n + 1);
    p = vector<int>(n + 1);
    for ( int i = 1; i <= m; ++i )
    {
        if ( i <= n )
            p[i] = i;
        is >> x >> y >> cost;
        gravmax += cost;
        g.push_back({x, y, cost, false});
    }
}

int Find(int x)
{
    if ( x != p[x] )
        p[x] = Find(p[x]);
    return p[x];
}

void Union(int x, int y)
{
    if ( h[x] < h[y] )
        p[x] = y;
    else
    {
        p[y] = x;
        if ( h[x] == h[y] )
            h[x]++;
    }
}

void Kruskal()
{
    sort(g.begin(), g.end());
    int c1, c2;
    for ( auto& a : g )
    {
        c1 = Find(a.x);
        c2 = Find(a.y);
        if ( c1 != c2 )
        {
            if ( cnt == k )
                return;
            a.v = true;
            cnt--;
            gravmax -= a.cost;
            Union(c1, c2);
        }
    }
}
