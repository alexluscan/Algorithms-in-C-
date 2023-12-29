#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin ("submatrix.in");
ofstream fout ("submatrix.out");

const int dim = 1005;
int n, l[dim][dim], m;
bool ma[dim][dim];

int main()
{
	fin >> n;
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			fin >> ma[i][j];
			if (ma[i][j])
				l[i][j] = min(l[i][j - 1], min(l[i - 1][j - 1], l[i - 1][j])) + 1;
			else
				l[i][j] = 0;
			m = max(m, l[i][j]);
		}
		
	fout << m;
}
