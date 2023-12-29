#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("lantq.in");
ofstream fout ("lantq.out");

int n, m, a[50][50], v[50], p, q;
bool ok, uz[50];

void afis(int l);
void bac(int k);
bool cond(int j);

int main()
{
    fin >> n >> m;
    for (int x, y, i = 1; i <= m; ++i)
    {
        fin >> x >> y;
        a[x][y] = a[y][x] = 1;
    }

    fin >> p >> q;

    v[1] = p;
    uz[p] = 1;
    bac(2);
    if (!ok)
        fout << "NU EXISTA";
}

void afis(int l)
{
    ok = true;
    for (int i = 1; i <= l; ++i)
        fout << v[i] << ' ';

    fout << '\n';
}

bool cond(int j)
{
    if (j == 1)
        return 1;
    return a[v[j - 1]][v[j]];
}

void bac(int k)
{
    for (int i = 1; i <= n; ++i)
        if (!uz[i])
        {
            uz[i] = 1;
            v[k] = i;
            if (cond(k))
                if (k > 1 && i == q)
                    afis(k);
                else
                    bac(k + 1);
            uz[i] = 0;
        }
}
