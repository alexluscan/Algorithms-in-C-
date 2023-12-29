#include <iostream>
#include <vector>
using namespace std;

#define maxn 100005

struct ST
{
    int lazy, val, cnt;
};

ST st[5*maxn], dmcd;
vector<int> e[maxn];
int n, p, num[maxn], pos[maxn], d[maxn], v[maxn], last[maxn];

void Build(int id,int l,int r)
{
    if (l == r)
    {
        st[id].val = d[pos[l]];
        st[id].cnt = 1;
        return;
    }
    
    Build(id*2, l, (l+r)/2);
    Build(id*2+1, (l+r)/2 + 1, r);
    
    st[id].val = min(st[id*2].val, st[id*2+1].val);
    st[id].cnt = st[id*2].cnt + st[id*2+1].cnt;
}

void Dfs(int u)
{
    if (v[u]) return;
    v[u] = 1;
    num[u] = ++p;
    pos[p] = u;
    for (int i = 0; i < (int)e[u].size(); i++)
    {
        int v = e[u][i];
        Dfs(v);
    }
    last[u] = p;
}

void Down(int id)
{
    int tmp = st[id].lazy;
    st[id*2].lazy += tmp;
    st[id*2+1].lazy += tmp;
    st[id*2].val -= tmp;
    st[id*2+1].val -= tmp;
    st[id].lazy = 0;
}

int Query(int id, int l, int r, int i, int j)
{
    if (l > j || r < i) return 0;
    
    if (l == r)
    {
        if (st[id].val > 0)
			return st[id].cnt;
        st[id] = dmcd;
        return 0;
    }
    
    int m = (l + r) / 2;
    Down(id);
    
    if (l >= i && r <= j)
    {
        if (st[id].val <= 0)
		{
			int m = (l + r) / 2;
			Query(id*2, l, m, i, j);
			Query(id*2 + 1, m + 1, r, i, j);

			st[id].val = min(st[id*2].val , st[id*2+1].val);
			st[id].cnt = st[id*2].cnt + st[id*2+1].cnt;
		}
		return st[id].cnt;
    }

    int t1 = Query(2*id, l, m, i, j);
    int t2 = Query(2*id+1, m + 1, r, i, j);

    st[id].val = min(st[2*id].val, st[2*id+1].val);
    st[id].cnt = st[2*id].cnt + st[2*id+1].cnt;
    return t1 + t2;
}

void Update(int id, int l, int r, int i, int j, int v)
{
    if (l > j || r < i) return;
    
    if (l >= i && r <= j)
    {
        st[id].lazy += v;
        st[id].val -= v;
        return;
    }
    
    Down(id);
    
    int m = (l + r) / 2;
    Update(id*2, l, m, i, j, v);
    Update(id*2+1, m+1, r, i, j, v);
    
    st[id].val = min(st[id*2].val, st[id*2+1].val);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    dmcd.val = 1000000000;
    
    for (int i = 1; i <= n; i++)
    {
        int x,c;
        cin >> x >> c;
        e[c].push_back(i);
        d[i] = x;
    }
    p = -1;
    Dfs(0);
    Build(1, 1, n);

    int test, k;
    cin >> test;
    while(test--)
    {
        cin >> k;
        if (k == 2)
        {
            int a;
            cin >> a;
            int cnt = Query(1, 1, n, num[a] + 1, last[a]);
            cout << cnt << "\n";
        }
        else
        {
            int a, val;
            cin >> a >> val;
            Update(1, 1, n, num[a] + 1, last[a], val);
        }
    }
    return 0;
}
