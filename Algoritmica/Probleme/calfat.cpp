#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("calafat.in");
ofstream fout ("calafat.out");

const int dim = 2e5 + 5;
int n, m, v[dim], a[dim], lp[dim];

void Update(int p, int v);
int Query(int p);

int main()
{
    fin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        fin >> v[i];
        if (!lp[v[i]])
        {
            lp[v[i]] = i;
            continue;
        }
        Update(lp[v[i]], i - lp[v[i]]);
        lp[v[i]] = i;
    }

    int st, dr;

    while(m--)
    {
        fin >> st >> dr;
        fout << Query(dr) - Query(st - 1) << '\n';
    }
}

void Update(int p, int v)
{
    for (int i = p; i <= n; i += i & -i)
        a[i] += v;
}

int Query(int p)
{
    int s = 0;
    for (int i = p; i >= 1; i -= i & -i)
        s += a[i];
    return s;
}
