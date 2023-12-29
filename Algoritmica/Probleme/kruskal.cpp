#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin ("kruskal.in");
ofstream fout ("kruskal.out");

struct Edge{
    int x, y, c;

     bool operator < (const Edge& e) const
    {
            return c < e.c;
    }
};

vector <Edge> E, apm;
vector <int> h, t;
int n, m, cmin;

inline int Find(int x);
void Union(int x, int y);
void Kruskal();

int main()
{
    fin >> n >> m;
    h = t = vector<int>(n + 1);
    E = vector<Edge>(m + 1);

    for (int i = 1; i <= m; ++i)
        fin >> E[i].x >> E[i].y >> E[i].c;

    for (int i = 1; i <= n; ++i)
        t[i] = i, h[i] = 0;
    Kruskal();

    fout << cmin << '\n';
    for (const auto& eg : apm)
        fout << eg.x << ' ' << eg.y << '\n';
}

inline int Find(int x)
{
    if (x == t[x])
        return x;
    return x = Find(t[x]);
}

void Union(int x, int y)
{
    if (h[x] < h[y])
        t[x] = y;
    else
    {
        t[y] = x;
        if (h[x] == h[y])
            h[x]++;
    }
}

void Kruskal()
{
    int c1, c2;

    sort(E.begin(), E.end());
    for (const auto& eg : E)
    {
        c1 = Find(eg.x);
        c2 = Find(eg.y);
        if (c1 != c2)
        {
            cmin += eg.c;
            apm.emplace_back(eg);
            Union(c1 ,c2);
            if (apm.size() == n - 1)
                break;
        }
    }
}
