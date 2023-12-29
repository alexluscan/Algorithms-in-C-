/* 
 * Se da o matrice a cu n x m valori numere intregi
 * Se da un punct de plecare (ip, jp) si unul de sosire (is, js)
 * Sa se gaseasca un drum de suma minima
 */ 

#include <iomanip>
#include <fstream>
#include <queue>
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

ifstream fin("labir.in");
ofstream fout("labir.out");

const int Inf = 0x3f3f3f3f,
	      di[] = {-1, -1, 0, 1, 1, 1, 0, -1},
	      dj[] = {0, 1, 1, 1, 0, -1, -1, -1};

using PI  = pair<int, int>;
using VI  = vector<int>;
using VVI = vector<VI>;

VVI a;     // valorile citite
int n, m, ip, jp, is, js;
VVI c;       // c[i][j] = suma minima de la  (ip, jp) la (i, j)

void Citeste();
void Lee();
bool Ok(int i, int j);
void Debug();

int main()
{
	Citeste();
	Lee();
	
	fout << c[is][js] << '\n';
	
	Debug();
}

#define iv (i + di[d])
#define jv (j + dj[d])


void Lee()
{
	c = VVI(n + 1, VI(m + 1, Inf));
	
	int i, j;
	queue<PI> Q;
	c[ip][jp] = a[ip][jp];
	Q.push({ip, jp});
	
	while (!Q.empty())
	{
		tie(i, j) = Q.front();
		Q.pop();
		
		for (int d = 0; d < 8; ++d)
			if (Ok(iv, jv) && c[iv][jv] > c[i][j] + a[iv][jv])
			{
				c[iv][jv] = c[i][j] + a[iv][jv];
				Q.push({iv, jv});
			}
	}
}

void Citeste()
{
	fin >> n >> m;
	
	a = VVI(n + 1, VI(m + 1));
	
	fin >> ip >>jp >> is >> js;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			fin >> a[i][j];
			
}

bool Ok(int i, int j)
{
	if (i < 1 || i > n || j < 1 || j > m) // in afara matricei
		return false;
		
	return true;
}

void Debug()
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
			fout << setw(3) << c[i][j];
		fout << '\n';
	}
}
