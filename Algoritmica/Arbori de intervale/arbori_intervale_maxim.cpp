#include <iostream>
using namespace std;

void Build(int x, int l, int r);
void Update(int x, int l, int r); // la pozitia pos cu valoarea val
void Query(int x, int l, int r, int st, int dr); // pe intervalul [st; dr]

int v[105], a[420], n, pos, val;
int ans;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> v[i];

    Build(1, 1, n);
    for (int i = 1; i <= 3; ++i)
    {
        int x, y;
        cin >> x >> y;
        ans = 0;
        Query(1, 1, n, x, y);
        cout << ans << ' ';
        pos = 3;
        val = 2;
        if (i == 2)
            Update(1, 1, n);
    }
}

void Build(int x, int l, int r)
{
    if (l == r)
    {
        a[x] = v[l];
        return;
    }
    int m = (l + r) / 2;
    Build(2 * x, l, m);
    Build(2 * x + 1, m + 1, r);
    a[x] = max(a[2 * x], a[2 * x + 1]);
}

void Query(int x, int l, int r, int st, int dr)
{
    if (st <= l && r <= dr)
    {
        ans = max(ans, a[x]);
        return;
    }
    int mij = (l + r) / 2;
    if (st <= mij)
        Query(2 * x, l, mij, st, dr);
    if (dr > mij)
        Query(2 * x + 1, mij + 1, r, st, dr);
}

void Update(int x, int l, int r)
{
    if (l == r)
    {
        a[x] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos <= m)
        Update(2 * x, l, m);
    else
        Update(2 * x + 1, m + 1, r);
    a[x] = max(a[2 * x], a[2 * x + 1]);
}
