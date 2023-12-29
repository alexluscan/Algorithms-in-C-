// Time complexity O(n^3)
// OK
#include <stdio.h>
#include <vector>
#include <string.h>
#include <time.h>

using namespace std;

const int MaxN = 128;
vector<int> adj[MaxN];  // arborele
int tmin[MaxN][MaxN];   // tmin[x][k] nr min de orase plasate intr-un judet din subarb cu rad in x, 
                        //  a.i. k orase (inclusiv x) nu sunt plasate inca
int nr[MaxN]; // nr[x] de noduri din subarborele cu radacina in x

int n, K;

void ReadData() 
{
	scanf ("%d%d", &n, &K);
	int a, b;
	for (int i = 1; i < n; i++)
	{
		scanf ("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}

int v[MaxN]; 
int C[2 * MaxN];

void Df(int x)
{
	v[x] = 1;
	nr[x] = 1;
	for (const int& f : adj[x])
		if ( !v[f] ) 
			Df(f), nr[x] += nr[f]; // rezolv pentru fii mai intai

	memset(tmin[x], 1, sizeof(tmin[x])); // setat pe infinit

   tmin[x][1] = 0;  // daca e frunza (si nu o plasez)
                    // daca nu e frunza    
	for (const int& f : adj[x])
		if (v[f] == 2) // asa evit sa merg spre tata
		{
			memset(C, 1, sizeof(C));   //  vector auxiliar setat pe infinit
			for (int j = 0; j <= nr[x]; j++)      // in x am j noduri neplasate
				for (int k = 0; k <= nr[f]; k++)   // in fiul f am k noduri neplasate
				
					if (j + k <= n)        // cream un alt judet (subarbore care-l contine pe x)
					{			              // din configuratia (f, k) sau le adaugam la alte noduri libere(neplasate) 
								              // si trecem in configuratia  (x, j + k)
						
						// am un arbore cu j noduri din x si k din fiu, care nu este partitionat pe judete
						C[j + k] = min(C[j + k], max(tmin[x][j], tmin[f][k]));
						
						                   // plasez cel k noduri intr-un singur arbore separat - nu combin j si k 
						if ( k >= K)       // daca k noduri din fiu pot forma singure un arbore
							C[j] = min(C[j], max({tmin[x][j], tmin[f][k], k}));					
					}
			memcpy(tmin[x], C, sizeof(C));
		}
	v[x] = 2; // am rezolvat x
}

void WriteData()
{
	int T = 1 << 20;
	for (int i = K; i <= n; i++)
		T = min(T, max(tmin[1][i], i));

	printf ("%d\n", T);
}

int main()
{
//    long T1=clock();

	freopen ("9-JUDETE.IN", "r", stdin);
	freopen ("judete.out", "w", stdout);

	ReadData();
	Df(1);
	WriteData();
    
//	printf ("%lf\n",(double)((double)clock()-T1)/CLK_TCK);
	return 0;
}

