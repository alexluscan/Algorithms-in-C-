// Marius Stroe

#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const char iname[] = "pamant.in";
const char oname[] = "pamant.out";

#define MAXN  100005
#define Min(a, b)  ((a) < (b) ? (a) : (b))

vector <int> adj[MAXN], dfn, low, ans, con;

stack <pair <int, int> > stk;

void read_in(vector <int>* adj, int &n)
{
    ifstream in(iname);
    int cnt_edges, x, y;

    assert(in >> n >> cnt_edges);

    assert(1 <= n && n <= 100000);
    assert(1 <= cnt_edges && cnt_edges <= 200000);

    for (; cnt_edges > 0; -- cnt_edges) {
        assert(in >> x >> y);

        assert(x != y && 1 <= x && x <= n && 1 <= y && y <= n);

        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    in.close();
}

void cache(int node) {
    ans.push_back(node);
}

void DF(const int n, const int fn, int number)
{
    vector <int>::iterator it;
    int critical = false;
    int sons = 0;

    dfn[n] = low[n] = number;
    for (it = adj[n].begin(); it != adj[n].end(); ++ it) {
        if (*it == fn)   continue ;
        if (dfn[*it] == -1) {
            stk.push( make_pair(n, *it) );
            DF(*it, n, number + 1);
            low[n] = Min(low[n], low[*it]);
            critical |= (low[*it] >= dfn[n]);
            sons ++;
        }
        else
            low[n] = Min(low[n], dfn[*it]);
    }
    if (n != fn) {
        if (critical)
            ans.push_back(n);
    } else if (sons > 1)
        ans.push_back(n);
}

int main(void)
{
    int n;
    read_in(adj, n);
    dfn.resize(n + 1), dfn.assign(n + 1, -1);
    low.resize(n + 1);

    for (int i = 1; i <= n; ++ i) if (dfn[i] == -1)
        con.push_back(i), DF(i, i, 0);

    ofstream out(oname);
    sort(con.begin(), con.end());
    out << con.size() << "\n";
    for (int i = 0; i < (int) con.size(); ++ i)
        out << con[i] << " ";  out << "\n";

    sort(ans.begin(), ans.end());
    out << ans.size() << "\n";
    for (int i = 0; i < (int) ans.size(); ++ i)
        out << ans[i] << " ";  out << "\n";
    out.close();

    return 0;
}

