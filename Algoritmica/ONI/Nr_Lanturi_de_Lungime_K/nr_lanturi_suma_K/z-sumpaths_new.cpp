// Nr total de lanturi de suma K
#include <fstream>
#include <vector>
using namespace std;
using VP = vector<pair<int,int>>;
using VVP = vector<VP>;
using VI = vector<int>;

ifstream fin("arb.in");
ofstream fout("arb.out");

const int MaxN = 50024, MaxM = 104, MOD = 321555123LL;
bool vz[MaxN];
long long ans;
int n, K;
VVP G;

VI Dfs(int x);

int main() 
{
	int x, y, w;
	fin >> n >> K;
	G = VVP(n + 1);
	for (int i = 1; i < n; ++i)
	{
		fin >> x >> y >> w;
		G[x].emplace_back(y, w);
		G[y].emplace_back(x, w);
	}
	
	Dfs(1);
	fout << ans;
	
	return 0;
}

VI Dfs(int x)
{
	vz[x] = true;
	VI X(K + 1);
	X[0] = 1;
	for (const auto& p : G[x])
	{
		auto& [y, w] = p;
		if (!vz[y])
		{
			VI S = Dfs(y);
			for (int i = 0; i <= K - w; ++i)
				ans = (ans + 1LL * X[i] * S[K - w - i]) % MOD;
			for (int i = w; i <= K; ++i)
			{
				X[i] += S[i - w];
				if (X[i] > MOD)
					X[i] -= MOD;
			}
		}
	}
	return X;
}
