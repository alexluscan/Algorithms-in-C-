#include <fstream>
using namespace std;

ifstream fin("entries.in");
ofstream fout("entries.out");

/*int Find(int x) // cautare cu compresie
{
    int r, y = x;
    while (y != t[y])
        y = t[y];
    r = y;

    // compresia drumului

    y = x;
    while (x != t[x])
    {
        x = t[x];
        t[y] = r;
        y = x;
    }

    return r;
}*/

const int MaxP = 10000001;

int t[MaxP];
int n, p;
int x, y, q;

int Find(int x)
{
    if (x == t[x])
        return x;
    return t[x] = Find(t[x]);
}

void Union(int x, int y)
{
    int r1 = Find(x);
    int r2 = Find(y);
    if (r1 != r2)
        t[r1] = r2;
}

void Init()
{
    for (int i = 1; i < MaxP; ++i)
        t[i] = i;
}

int main()
{
    fin >> n;
    Init();
    for (int i = 1; i <= n; ++i)
    {
        fin >> x >> y >> q;

        if (q == 1)
            Union(x, y);
        else
            fout << (Find(x) == Find(y)) << '\n';
    }

    fin.close();
    fout.close();

    return 0;
}
