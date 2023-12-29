#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream fin ("heavypath.in");
ofstream fout ("heavypath.out");

using VI = vector<int>;
using VVI = vector<VI>;

class ST {
public:
    ST(const VI& values)
    {
        for (N = 1; N < int(values.size()); N <<= 1);

        tree = VI(2 * N, 0);
        for (int p = 0; p < int(values.size()); ++p)
            tree[p + N] = values[p];
        for (int i = N - 1; i > 0; --i)
            tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
    void Update(int p, const int v)
    {
        p += N;
        tree[p] = v;
        for (p >>= 1; p > 0; p >>= 1)
            tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
    int Query(int l, int r) const
    {
        l += N;
        r += N;
        int mx = 0;
        while (l <= r)
        {
            mx = max(mx, max(tree[l], tree[r]));
            l = (l + 1) / 2;
            r = (r - 1) / 2;
        }
        return mx;
    }
private:
    int N;
    VI tree;
};

vector<ST> st;
VVI G, paths;
VI v, h, nr, t, pid, pos;
int n;

void HeavyPath();
void DFS(int x);
int Query(int x, int y);

int main()
{
    int Q;
    fin >> n >> Q;
    v = VI(n + 1);
    G = VVI(n + 1);
    for (int i = 1; i <= n; ++i)
        fin >> v[i];

    for (int i = 1; i < n; ++i)
    {
        int x, y;
        fin >> x >> y;
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }

    HeavyPath();


    int op, x, y;
    for (int i = 1; i <= Q; ++i)
    {
        fin >> op >> x >> y;
        if (op == 0)
        {
            v[x] = y;
            st[pid[x]].Update(pos[x], y);
        }
        else
            fout << Query(x, y) << '\n';
    }

}

void HeavyPath()
{
    nr = h = t = pid = pos = VI(n + 1);
    DFS(1);
    for (int i = 0; i < int(paths.size()); ++i)
    {
        VI pvalues;
        for (const auto& x : paths[i])
            pvalues.emplace_back(v[x]);
        st.emplace_back(pvalues);
    }
}

void DFS(int x)
{
    int hs = 0;
    nr[x] = 1;

    for(const auto& y : G[x])
    {
        if (y == t[x])
            continue;
        h[y] = h[x] + 1;
        t[y] = x;
        DFS(y);
        nr[x] += nr[y];
        if(hs == 0 || nr[y] > nr[hs])
            hs = y;
    }

    if (hs == 0)
    {
        pid[x] = int(paths.size());
        paths.emplace_back(VI());
    }
    else
        pid[x] = pid[hs];

    pos[x] = int(paths[pid[x]].size());
    paths[pid[x]].emplace_back(x);
}

int Query(int x, int y)
{
    if (pid[x] == pid[y])
    {
        if (pos[x] > pos[y])
            swap(x, y);
        return st[pid[x]].Query(pos[x], pos[y]);
    }
    if (h[paths[pid[x]].back()] < h[paths[pid[y]].back()])
        swap(x, y);
    return max(st[pid[x]].Query(pos[x], int(paths[pid[x]].size()) - 1),
                          Query(t[paths[pid[x]].back()], y));
}
