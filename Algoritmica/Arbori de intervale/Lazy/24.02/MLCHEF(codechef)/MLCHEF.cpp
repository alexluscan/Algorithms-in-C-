#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define eb emplace_back
#define mt make_tuple

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int N = 100010;
const int oo = 0x3f3f3f3f;

int tree[4*N], lazy[4*N];
int a[N];

int build(int start, int end, int pos)
{
	if (start == end)
		return tree[pos] = a[start];
	int mid = (start+end)/2;
	int l = build(start, mid, 2*pos + 1);
	int r = build(mid+1, end, 2*pos + 2);
	return tree[pos] = min(l, r);
}

void prop(int start, int end, int pos)
{
	if (lazy[pos] == 0)
		return;
	
	tree[pos] += lazy[pos];
	if (start != end)
	{
		lazy[2*pos + 1] += lazy[pos];
		lazy[2*pos + 2] += lazy[pos];
	}
	lazy[pos] = 0;
}

int update(int start, int end, int ustart, int uend, int val, int pos)
{
	prop(start, end, pos);
	if (ustart > end or uend < start)
		return tree[pos];
	if (start >= ustart and end <= uend)
	{
		lazy[pos] = val;
		prop(start, end, pos);
		return tree[pos];
	}
	int mid = (start+end)/2;
	int l = update(start, mid, ustart, uend, val, 2*pos + 1);
	int r = update(mid+1, end, ustart, uend, val, 2*pos + 2);
	return tree[pos] = min(l, r);
}

int find(int start, int end, int qstart, int qend, int pos)
{
	if (qstart > end or qend < start)
		return -1;

	prop(start, end, pos);

	if (tree[pos] > 0)
		return -1;
	
	if (start == end)
		return start;

	int mid = (start+end)/2;

	if (start >= qstart and end <= qend)
	{
		prop(start, mid, 2*pos + 1);
		if (tree[2*pos + 1] <= 0)
			return find(start, mid, qstart, qend, 2*pos + 1);
		return find(mid+1, end, qstart, qend, 2*pos + 2);	
	}

	int l = find(start, mid, qstart, qend, 2*pos + 1);
	if (l != -1)
		return l;
	return find(mid+1, end, qstart, qend, 2*pos + 2);
}

int h[N];
vector<int> g[N];
vector<int> ln;
int inter[N][2], t;

void dfs(int u)
{
	ln.pb(u);
	inter[u][0] = t++;
	for (int v : g[u])
		dfs(v);
	inter[u][1] = t-1;
}

int ft[N];
int query(int pos)
{
	int ret = 0;
	while (pos)
	{
		ret += ft[pos];
		pos -= pos&-pos;
	}
	return ret;
}

void upd(int pos, int val)
{
	while (pos < N)
	{
		ft[pos] += val;
		pos += pos&-pos;
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int p;
		scanf("%d %d", h+i, &p);
		g[p].pb(i);
	}
	h[0] = oo;
	ln.pb(-1);
	t = 1;
	dfs(0);
	for (int i = 1; i <= n+1; i++)
		a[i] = h[ln[i]];
	build(1, n+1, 0);
	int q;
	scanf("%d", &q);
	while (q--)
	{
		int type;
		scanf("%d", &type);
		if (type == 1)
		{
			int u, x;
			scanf("%d %d", &u, &x);
			int l = inter[u][0]+1, r = inter[u][1];
			if (r < l) continue;
			update(1, n+1, l, r, -x, 0);
		}
		else
		{
			int u;
			scanf("%d", &u);
			int l = inter[u][0]+1, r = inter[u][1];
			
			if (r < l)
			{
				printf("0\n");
				continue;
			}

			int pos;
			while (pos = find(1, n+1, l, r, 0), pos != -1)
			{
				update(1, n+1, pos, pos, oo, 0);
				upd(pos, 1);
			}
			int ans = inter[u][1] - inter[u][0] - (query(inter[u][1]) - query(inter[u][0]));
			printf("%d\n", ans);
		}
	}
	return 0;
}

