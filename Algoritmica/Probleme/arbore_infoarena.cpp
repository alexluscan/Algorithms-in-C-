#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin ("arbore.in");
ofstream fout ("arbore.out");

#define eb emplace_back

using VI = vector<int>;

struct Node{
    int smax, sm;
    Node()
    {
        smax = sm = 0;
    }
} sgt[1 << 19];

const int Nmax = 1e5 + 5;
int n, m, L[Nmax], R[Nmax], ind, nd[Nmax];
VI arb[Nmax];

void DFS(int node, int dad)
{
    nd[++ind] = node;
    L[node] = ind;
    for (auto it : arb[node])
    {
        if (it == dad) continue;

        DFS(it, node);
    }
    R[node] = ind;
}

void Update(int node, int l, int r, int x, int y, int val)
{
    if (x <= l && r <= y)
    {
        sgt[node].sm += val;
        sgt[node].smax = sgt[node].sm + max(sgt[2 * node].smax, sgt[2 * node + 1].smax);
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid)
        Update(2 * node, l, mid, x, y, val);
    if (mid < y)
        Update(2 * node + 1, mid + 1, r, x, y, val);
    sgt[node].smax = sgt[node].sm + max(sgt[2 * node].smax, sgt[2 * node + 1].smax);
}

int Query(int node, int l, int r, int val)
{
    if (sgt[node].sm == val) return nd[l];
    if (l == r)
        return -1;
    int mid = (l + r) / 2;
    if (val < sgt[node].sm) return -1;
    int res = -1;
    if (sgt[2 * node].smax + sgt[node].sm >= val)
        res = Query(2 * node, l, mid, val - sgt[node].sm);
    if (res != -1)
        return res;
    if (sgt[2 * node + 1].smax + sgt[node].sm >= val)
        res = Query(2 * node + 1, mid + 1, r, val - sgt[node].sm);
    return res;
}

int main()
{
    fin >> n >> m;

    for (int i = 1, x, y; i < n; ++i)
    {
        fin >> x >> y;
        arb[x].eb(y);
        arb[y].eb(x);
    }
    DFS(1, 0);

    int tp, poz, vl, x;
    while (m--)
    {
        fin >> tp;
        if (tp == 1)
        {
            fin >> poz >> vl;
            Update(1, 1, n, L[poz], R[poz], vl);

            for (int i = 1; i <= 2 * n; ++i)
                cout << i << ' ' << sgt[i].sm << ' ' << sgt[i].smax << '\n';
            cout << '\n';
        }
        if (tp == 2)
        {
            fin >> x;
            fout << Query(1, 1, n, x) << '\n';
        }
    }
}
