// prof. Constantin Galatan
#include <fstream>
#include <limits>
using namespace std;

#define IN    "kimberley.in"
#define OUT   "kimberley.out"

const int MAX_N = 51;         // nr maxim de sali
const int MAX_G = 101;        // nr maxim de galerii
const int MAX_M = 151;        // nr maxim de mineri

#define  MIN(a, b) ( (a) < (b) ? (a) : (b) )
#define  INF  numeric_limits<int>::max()
#define  TMP MAX_N + MAX_M
#define  viitor 1
#define  trecut 0

struct nod {
    int s;            // sala
    int t;            // timp
};

int C[MAX_N][MAX_N][2];       // C[i][j][1] - capacitatea tuturor arcelor (i, t) -> (j, t + 1), cu t = 1, 2, ..., N + M
                              // C[i][j][0] - capacitatea arcului (i, t) -> (j, t - 1)
int F[MAX_N][MAX_N][TMP][2];  // F[i][j][t][1] - fluxul pe arcul  (i, t) -> (j, t + 1)
                              // F[i][j][t][0] - fluxul pe arcul  (i, t) -> (j, t - 1)

int S, D, M;          // sursa, destinatie, nr de mineri
bool a[MAX_N][MAX_N]; // galeriile
int flow;
int N, G;             // nr de sali, nr de galerii
int R;                // capacitatea reziduala a unui drum de crestere intre (S, 0) si (D, T)
int T;                // timpul minim cerut

nod q[4*MAX_G*(MAX_N + MAX_M)];
nod pred[MAX_N][TMP];
bool sel[MAX_N][TMP];

void Read();
void Solve();
void BuildNetwork();
bool FindPath();
void Augment();
void Write();

int main()
{
	Read();
	BuildNetwork();
	Solve();
	Write();
}

void Solve()
{
    flow = 0, T = 0;
	while (flow < M )
        for (T++; flow < M && FindPath(); flow += R )
            Augment();
}

void Read()
{
	ifstream fin(IN);
	fin >> N >> G >> S >> D >> M;
	int x, y;
	for ( int i = 0; i < G; i++ )
	{
		fin >> x >> y;
		a[x][y] = a[y][x] = true;
 		a[x][x] = a[y][y] = true;      // pt ca exista arce (x, t) ->(x, t + 1)
	}
	fin.close();
}

void BuildNetwork()
{
    for (int t = 0; t < N + M; t++ )
        for (int i = 1; i <= N; i++ )
	    {
			for ( int j = 1; j <= N; j++ )
			{
				if ( !a[i][j] ) continue;
				C[i][j][viitor] = 1;    // arc intre nodurile (i, t) -> (j, t + 1)
				C[i][j][trecut] = 0;    // arc intre nodurile (i, t) -> (j, t - 1)
			}
			C[i][i][viitor] = INF;      // arc intre nodurile (i, t) -> (i, t + 1)
         }
}

bool FindPath() // cauta un drum de crestere intre nodul initial (S, 0) si cel final (D, T)
{
    memset(sel, 0, sizeof(sel));
    int p(0), u(0);
    int i, t;
    R = INF;
    q[u].s = S;
    q[u].t = 0;

    while (p <= u)
    {
        i = q[p].s;
        t = q[p++].t;

        for ( int j = 1; j <= N; j++ )
        {
			if ( !a[i][j] ) continue;

			if ( !sel[j][t+1] && F[i][j][t][viitor] < C[i][j][viitor] && t + 1 <= T )  // arc spre viitor
			{                                                 // acopera si cazul j == i (bucla pe i spre viitor)
                sel[j][t+1] = true;
                q[++u].s = j;
                q[u].t = t + 1;
                pred[j][t+1].s = i;
                pred[j][t+1].t = t;
                R = MIN(R, C[i][j][viitor] - F[i][j][t][viitor]);
                if (j == D and t + 1 == T)
                  return true;
			}
				                                             // acopera si cazul j == i  (bucla pe i spre trecut)
			if ( !sel[j][t-1] && F[i][j][t][trecut] < 0 )    // spre trecut
			{
                sel[j][t-1] = true;
                q[++u].s = j;
                q[u].t = t - 1;
                pred[j][t-1].s = i;
                pred[j][t-1].t = t;
                R = MIN(R, -F[i][j][t][trecut]);
			}
		}
	}
	return false;
}

void Augment()                 // modifica fluxul pe drmul de ameliorare gasit
{
	int i, tmp;

	for ( int j = D, t = T; j != S || t != 0; j = i, t =  tmp)
	{
		i = pred[j][t].s;
		tmp = pred[j][t].t;
		if ( tmp + 1 == t )    // (i, tmp)->(j, t) arc spre viitor
			F[i][j][tmp][viitor]   += R,
			F[j][i][tmp+1][trecut] -= R;
		else // tmp - 1 == t
			F[i][j][tmp][trecut]   += R,
			F[j][i][tmp-1][viitor] -= R;
	}
}

void Write()
{
	ofstream fout(OUT);
	fout << T << '\n';
	fout.close();
}
