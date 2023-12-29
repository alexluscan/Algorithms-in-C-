#include <iostream>
#include <algorithm>

const int MaxN = 4e3 + 20, maxK = 8e2 + 20;
int C[maxK][MaxN]; // C[g][i] = costl minim sa grupez primele i persoane
                   // in g grupuri   
int sum[MaxN][MaxN];  // sum[i][j] - suma in drept (1, 1) (i, j)
int N, K;

void DEI(int g, int l, int r, int optL, int optR)
{
	if (l > r) return;
	
	int m = (l + r) / 2;  // vom rezolva poz optimului
	                      // in intervalul [l, m]
	int opt;
	int tmp;
	int cmin = 1e9;
	for (int k = optL; k <= std::min(optR, m); ++k)
	{
		tmp = C[g - 1][k - 1] + sum[m][m] - sum[k - 1][m] - sum[m][k - 1] + sum[k -  1][k - 1];
		if (tmp < cmin)
		{
			cmin = tmp;
			opt = k;
		}
	}
	
	C[g][m] = cmin;
	DEI(g, l, m - 1, optL, opt);
	DEI(g, m + 1, r, opt, optR);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0);
	
	std::cin >> N >> K;
	
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			std::cin.get(),
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]
						+ (std::cin.get() - '0');
	
	for (int j = 1; j <= N; ++j)
		C[1][j] = sum[j][j];
		
	for (int g = 2; g <= K; g++)
		DEI(g, 1, N, 1, N);
		
	std::cout << C[K][N] / 2;
}
