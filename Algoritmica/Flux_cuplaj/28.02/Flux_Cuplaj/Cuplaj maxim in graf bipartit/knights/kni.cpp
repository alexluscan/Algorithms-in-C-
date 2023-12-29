#include <cstdio>
#include <vector>
using namespace std;

int n, m;
typedef vector<int> VI;
vector<VI > ai1, aj1, ai2, aj2, sel;
vector<vector<bool> > obst;
int nr;
int aux;

const int di[] = {-2, -1, 1, 2, 2, 1, -1, -2},
          dj[] = {1, 2, 2, 1, -1, -2, -2, -1};
          
void Read();
void Solve();
void Write();
bool Cuplaj(int i, int j);
bool Ok(int i, int j);

int main()
{
	Read();
	Solve();
	Write();
	return 0;
}

void Read()
{
	FILE *fin = fopen("kni8.in", "r");
	fscanf(fin, "%d%d", &n, &m);
	
	ai1.resize(n+2);
	ai2.resize(n+2);
	aj1.resize(n+2);
	aj2.resize(n+2);
	obst.resize(n+2);
	sel.resize(n+2);
	for (int i = 0; i <= n; i++)
	{
		ai1[i].resize(n+2);
		ai2[i].resize(n+2);
		aj1[i].resize(n+2);
		aj2[i].resize(n+2);
		obst[i].resize(n+2);
		sel[i].resize(n+2);
	}
	
	int ii, jj;
	for (int i = 1; i <= m; i++)
	{
		fscanf(fin, "%d%d", &ii, &jj);
		obst[ii][jj] = true;
	}
	fclose(fin);
}

void Solve()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!obst[i][j])
				if (!((i+j)&1) && !ai1[i][j])
				{
					++aux;
					if (!sel[i][j] 
						&& Cuplaj(i, j)) nr++;
				}
}

#define iv (i + di[d])
#define jv (j + dj[d])

bool Cuplaj(int i, int j)
{
	for (int d = 0; d < 8; d++)
	{
		if (!Ok(iv, jv)) continue;
		sel[iv][jv] = aux;
		if (!ai2[iv][jv] || Cuplaj(ai2[iv][jv], aj2[iv][jv]) )
		{
			ai1[i][j] = iv;
			aj1[i][j] = jv;
			ai2[iv][jv] = i;
			aj2[iv][jv] = j;
			return true;
		}	
	}
	sel[i][j] = aux;       
	return false;
}

bool Ok(int i, int j)
{
	if ( i < 1 || i > n || j < 1 || j > n) return false;
	if (obst[i][j]) return false;
	if (sel[i][j] == aux) return false;
	return true;
}

void Write()
{
	FILE *fout = fopen("kni.out", "w");
	int solutie = n*n - m - nr;
	fprintf(fout, "%d\n", solutie);
	fclose(fout);
}
