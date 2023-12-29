// Arborele de acoperire minim
// - algoritmul lui Prim
// nu e necesara lista de adiacenta
// e OK pana acum ( de eliminat lista de vecini)
// O alta modificare care poate fi facuta: in coada de prioritate nu e obligatoriu sa retinem
// tot graful ci numai nodurile adicente in fiecare moment cu cele din arbore (vezi CLR mai ales desenul)
// E foarte important acest aspect

#include <fstream>
#include <iomanip>
using namespace std;

#define INFILE "prim.in"
#define OUTFILE "prim.out"
#define __DEBUG__

#define MAX 101
#define INFINIT 1000
#define LEFT(x) (2 * (x))

int n, m, c[MAX][MAX];      // ponderi
int H[MAX], nrh;            // min-HEAP-ul pastraeza nodurile in functie de key[]
int s,  key[MAX];  // sursa, key[i] - costul minim al muchiei care il uneste pe i de APM
int  sel[MAX];     // sel[i] = 1 daca i este in coada de prioritate(nu apartine inca APM)
int poz[MAX], pred[MAX];    // poz[nod] = i pozitia lui nod in sirul H[] este i
                            // sirul predecesorilor (tati - retine APM)


typedef struct node {
	int vf;
	node * next;
} NODE, * PNODE;

PNODE a[MAX];   // lista de adiacenta se creaza degeaba din moment ce exista matricea ponderilor

void ReadData();
void Add(int i, int j);
void Prim(int s);
void Print();
void BuildHeap();
void RebuildHeap(int i, int n);
int ExtractMin();

int main()
{
	ReadData();
	Prim(s);
	Print();

	return 0;
}

void ReadData()
{
	ifstream fin(INFILE);

	fin >> n >> s;   // noduri, sursa (sursa poate fi oricare nod)

	nrh = n;

	int i = 0, j = 0, cost = 0;

	for ( i = 1; i <= n; i++ )
	{
		H[i] = i;  // toate nodurile in HEAP
		poz[i] = i;
		sel[i] = 1;
		for ( j = 1; j <= n; j++ )
			if ( i != j ) c[i][j] = INFINIT;
	}

	while ( fin >> i >> j >> cost )
	{
		m++;
		c[i][j] = c[j][i] = cost;
		Add(i, j);
		Add(j, i);
	}
}

void Add(int i, int j)
{
	PNODE x = new NODE;
	x->vf = j;
	x->next = a[i];
	a[i] = x;
}

void RebuildHeap(int i, int n) // n - nrh (nr elem din HEAP)
{
	int value = 0, son = 0, parent = 0;

	value = H[i];
	parent = i;
	son = LEFT(parent);

	while ( son <= n )
	{
		if ( son < n )
			if ( key[H[son]] > key[H[son+1]] ) son++;
		if ( key[value] > key[H[son]] )
		{
			H[parent] = H[son];
			poz[H[parent]] = parent;
			parent = son;
			son = LEFT(son);
		}
		else break;
	}

	H[parent] = value;
	poz[H[parent]] = parent;
}

void MoveUp(int nod) // key[nod] a scazut. nod urca in HEAP
{
	int son, parent;
	son = poz[nod];
	parent = son / 2;
	while ( parent && key[H[parent]] > key[nod] )
	{
		H[son] = H[parent];
		poz[H[son]] = son;
		son = parent;
		parent = son / 2;
	}
	H[son] = nod;
	poz[nod] = son; // pozitia in sirul H[] a nodului H[son] este son
}

void BuildHeap()
{
	int i = 0;

	for ( i = nrh / 2; i >= 1; i-- )  // n - nr elem din HEAP
		RebuildHeap(i, nrh);
}

int ExtractMin()
{
	int min = H[1];
	sel[H[1]] = 0;   // nu mai apartine cozii
	H[1] = H[nrh--];
	RebuildHeap(1, nrh);

	return min;
}

void Prim(int s)
{
	int i = 0, u = 0;

	for ( i = 1; i <= n; i++ )
		key[i] = INFINIT;

	key[s] = 0;
	pred[s] = 0;
	nrh = n;
	BuildHeap(); // construieste HEAP-ul O(n)

	while ( nrh )
	{
		u = ExtractMin();     // O(log nrh)
		poz[u] = 0;           // u nu mai e in HEAP
		for ( PNODE x = a[u]; x; x = x->next )
			if ( sel[x->vf] && c[u][x->vf] < key[x->vf] ) // e in coada de prioritate (in HEAP)
			{
				pred[x->vf] = u;
				key[x->vf] = c[u][x->vf];
				MoveUp(x->vf);
			}
	}
}

void Print()
{
	ofstream fout(OUTFILE);

	int i = 0, sum = 0, source = 0;

	for ( i = 1; i <= n; i++ )
		if ( key[i] != INFINIT ) sum += key[i];   // nu cred ca sum == costul APM

	fout << sum << endl;
#ifndef __DEBUG__
	fout << endl;
	for ( int i = 1; i <= n; i++ )
	{
		for (int j = 1; j <= n; j++ )
			fout << setw(7) << c[i][j];
		fout << endl;
	}
	fout << endl;
#endif
	for ( int i = 1; i <= n; i++ )
		for (int j = i + 1; j <= n; j++ )
			if ( pred[i] == j || pred[j] == i ) // recuperez muchiile APM din sirul predecesorilor
				fout << i << " " << j << " " << c[i][j] << endl;

	fout.close();
}





