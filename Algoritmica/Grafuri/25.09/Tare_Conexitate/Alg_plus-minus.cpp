/* Determinarea componentelor Tare-Conexe
 * pr un Graf Orientat
 * Algoritmul Plus-Minus
 * 
 * O(n * n) 
 */ 
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin("graf.in");
ofstream fout("graf.out");

const int MaxN = 500;
bool a[MaxN][MaxN];  // matr de adiacenta
int succ[MaxN];      // succ[x] -> succesorii nodului x (accesibile din x)
int pred[MaxN];      // pred[x] -> predecesorii nodului x (nodurile din care se poate accesa x)
int nrc;             // nr de comp tare conexe
int n, m;            // noduri, arce

void CitesteGraf();
void CompTareConexe();
void Df(int x);
void DfT(int x);     // parcurgere pe graful Transpus

int main()
{
	CitesteGraf();
	CompTareConexe();
}  

void CitesteGraf()
{
	fin >> n >> m;
	int x, y;
	for (int i = 1; i <= m; ++i)
	{
		fin >> x >> y;
		a[x][y] = true;
	}
}

void CompTareConexe()
{
	for (int x = 1; x <= n; ++x)
		if (succ[x] == 0)
		{
			nrc++;
			Df(x);
			DfT(x);
			
			for (int y = 1; y <= n; ++y)
				if (succ[y] == pred[y] && succ[y] == nrc)
				{
					fout << y << ' ';
				}
				else
					if (succ[y] == 0 || pred[y] == 0)
						succ[y] = pred[y] = 0;
			
			fout << '\n';	
		}
}

void Df(int x)
{
	succ[x] = nrc;
	for (int y = 1; y <= n; ++y)
		if (a[x][y] && !succ[y])
			Df(y);
}

void DfT(int x)     // parcurgere pe graful Transpus
{
	pred[x] = nrc;
	for (int y = 1; y <= n; ++y)
		if (a[y][x] && !pred[y])
			DfT(y);
}

