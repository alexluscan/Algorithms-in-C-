#include <fstream>
#include <vector>
#include <bitset>
using namespace std;

const int NMAX = 1e4 + 1;
const int KMAX = 100;
const int MOD = 321555123LL;


ifstream fin("arb.in");
ofstream fout("arb.out");

using VP = vector <pair <int, int> >;
using VI = vector <int>;
using VVP = vector<VP>;

bitset <NMAX> used;

int n, k, x, y, c;
VVP G;

long long ans;

VI DFS(int node)
{
	used[node] = 1;
	
	VI X(k + 1);
	X[0] = 1;
	
	for (auto p : G[node])
	{
		auto& [y, w] = p;  // C++17
		if (used[y])
			continue;
		VI F = DFS(y);
		
		for (int i = 0; i <= k - w; ++i)
		{
			ans += 1LL * X[i] * F[k - i - w];
			ans %= MOD;
		}
		
		for (int i = w; i <= k; ++i)
		{
			X[i] += F[i - w];
			if (X[i] >= MOD)
			X[i] -= MOD;
		}
	}
	return X;
}

int main()
{
	fin >> n >> k;
	G = VVP(n + 1);
	 
	for (int i = 1; i < n; ++i)
	{
		fin >> x >> y >> c;
		G[x].emplace_back(y, c);
		G[y].emplace_back(x, c);
	}
	
	DFS(1);
	
	fout << ans << '\n';
	
	return 0;
}
