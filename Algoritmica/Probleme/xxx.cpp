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

using VE = vector<Edge>;
using VI = vector<int>;

VE E, apm;
VI t, h;
int n, m, cmin;

void Kruskal();
void Union(int x, int y);
int Find(int x);

int main()
{
    fin >> n >> m;
    E = VE(m + 1);
    t = h = VI(n + 1);
    for (int i = 1; i <= m; ++i)
        fin >> E[i].x >> E[i].y >> E[i].c;

    for (int i = 1; i <= n; ++i)
        t[i] = i, h[i] = 0;

    sort(E.begin(), E.end());

    Kruskal();

    fout << cmin << '\n';
    for (const auto& eg : apm)
        fout << eg.x << ' ' << eg.y << '\n';
}

int Find(int x)
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
    for (const auto& eg : E)
    {
        c1 = Find(eg.x);
        c2 = Find(eg.y);
        if (c1 != c2)
        {
            Union(c1, c2);
            cmin += eg.c;
            apm.emplace_back(eg);
        }
    }
}
