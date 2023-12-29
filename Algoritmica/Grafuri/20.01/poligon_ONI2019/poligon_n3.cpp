#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#define x first
#define y second
using namespace std;
/*ifstream fin("poligon.in");
ofstream fout("poligon.out");*/
using ld  = long double;
using VD  = vector<ld>;
using VVD = vector<VD>;
using PII = pair<int, int>;
using VP  = vector<PII>;
int p, T, n; 
VVD c;
VP v;
inline ld dist(PII a, PII b)
{
	long long c = (a.x - b.x) * (a.x - b.x), d = (a.y - b.y) * (a.y - b.y);
	ld e = sqrt(c + d);
	return e;
}
int main()
{
	#define fin cin
	#define fout cout
	fin >> p >> T;
	for (int t = 1; t <= T; ++t)
	{
		fin >> n;
		c = VVD(n + 2, VD(n + 2));
		v = VP(n + 2);
		for (int i = 1; i <= n; ++i)
			fin >> v[i].x >> v[i].y;
		for (int i = 1; i <= n; ++i)
			c[i][i] = c[i][i+1] = 0;
		for (int l = 2; l < n; ++l)
			for (int i = 1; i + l <= n; ++i)
			{
				int j = i + l;
				c[i][j] = ld(1000);
				for (int k = i + 1; k <= j; ++k)
					c[i][j] = min(c[i][j], c[i][k] + c[k][j] + min(dist(v[k], v[i]), dist(v[k], v[j])));
			}
		c[1][n] += dist(v[1], v[n]);
		fout << fixed << setprecision(12) << c[1][n] << '\n';
	} 
	/*fin.close();
	fout.close();*/
	return 0;
}
