/*  100 puncte
    Complexitate O(N^2 * K)
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("drumuri.in");
ofstream fout("drumuri.out");
const int Dim = 251;
const int MOD = 31607;
int m, n, L, k;              // m - nr jetoane, k - nr puncte prin care tr sa treaca
short nr[2*Dim][Dim][Dim];   // nr de drumuri pan la diag i, coloana j, care trec prin p valori 1
short a[2*Dim][Dim];         // a[d][j] = 1 daca pe diagonala d si coloana j este un jeton

int main()
{
    fin >> n >> m >> k >> L;

    int x, y;
    for ( int i = 0; i < m; ++i )
    {
        fin >> x >> y;
        a[x + y - 1][y] = 1;
    }
    if ( a[1][1] )
        nr[1][1][1] = 1;
    else
        nr[1][1][0] = 1;


    for ( int i = 2; i <= L; ++i )
        for ( int j = max(i - n + 1, 1); j <= min(i, n); ++j )
            for ( int p = 0; p <= i && p <= k; ++p )
                nr[i][j][p + a[i][j]] = ((int) nr[i - 1][j][p] + (int)nr[i - 1][j - 1][p]) % MOD;

    int res = 0;
    int jmax = min(L, n);
    for ( int j = max(L - n + 1, 1); j <= jmax; ++j )
        res = (res + (int)nr[L][j][k]) % MOD;
    fout << res << '\n';

    fin.close();
    fout.close();
    return 0;
}

