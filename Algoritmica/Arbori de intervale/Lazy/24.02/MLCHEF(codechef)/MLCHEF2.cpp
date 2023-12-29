#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;


#define MX 100005
vector<int> V[MX];
int health[MX];
int arr[MX], start[MX], final[MX], indx;
int n;

int minm[4*MX], lazy[4*MX];
int cnt[4*MX];

void DFS(int x)
{
	arr[indx++] = x;
	start[x] = indx - 1;

	for(const int y : V[x])
		DFS(y);
	
	final[x] = indx - 1;
}

void update(int x, int L, int H, int lo, int hi, int val)
{
	if (hi < L || H < lo) return;

	if (lo <= L && H <= hi)
	{
		lazy[x] += val;
		minm[x] -= val;
		return;
	}

	if (lazy[x])
	{
		lazy[x*2] += lazy[x];
		lazy[x*2+1] += lazy[x];

		minm[x*2] -= lazy[x];
		minm[x*2+1] -= lazy[x];

		lazy[x] = 0;
	}

	int M = (L + H)/2;
	update(x*2, L, M, lo, hi, x);
	update(x*2 + 1, M + 1, H, lo, hi, x);

	minm[x] = min(minm[x*2] , minm[x*2+1]);
}

void build(int x, int L, int H)
{
	if (L == H)
	{
		lazy[x] = 0;
		minm[x] = health[arr[L]];
		cnt[x] = 1;

		return;
	}

	int M = (L + H)/2;

	build(x*2, L, M);
	build(x*2 + 1, M + 1, H);

	minm[x] = min(minm[x*2] , minm[x*2+1]);
	cnt[x] = cnt[x*2] + cnt[x*2+1];
	lazy[x] = 0;
}

int query(int x, int L, int H, int lo, int hi)
{
	if(hi < L || H < lo) return 0;

	if (L == H)
	{
		if(minm[x] > 0) return cnt[x];

		minm[x] = 2000000000;
		return cnt[x] = 0;
	}

	if (lazy[x])
	{
		lazy[x*2] += lazy[x];
		lazy[x*2+1] += lazy[x];

		minm[x*2] -= lazy[x];
		minm[x*2+1] -= lazy[x];

		lazy[x] = 0;
	}

	if (lo <= L && H <= hi)
	{
		if (minm[x] <= 0)
		{
			int M = (L + H)/2;
			query(x*2, L, M, lo, hi);
			query(x*2 + 1, M + 1, H, lo, hi);

			minm[x] = min(minm[x*2] , minm[x*2+1]);
			cnt[x] = cnt[x*2] + cnt[x*2+1];
		}

		return cnt[x];
	}

	int M = (L + H)/2;
	int a = query(x*2, L, M, lo, hi);
	int b = query(x*2 + 1, M + 1, H, lo, hi);

	minm[x] = min(minm[x*2] , minm[x*2+1]);

	cnt[x] = cnt[x*2] + cnt[x*2+1];

	return a + b;
}

int main()
{
	int p, t, ans, q, a, x;

	scanf("%d", &n);
	
	for(int i = 1; i <= n; i++)
	{
		scanf("%d %d", &health[i], &p);
		V[p].push_back(i);
	}

	indx = 0;
	DFS(0);

	build(1, 0, n);

	scanf("%d", &q);

	while (q--)
	{
		scanf("%d", &t);
		if(t == 1)
		{
			scanf("%d %d", &a, &x);
			update(1, 0, n, start[a]+1, final[a], x);

		}
		else if(t == 2)
		{
			scanf("%d", &a);
			ans = query(1, 0, n, start[a]+1, final[a]);
			printf("%d\n", ans);
		}
	}

	return 0;
}
