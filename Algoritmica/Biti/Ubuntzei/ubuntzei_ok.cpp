#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

ifstream fin("ubuntzei.in");
ofstream fout("ubuntzei.out");

struct Pair {
	int dist, nod;

	bool operator < (const Pair& p) const
	{
		return dist > p.dist;
	}
};

using VI = vector<int>;
using VVI = vector<VI>;
using PII = pair<int, int>;

const int Inf = 0x3f3f3f3f;
VI C, d;     // d - Dijkstra din nodul sursa, C - orasele speciale
VVI D, dp;   // D[i] - vector distantele  minime de la C[i] la restul nodurilor
             // dp[i][j] - dist minima a unui drum care porneste din 1 si se termina cu cu nodul C[j],
             //            daca drumul contine o submultime i de noduri din cele speciale, si j e inclus in i
int n, m, K;
vector<vector<PII>> G;

void Read();
void Dijkstra(int S, VI& d);

int main()
{
	Read();
	Dijkstra(1, d);

	if (K == 0)
	{
		fout << d[n] << '\n';
	}
	else
	{
		for (int i = 0; i < K; ++i)
			Dijkstra(C[i], D[i]);

		// initializare
		dp = VVI(1 << K, VI(K, Inf));

		for (int j = 0; j < K; ++j)
			dp[1 << j][j] = d[C[j]];          // dp[1 << j][j] - dist minima de la 1 la C[j], daca trec obligatoriu numai prin nodul C[j]

		// dinamica
		for (int i = 1; i < (1 << K); ++i)    // pt fiecare submultime i de pozitii din sirul nodurilor {C[0], ..., C[K - 1] }
			for (int j = 0; j < K; ++j)
				if (i & (1 << j))             // masca i contine bitul j
					for (int k = 0; k < K; ++k)
						if ( !(i & (1 << k)) ) // si masca i NU contine bitul k
							dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + D[j][C[k]]);

		int res(Inf);
		for (int i = 0; i < K; ++i)
			res = min(res, dp[(1 << K) - 1][i] + D[i][n]);

		fout << res << '\n';

	}
}

void Dijkstra(int S, VI& d)
{
	queue<Pair> Q;
	d = VI(n + 1, Inf);
	d[S] = 0; Q.push({0, S});

	for (int x, dx, y, w; !Q.empty(); )
	{
		x = Q.front().nod; dx = Q.front().dist;
		Q.pop();
		if ( d[x] < dx )
			continue;
		for (const auto& e : G[x])
		{
			y = e.first; w = e.second;

			if ( d[y] > d[x] + w )
			{
				d[y] = d[x] + w;
				Q.push({d[y], y});
			}
		}
	}
}

void Read()
{
	fin >> n >> m >> K;
	G = vector<vector<PII>>(n + 1);
	C = VI(K);  D = VVI(K);

	for (int i = 0; i < K; ++i)
		fin >> C[i];

	for (int i = 1, x, y, w; i <= m; ++i)
	{
		fin >> x >> y >> w;
		G[x].push_back({y, w});
		G[y].push_back({x, w});
	}
	fin.close();
}
