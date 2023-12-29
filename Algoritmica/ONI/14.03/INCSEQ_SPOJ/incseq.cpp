#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <cstring>
#include <cassert>
#include <queue>
#include <set>
#include <numeric>
#include <stack>
using namespace std;
#define mp make_pair
#define INF (int)1e9
#define X first
#define Y second
#define REP(i, n) for(int i=0; i < n; i++)
#define FOR(i, a, b) for(int i=a; i < b; i++)
#define fill(a, x) memset(a, x, sizeof(a))
#define all(c) c.begin(), c.end()
#define sz(x)    ((int) x.size())
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
#define MAXN 100010
#define MOD 5000000

int tree[51][MAXN];
int arr[MAXN];

bool cmp (int a, int b) { return arr[a] < arr[b]; }

int Query(int sel, int idx) 
{
	ll sum = 0;
	while(idx > 0) {
		sum = (sum + tree[sel][idx]) % MOD;
		idx -= (idx & -idx);
	}
	return (int) sum;
}

void Update(int sel, int i, int val) 
{
	// printf("upd: %d %d %lld\n", sel, idx, val);
	while (; i < MAXN; i += (i & -i)) 
	{
		ll temp = ((ll) tree[sel][i] + (ll) val) % MOD;
		tree[sel][i] = (int) temp;
	}
}

int main() 
{
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; ++i) 
		scanf("%d", &arr[i]);
	
	fill(tree, 0);
	
	int dp[51];
	for (int i = 0; i < n; i++) 
	{
		// fill(dp, 0);
		for(int j = 0; j < k - 1; ++j) 
			dp[j] = Query(j, arr[i]);
			
		Update(0, arr[i] + 1, 1);
		for (int j = 1; j < k; ++j)
			Update(j, arr[i] + 1, dp[j - 1]);
	}
	
	ll cnt = Query(k - 1, MAXN - 1);
	printf("%lld\n", cnt);
	return 0;
}
