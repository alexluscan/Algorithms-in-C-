#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin ("smax.in");
ofstream fout ("smax.out");

const int dim = 1005;
int n, b[dim][dim], s, m, ma;

int main()
{
	int x;
	fin >> n >> m;
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			fin >> x;
			b[i][j] = b[i - 1][j] + x;
		}
	int sum_col = 0;
	for (int i1 = 1; i1 <= n; ++i1, s = 0)
		for (int i2 = i1; i2 <= n; ++i2)
			for (int j = 1; j <= m; ++j)
			{
				sum_col = b[i2][j] - b[i1 - 1][j];
				if (sum_col + s >= 0)
					s += s;
				else
					s = 0;
				ma = max(ma, s);
			}
			
	fout << ma;		
}
