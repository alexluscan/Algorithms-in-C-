/* Det Componentelor tare-conexe pt un G.O.
 * Algoritmul Plus-Minus 
 */ 
#include <fstream>
using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

const int N = 1001;
bool a[N][N];
int s[N];  // marcheaza nodurile vizitate pe graful G
int p[N];  // marcheaza nodurile vizitate pe graful Gt (transpus)

int n, m;
int ctc; // nr de comp tare-conexe

void CitesteGraf();
void Df(int x);
void Dft(int x); // pe graful transpus
void CompTareConexe();

int main()
{
	CitesteGraf();
	CompTareConexe();
	
	return 0;
}

void CompTareConexe() // O(m + n * n)
{
	for (int nod = 1; nod <= n; ++nod)
		if (!s[nod])
		{
			ctc++;
			Df(nod);
			Dft(nod);
			
			for (int i = 1; i <= n; ++i)
				if (s[i] == p[i] && s[i] == ctc)
					fout << i << ' ';
				else
					if (!s[i] || !p[i])
						s[i] = p[i] = 0;
			fout << '\n';
		}
}

void Df(int x) // O(m)
{
	s[x] = ctc;
	for (int y = 1; y <= n; ++y)
	{
		if (s[y] || !a[x][y]) continue;
		Df(y);
	}
}

void Dft(int x) // O(m)
{
	p[x] = ctc;
	for (int y = 1; y <= n; ++y)
	{
		if (p[y] || !a[y][x]) continue;
		Dft(y);
	}
}

void CitesteGraf()
{
	fin >> n >> m;
	int x, y;
	while (m--)
	{
		fin >> x >> y;
		a[x][y] = true;
	}
}

