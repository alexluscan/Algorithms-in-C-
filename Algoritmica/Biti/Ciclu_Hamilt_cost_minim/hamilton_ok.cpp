// ok - infoarena
// Ciclu hamiltonian de cost minim
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ofstream fout("hamilton.out");

const int MaxS = 1 << 18, MaxN = 19, Inf = 0x3f3f3f3f;
int C[MaxS][MaxN];  // C[i][j] costul minim al unui lant elementar care se termina cu j si contine toate nodurile din submultimea i
typedef vector<int> VI;
VI G[MaxN];
int w[MaxN][MaxN], n, m;

void Read();

int main()
{
    Read();
	
	for (int mask = 0; mask < 1 << n; ++mask)
		for (int x = 0; x < n; ++x)
			C[mask][x] = Inf;
    C[1][0] = 0;
    for (int i = 0; i < 1 << n; ++i)     // pt fiecare subm de noduri din masca i
		for (int j = 0; j < n; ++j)
			if ( i & (1 << j) )         // daca nodul j se gaseste in submultimea i
				for (const int& k : G[j])
					if ( !(i & (1 << k)) ) // daca k nu e in subm i
						C[i | (1 << k)][k] = min(C[i | (1 << k)][k], C[i][j] + w[j][k]);
    
    
    int res = Inf;
    for (int j = 0; j < n; ++j)
		res = min(res, C[(1 << n) - 1][j] + w[j][0]); 
    
    if ( res < Inf )
		fout << res << '\n';
	else
		fout << "Nu exista solutie\n";
    return 0;
}
    
void Read()
{
	ifstream fin("hamilton.in");
	fin >> n >> m;
	
    for (int x = 0; x < n; ++x)
		for (int y = 0; y < n; ++y)
			w[x][y] = Inf;
	int x, y, cost;
	
	for (int i = 0; i < m; ++i)
	{
		fin >> x >> y >> cost;
		G[x].push_back(y);
		w[x][y] = cost;
	}
	fin.close();
}
