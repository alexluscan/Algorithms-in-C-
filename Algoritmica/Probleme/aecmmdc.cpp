#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("aecmmdci.in");
ofstream fout ("aecmmdci.out");

void Update(int nd, int l, int r);
void Query(int nd, int l, int r);
int GCD(int a, int b)
{
    int r;
    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

const int N = 100005;
int n, q, v[N], A[4 * N], p, st, dr, x, cmdc;

int main()
{
    int tp;
    fin >> n;
    for (int i = 1; i <= n; ++i)
    {
        fin >> v[i];
        p = i;
        x = v[i];
        Update(1, 1, n);
    }
    fin >> q;
    for (int i = 1; i <= q; ++i)
    {
        fin >> tp;
        if (tp == 1)
        {
            fin >> st >> dr;
            cmdc = 0;
            Query(1, 1, n);
            cout << cmdc << '\n';
        }
        else
        {
            fin >> p >> x;
            Update(1, 1, n);
        }
    }
}

void Update(int nd, int l, int r)
{
    if (l == r)
    {
        A[nd] = x;
        return;
    }
    int mij = (l + r) / 2;

    if (p <= mij)
        Update(2 * nd, l, mij);
    else
        Update(2 * nd + 1, mij + 1, r);

    A[nd] = GCD(A[2 * nd], A[2 * nd + 1]);
}

void Query(int nd, int l, int r)
{
    if (st <= l && r <= dr)
    {
        cmdc = GCD(cmdc, A[nd]);
        return;
    }

    int mij = (l + r) / 2;
    if (st <= mij)
        Query(2 * nd, l, mij);
    if (dr > mij)
        Query(2 * nd + 1, mij + 1, r);
}
