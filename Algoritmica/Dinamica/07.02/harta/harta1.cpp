/* 100 puncte
   Constantin Galatan
*/
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back
#define DIM 1501

ifstream fin("harta.in");
ofstream fout("harta.out");

struct Dr {
    int i1, j1, i2, j2;
    Dr(int _i1, int _j1, int _i2, int _j2)
        : i1(_i1), j1(_j1), i2(_i2), j2(_j2) {
    }
};

typedef vector<int> VI;
VI xa, ya, x, y;
vector<Dr> d;
int imax, jmax;
int T, N, M, n, m, k, L, H, Lmax;
bool A[DIM][DIM], s1[DIM], s2[DIM];

void One(), Two(), WriteMatr(bool a[][DIM], int N, int M);

int main()
{
    fin >> T >> N >> M >> k;
    int i1, j1, i2, j2;
    x.pb(0), y.pb(0); s1[0] = true, s2[0] = true;
    for ( int i = 0; i < k; ++i )
    {
        fin >> i1 >> j1 >> i2 >> j2;
        d.pb(Dr(i1, j1, i2, j2));
        L = i2 - i1 + 1, H = j2 - j1 + 1;
        if (  L == H && L > Lmax )
            Lmax = L;

        for ( int i = i1; i <= i2; ++i)
        {
            xa.pb(i), ya.pb(j1), xa.pb(i), ya.pb(j2);
            if ( !s1[i] ) x.pb(i), s1[i] = true;
        }
		for ( int j = j1; j <= j2; ++j )
        {
            xa.pb(i1), ya.pb(j); xa.pb(i2), ya.pb(j);
            if ( !s2[j] ) y.pb(j), s2[j] = true;
        }
        if ( !s1[i1 - 1] ) x.pb(i1 - 1), s1[i1 - 1] = true;
        if ( !s2[j1 - 1] ) y.pb(j1 - 1), s2[j1 - 1] = true;
        imax = max(imax, i2); jmax = max(jmax, j2);
    }

     if ( T == 1 )
        One();
    else
        Two();

    fin.close();
    fout.close();
    return 0;
}

void One()
{
    int nr_dr(0);
    for ( int i = 0; i < k; ++i )
    {
        L = d[i].i2 - d[i].i1 + 1, H = d[i].j2 - d[i].j1 + 1;
        if ( L < Lmax - 1 &&  H < Lmax - 1)
            nr_dr++;
    }
    fout << Lmax * Lmax << ' ' << nr_dr << '\n';
}

void Two()
{
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());

    int i, j;
    for (size_t k = 0; k < xa.size(); ++k )
    {
        i = lower_bound(x.begin(), x.end(), xa[k]) - x.begin();
        j = lower_bound(y.begin(), y.end(), ya[k]) - y.begin();
        n = max(n, i), m = max(m, j);
        A[i][j] = 1;
    }

    if ( n < M )  n++;
    if ( m < M )  m++;
    WriteMatr(A, n, m);
}

void WriteMatr(bool a[][DIM], int N, int M)
{
	for ( int i = 1; i <= N; ++i )
	{
		for ( int j = 1; j <= M; ++j )
			fout << a[i][j] << ' ';
		fout << '\n';
	}
}
