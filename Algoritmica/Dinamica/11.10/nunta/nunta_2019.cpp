#include <fstream>
#include <cmath>
using namespace std;

ifstream fin("nunta.in");
ofstream fout("nunta.out");

const int N = 55, K = 25;
bool nr[N][N][K];

int n, v[N];

int main() 
{
	fin >> n;
	
	for (int i = 1; i <= n; ++i)
		fin >> v[i];
		
	for (int i = 1; i <= n; ++i)
		nr[i][i][v[i]] = true;
		
	for (int l = 1; l <= n; ++l)
		for (int i = 1; i + l <= n; ++i)
		{
			int j = i + l;
			for (int k = i; k <= j; ++k)
				for (int u1 = 0; u1 <= 20; ++u1)
					if (nr[i][k][u1])
						for (int u2 = 0; u2 <= 20; ++u2)
							if (nr[k + 1][j][u2])
								nr[i][j][abs(u2 - u1)] = true;
		}
		
	int ans = 0;
		
	for (int i = 0; i <= 20; ++i)
		ans += nr[1][n][i];
		
	fout << ans << '\n';
	
	for (int i = 0; i <= 20; ++i)
		if (nr[1][n][i])
			fout << i << ' ';
			
	fin.close();
	fout.close();
	
	return 0;

}
