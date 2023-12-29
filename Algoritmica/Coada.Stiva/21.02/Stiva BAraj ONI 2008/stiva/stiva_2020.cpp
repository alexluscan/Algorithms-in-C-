#include <fstream>
#include <string>
using namespace std;

ifstream fin ("stiva.in");
ofstream fout ("stiva.out");

const int dim = 505;
int n, Min[dim][dim];

string s;

int main()
{
	int j;
	fin >> s; s = " " + s;
	n = s.size() - 1;
	
	for (int i = 1; i <= n; ++i)
		Min[i][i] = 1;
		
	for (int d = 1; d < n; ++d)
		for (int i = 1; i + d <= n; ++i)
		{
			j = i + d;
			Min[i][j] = 1 + Min[i][j - 1];
			
			for (int k = i; k < j; ++k)
				if (s[k] == s[j])
					Min[i][j] = min(Min[i][j], Min[i][k] + Min[k + 1][j - 1]);
		}
		
	fout << 2 * Min[1][n] + n;
}
