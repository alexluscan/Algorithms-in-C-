// Alg. lui Prim
// Det arborelui minim de acoperire (minimum spanning tree)
// ( Arborele Partial de Cost Minim  - APM )
#include <fstream>
using namespace std;

const int DIM = 100;
const int INFINIT = 10000;
int a[DIM][DIM];


int m, n;
int costmin;    // costul minim al arborelui minim de acoperire
int tata[DIM];  // sirul predecesorilor (retine arborele )
int s[DIM];     // sir caracteristic (selecteaza nodurile)
ofstream fout("graf.out");

void Read();
void Parcurge();
void Prim(int);
void Add(int a, int b, int cost);

int main()
{
	Read();
	Prim(1);

	fout.close();
	return 0;
}

void Read()
{
	ifstream fin("graf.in");
	int v1, v2, cost;
	fin >> n >> m;

	for ( int i = 1; i <= m; i++ )
	{
		fin >> v1 >> v2 >> cost;
		a[v1][v2] = a[v2][v1] = cost;
	}
	fin.close();
}


void Prim(int nod)
{
	int tv, v;
	int u = 1;   // poz ultimului nod din coada
	int q[100];  // coada (retine nodurile selectate (care fac parte din arbore)
	q[1] = nod;
	s[nod] = 1;

	while ( u < n ) // cat timp nu am selectat toate nodurile
	{
		int min = INFINIT;
		for ( int i = 1; i <= u; i++ )  // i poz in sirul q
		{
			for ( int j = 1; j <= n; j++ )
				if ( a[q[i]][j] < min && !s[j] && a[q[i]][j] ) // a[i][j] == 0 nu exista muchie
				{
					min = a[q[i]][j];
					v = j;      // retin vecinul
					tv = q[i];  // tata vecinului este
				}
		}
		costmin += min;   // adaug la arbore costul muchiei
		fout << tv << " " << v << " " << min << endl;
		s[v] = 1;
		tata[v] = tv;
		q[++u] = v;
	}
	fout << "costul minim : " << costmin << "\n";
}






