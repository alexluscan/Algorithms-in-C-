#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility>
#include <numeric>
#include <complex>

using namespace std;

const int MOD = 1000003;
vector <int> a, b;
int n, N;
int d;

int store[31][32768];
bool seen[31][32768];

int memo(int k, int mask)
{
	if (seen[k][mask]) return store[k][mask];
	int ans = 0;

	vector <bool> bottom(n, false), top(n, false);
	vector <int> kills(n);
	for (int i = 0; i < d; i++)
	if ((mask>>i)&1)
	{
		bottom[b[i]] = true;
		top[a[i]] = true;
		kills[a[i]] |= 1<<i;
	}
	int nbottom = count(bottom.begin(), bottom.end(), true);
	vector <int> tops;
	for (int i = 0; i < n; i++)
		if (!bottom[i] && top[i])
		  tops.push_back(i);
	int ntop = tops.size();
	int nleft = k - nbottom - ntop;
	if (nleft >= 0)
	{
		for (int j = 0; j < ntop; j++)
			ans += memo(k-1, mask&~kills[tops[j]]);
		if (nleft > 0)
			ans += nleft * memo(k-1, mask);
	}
	seen[k][mask] = true;
	return store[k][mask] = ans % MOD;
}

class RaceOrdering {
  public:
  int countOrders(int n0, vector <int> first, vector <int> second) {
    
    a = first; b = second;
    d = a.size(); n = n0;
    store[0][0] = 1;
    seen[0][0] = true;
    return memo(n, (1<<d)-1);

  }
};

