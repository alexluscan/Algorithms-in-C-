#include <fstream>
using namespace std;

ifstream fin ("drumuri.in");
ofstream fout ("drumuri.out");

const int maxN = 255, maxM = 10005, MOD = 31607;
int dp[2][maxN][maxM], n, m, k, lg, ans;
bool jt[maxN][maxN], ln;


int main()
{
	int x, y;
	fin >> n >> m >> k >> lg;
	
	for (int i = 1; i <= m; ++i)
	{
		fin >> x >> y;
		jt[x][y] = true;
	}
	
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			for (int d = 0; d <= m; ++d)
				dp[ln][j][d] = 0;
				
		if (i == 1) 	dp[0][1][jt[1][1]] = 1;
		
		for (int j = 1; j <= n; ++j)
		{
			if (i != 1 || j != 1)
				for (int d = m; d >= jt[i][j]; --d)
					dp[ln][j][d] = (dp[!ln][j][d - jt[i][j]] + dp[ln][j - 1][d - jt[i][j]]) % MOD;
			if (i + j - 1 == lg)
				ans = (ans + dp[ln][j][k]) % MOD;
		}
		ln = !ln;
	}
				
	fout << ans;
}
