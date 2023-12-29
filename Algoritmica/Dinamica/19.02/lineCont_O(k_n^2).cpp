#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

const int Inf = 1e9, MaxK = 105, MaxN = 10010;
int dp[MaxK][MaxN];
int A[MaxN];
int n, K;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
	cin >> n >> K;
    for (int i = 1; i <= n; ++i) 
		cin >> A[i];
		
    for (int i = 1; i <= n; ++i) 
		dp[1][i] = (A[i] - A[1]) * (A[i] - A[1]); // 1 grup
		
    for (int k = 2; k <= K; ++k)
        for (int i = k; i <= n; ++i)			
        {
			dp[k][i] = Inf;
			for (int j = 1; j <= i; ++j)
			{
				dp[k][i] = min(dp[k][i], dp[k - 1][j - 1] + (A[i] - A[j]) * (A[i] - A[j]));
			}
		}
		
    cout << dp[K][n];
    return 0;
}

/*
 * dp[k][i] = min(dp[k][i], dp[k - 1][j - 1] + (A[i] - A[j]) * (A[i] - A[j]));
 * dp[k][i] = min(dp[k][i], -2A[j] * A[i] + A[j]^2 + dp[k - 1][j - 1]  + A[i]^2);
 * 
 * y = m * x + b
 * m = -2A[j];
 * x = A[i] - valoarea pt care testam
 * b = A[j]^2 + dp[k - 1][j - 1]
 * 
 * m si b sunt valori specifice pozitiei j (depind de j)
 */ 
