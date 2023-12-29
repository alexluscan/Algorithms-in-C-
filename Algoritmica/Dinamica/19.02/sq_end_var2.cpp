/* AC
 * 262 ms
 * 9 MB
 * 
 */ 
#include <climits>
#include <type_traits>
#include <vector>
#include <iostream>
#include <fstream>
#include <ranges>
#include <algorithm>
using namespace std;

#define int long long

int dp[105][10010];
int n, k;

using VI = vector<int>;


template <typename T, typename Compare = greater<T>> 
struct LiChaoTree {
	
	struct Line {
		T m, b;
		T operator()(T x) { return m * x + b; }
	};
	
	std::vector<Line> a;
	std::vector<T> xs;
	size_t N;
	Compare comp;
	
	static const T Inf = LLONG_MAX - 5;

	LiChaoTree(const std::vector<T>& x) : xs(x), N {1}
	{
		size_t k = xs.size() - 1;
		while (N < k) N <<= 1;
		
		while (xs.size() <= N  ) 
			xs.push_back(xs.back() + 1);

		if (is_same_v<Compare, less<T>>)
			a = vector<Line>(2 * N, Line({0, Inf}));
		else
			a = vector<Line>(2 * N, Line({0, 0}));
	}
	
	void insert(Line seg, int nd, int l, int r) 
	{
		if (l + 1 == r)  // m = l
		{
			if ( comp(seg(xs[l]), a[nd](xs[l])) ) // seg(xs[l]) < a[n](xs[l])
				a[nd] = seg;
			return;
		}
		
		int mid = (l + r) >> 1;;
		if(a[nd].m < seg.m) 
			swap(a[nd], seg);
			
		if ( comp(seg(xs[mid]), a[nd](xs[mid])) ) 
		{
			swap(a[nd], seg);
			insert(seg, 2 * nd, l, mid);
		}
		else 
			insert(seg, 2 * nd + 1, mid, r);
	}

	void insert(Line seg)
	{
		insert(seg, 1, 1, N);
	}
	
	T query(T x, int nd, int l, int r) 
	{
		if (l + 1 == r) return a[nd](x);

		int mid = (l + r) >> 1;
	
		if (x < xs[mid])  
		{
			if (is_same_v<Compare, greater<T>>)
				return max(a[nd](x), query(x, 2 * nd, l, mid));
			return min(a[nd](x), query(x, 2 * nd, l, mid));
		}
		else
		{
			if (is_same_v<Compare, greater<T>>)
				return max(a[nd](x), query(x, 2 * nd + 1, mid, r ));
			return min(a[nd](x), query(x, 2 * nd + 1, mid, r ));
		}
	}
	
	T query(T x)
	{
		x = xs[x];	
		return query(x, 1, 1, N);
	}
};


int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	
	cin >> n >> k;
	VI a(n + 1);
	for(int i = 1; i <= n; i++) 
		cin >> a[i];
	
	VI b(a);
	sort(b.begin() + 1, b.end());
	b.erase(unique(b.begin() + 1, b.end()), b.end());
	
	VI c(n + 1);
	for(int i = 1; i <= n; i++) 
		c[i] = lower_bound(b.begin() + 1, b.end(), a[i]) - b.begin();

    for (int i = 1; i <= n; ++i) 
		dp[1][i] = (a[i] - a[1]) * (a[i] - a[1]); 
		
    for (int j = 2; j <= k; ++j)
    {
        LiChaoTree<int, less<int>> lct {b};
      
        for (int i = j; i <= n; ++i)
        {
            lct.insert({-2 * a[i], a[i] * a[i] + dp[j - 1][i - 1]});
            dp[j][i] = lct.query(c[i]) + a[i] * a[i];
        }
    }
	
    cout << dp[k][n];
    
    return 0;
}
