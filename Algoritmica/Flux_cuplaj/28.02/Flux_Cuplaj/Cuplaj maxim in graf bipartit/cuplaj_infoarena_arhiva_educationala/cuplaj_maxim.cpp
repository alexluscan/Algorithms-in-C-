// OK - 100p (H-K)
// O(sqrt(V) * E) cu optimizarea Hopcroft-Karp
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
#define DIM 10001
 
ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");
 
typedef vector<int> VI;

 
VI G[DIM];
int n, m, K;   // noduri din prima si a doua partitie, nr de muchii
int v[DIM];   // vizitat
VI L, R;
 
void Read();
bool Cupleaza(int x);
 
int main()
{
    Read();
    int max_matching = 0;
    bool found_path = false;
    do
    {
        memset(v, false, sizeof(v));
        found_path = false;
        for (int i = 1; i <= n; ++i)
            if ( !L[i] && DoMatch(i) )
            {
                max_matching++;
                found_path = true;
            }
    } while ( found_path );
     
    fout << max_matching << '\n';
    for (int i = 1; i <= n; ++i)
        if ( L[i] )
            fout << i << ' ' << L[i] << '\n';
     
    fout.close();
}
  
bool DoMatch(int x)
{
    if ( v[x] ) return false;
    v[x] = true;
    for (const int& y : G[x])
        if ( !R[y] || DoMatch(R[y]) )
        {
            L[x] = y;
            R[y] = x;
            return true;
        }
    return false;
}
 
void Read()
{
    fin >> n >> m >> K;
    L.resize(n + 1), R.resize(m + 1);
    int x, y;
    for ( int i = 0; i < K; ++i )
    {
        fin >> x >> y;
        G[x].push_back(y);
    }
    fin.close();
}
