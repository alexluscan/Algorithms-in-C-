#include <bits/stdc++.h>
using namespace std;
using VI  = vector<int>;
using VVI = vector<VI>;
const int INF(1e9 + 1);
VVI g;
VI first, last, v, hp;
int n, q, x, y, op, ind(-1);
inline void DFS(const int& x, const int& dad) {
    ++ind;
    first[x] = ind;
    v[ind] = x;
    for (const int& y : g[x])
        if (y != dad)
            DFS(y, x);
    last[x] = ind;
}
class Segtree {
public:
    Segtree(const int& _n = 0) : n(_n) {
        mini = cnt = flag = VI(4 * n);
        Build(1, 1, n);
    }
    inline void Update(const int& x, const int& val) {
        Update(1, 1, n, first[x] + 1, last[x], val);
    }
    inline int Query(const int& x) {
        return Query(1, 1, n, first[x] + 1, last[x]);
    }
private:
    inline void Build(const int& node, const int& st, const int& dr) {
        if (st == dr) {
            mini[node] = hp[v[st]];
            cnt[node] = 1;
            return;
        }
        int mid = (st + dr) / 2;
        Build(2 * node, st, mid);
        Build(2 * node + 1, mid + 1, dr);
        mini[node] = min(mini[2 * node], mini[2 * node + 1]);
        cnt[node] = cnt[2 * node] + cnt[2 * node + 1];
    }
    inline void Update(const int& node, const int& st, const int& dr, const int& l, const int& r, const int& val) {
        Propagate(node, st, dr);
        if (st > r || dr < l || st > dr)
            return;
        if (l <= st && dr <= r) {
            flag[node] += val;
            mini[node] -= val;
            return;
        }
        int mid = (st + dr) / 2;
        Update(2 * node, st, mid, l, r, val);
        Update(2 * node + 1, mid + 1, dr, l, r, val);
        mini[node] = min(mini[2 * node], mini[2 * node + 1]);
        cnt[node] = cnt[2 * node] + cnt[2 * node + 1];
    }
    inline int Query(const int& node, const int& st, const int& dr, const int& l, const int& r) {
        Propagate(node, st, dr);
        if (st > r || dr < l || st > dr)
            return 0;
        if (st == dr) {
            if (mini[node] > 0)
                return cnt[node];
            mini[node] = INF;
            return cnt[node] = 0;
        }
        if (l <= st && dr <= r && mini[node] > 0)
            return cnt[node];
        int mid = (st + dr) / 2;
        int r1 = Query(2 * node, st, mid, l, r);
        int r2 = Query(2 * node + 1, mid + 1, dr, l, r);
        mini[node] = min(mini[2 * node], mini[2 * node + 1]);
        cnt[node] = cnt[2 * node] + cnt[2 * node + 1];
        return r1 + r2;
    }
    inline void Propagate(const int& node, const int& st, const int& dr) {
        if (st != dr) {
            flag[2 * node] += flag[node];
            flag[2 * node + 1] += flag[node];
            mini[2 * node] -= flag[node];
            mini[2 * node + 1] -= flag[node];
            flag[node] = 0;
        }
    }
    int n;
    VI mini, cnt, flag;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    first = last = v = hp = VI(n + 1);
    g = VVI(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> hp[i] >> x;
        g[x].emplace_back(i);
    }
    DFS(0, -1);
    Segtree tree(n);
    cin >> q;
    while (q--) {
        cin >> op >> x;
        if (op == 1) {
            cin >> y;
            tree.Update(x, y);
        }
        else cout << tree.Query(x) << '\n';
    }
    return 0;
}
