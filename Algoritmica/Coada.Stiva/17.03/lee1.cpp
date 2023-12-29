/* Problema labirintului
 * Se da o matrice n x m cu obstacole (# - obstacol, '_' - liber)
 * Se da un punct de plecare (ip, jp) si unul de sosire (is, js)
 * Sa se gaseasca lungimea celui mai scrur drum de la plecare la sosire
 */ 

#include <iomanip>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

ifstream fin("labir.in");
ofstream fout("labir.out");

struct Cel {
	int i, j;
};

const int Dim = 301, Inf = 0x3f3f3f3f,
	      di[] = {-1, -1, 0, 1, 1, 1, 0, -1},
	      dj[] = {0, 1, 1, 1, 0, -1, -1, -1};

char L[Dim][Dim];
int n, m, ip, jp, is, js;
int c[Dim][Dim];       // c[i][j] = dist minima de la (ip, jp) la (i, j)

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

void Lee()
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			c[i][j] = Inf;
	
	int i, j, iv, jv;
	queue<Cel> Q;
	c[ip][jp] = 0;
	Q.push({ip, jp});
	
	while (!Q.empty())
	{
		i = Q.front().i;
		j = Q.front().j;
		Q.pop();
		
		for (int d = 0; d < 8; ++d)
		{
			iv = i + di[d];
			jv = j + dj[d];
			
			if (Ok(iv, jv) && c[iv][jv] > c[i][j] + 1)
			{
				c[iv][jv] = c[i][j] + 1;
				Q.push({iv, jv});
			}
		}
	}
}

void Citeste()
{
	fin >> n >> m;
	fin >> ip >>jp >> is >> js;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			fin >> L[i][j];
			
}

bool Ok(int i, int j)
{
	if (i < 1 || i > n || j < 1 || j > m) // in afara matricei
		return false;
		
	if (L[i][j] == '#')
		return false;
		
	return true;
}

void Debug()
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
			if (L[i][j] == '#')
				fout << " []";
			else
				if (c[i][j] == Inf)
					fout << " oo";
				else
					fout << setw(3) << c[i][j];
		fout << '\n';
	}
}
