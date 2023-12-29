#include <iostream>
using namespace std;
const int mod = 5000000;
int dp[10005][55], v[10005], n, K, res;
int main()
{
	cin >> n >> K;
	for (int i = 1; i <= n; ++i)
		cin >> v[i];
	dp[1][1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		dp[i][1] = 1;
		for (int j = 1; j < i; ++j)
			if (v[j] < v[i])
				for (int k = 1; k <= K; ++k)
				{
					dp[i][k + 1] += dp[j][k];
					if (dp[i][k + 1] > mod)
						dp[i][k + 1] -= mod;
				}
	}
	
	for (int i = K; i <= n; ++i)
	{
		res += dp[i][K];
		if (res > mod)
			res -= mod;
	}
	cout << res;
	return 0;
}

