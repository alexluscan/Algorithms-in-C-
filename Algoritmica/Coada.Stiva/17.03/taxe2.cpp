/* 
 * Se da o matrice a cu n x m valori numere intregi
 * Se da un punct de plecare (ip, jp) si unul de sosire (is, js)
 * Sa se gaseasca un drum de suma minima
 */ 

#include <iomanip>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

ifstream fin("taxe2.in");
ofstream fout("taxe2.out");

struct Cel {
	int i, j;
};

const int Dim = 101, Inf = 0x3f3f3f3f,
	      di[] = {-1, 0, 1, 0},
	      dj[] = {0, 1, 0, -1};

int a[Dim][Dim];   // valorile citite
int n, m, ip, jp, is, js, S;
int c[Dim][Dim];       // c[i][j] = suma minima de la  (ip, jp) la (i, j)

void Citeste();
void Lee();
bool Ok(int i, int j);
void Debug();

int main()
{
	Citeste();
	Lee();
	if (S >= c[is][js])
		fout << S - c[is][js];
	else
		fout << -1;

}

#define iv (i + di[d])
#define jv (j + dj[d])

void Lee()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			c[i][j] = Inf;
	
	int i, j;
	queue<Cel> Q;
	c[ip][jp] = a[ip][jp];
	Q.push({ip, jp});
	
	while (!Q.empty())
	{
		i = Q.front().i;
		j = Q.front().j;
		Q.pop();
		
		for (int d = 0; d < 4; ++d)
			if (Ok(iv, jv) && c[iv][jv] > c[i][j] + a[iv][jv])
			{
				c[iv][jv] = c[i][j] + a[iv][jv];
				Q.push({iv, jv});
			}
	}
}

void Citeste()
{
	fin >> S >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			fin >> a[i][j];
	ip = 1;
	jp = 1;
	js = n;
	is = n;
}

bool Ok(int i, int j)
{
	if (i < 1 || i > n || j < 1 || j > n) // in afara matricei
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
