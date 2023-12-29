// Determinarea punctelor de articulatie ale unui graf neorientat
#include <fstream>
#include <vector>
using namespace std;

const int MAX = 100;
vector<int> G[MAX];
int n;
bool p[MAX];     // p[i] == true daca i e pct. articulatie
int t[MAX];     // sir de tati
int niv[MAX];   // Nivelul fiecarui nod in arborele DF
int L[MAX];     // Niv minim in arbore pe care se p ajung dintr-un nod sau
                // dintr-unul dintre descendentii lui
                // printr-o singura muchie de intoarcere
int root;       // nodul ales radacina
int nr;         // Nr de muchii "de arbore" (care "ies" din radacina)
bool s[MAX];

void Read();
void Write();
void DF(int nod, int nv);
void PuncteArticulatie();

int main()
{
	Read();
	root = 1;
	DF(root, 1);           // O(m)
	PuncteArticulatie();   // O(n)
	Write();               // O(n)
	return 0;
}

void DF(int x, int nv)   // O(m)
{
	if ( nv == 2 ) nr++;
	L[x] = niv[x] = nv;
	s[x] = true;
	for (const int& y : G[x])
    {
        if ( y == t[x] ) continue;
        if ( !s[y] ) // muchie de arbore
        {
            t[y] = x;
            DF(y, nv + 1);
            L[x] = min(L[x], L[y]);
        }
        else // muchie de intoarcere
            L[x] = min(L[x], niv[y]);
    }
}

void PuncteArticulatie()
{
	if ( nr > 1 )
        p[root] = true;   // rad e punct de articulatie daca din ea pleaca cel putin doua muchii de arbore
	for (int i = 1; i <= n; i++ )
    {
		if ( i == root || t[i] == root)
            continue;
        if ( L[i] >= niv[t[i]] )
            p[t[i]] = true;
    }
}

void Write()
{
	ofstream fout("graf.out");

    fout << "Nivelurile niv:\n";
	for ( int i = 1; i <= n; i++ )
		fout << niv[i] << " ";

	fout << "\nNivelurile minime L:\n";
	for ( int i = 1; i <= n; i++ )
		fout << L[i] << " ";

	fout << "\nPunctele de articulatie:\n";
	for ( int i = 1; i <= n; i++ )
		if ( p[i] ) fout << i << " ";
	fout.close();
}

void Read()
{
	int x, y;
	ifstream fin("graf.in");
	fin >> n;
	while ( fin >> x >> y )
	{
		G[x].push_back(y);
		G[y].push_back(x);
	}
	fin.close();
}


