/* 100 pucte
   Constantin Galatan
*/

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back
#define DIM 1501
typedef vector<int> VI;

ifstream fin("harta.in");
ofstream fout("harta.out");

struct Dr {
    int i1, j1, i2, j2;
    Dr(int _i1, int _j1, int _i2, int _j2)
        : i1(_i1), j1(_j1), i2(_i2), j2(_j2) {
    }
};

vector<Dr> d;
int imax, jmax;
VI xa, ya, x, y, c1, c2, b1, b2;
int k, N, M, n, m, Lmax, L, H, T, nr_dr;
bool A[DIM][DIM], s1[DIM], s2[DIM];

void WriteMatr(bool a[][DIM], int N, int M);
int GetPos(VI, int val);

int main()
{
    fin >> T >> N >> M >> k;
    int i1, j1, i2, j2;
    x.pb(0), y.pb(0); s1[0] = true; s2[0] = true;
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
            if ( !s1[i] ) x.pb(i),  s1[i] = true;
        }
		for ( int j = j1; j <= j2; ++j )
        {
            xa.pb(i1), ya.pb(j); xa.pb(i2), ya.pb(j);
            if ( !s2[j] ) y.pb(j),  s2[j] = true;
        }
        if ( !s1[i1 - 1] ) x.pb(i1 - 1), s1[i1 - 1] = true;
        if ( !s2[j1 - 1] ) y.pb(j1 - 1), s2[j1 - 1] = true;
        imax = max(imax, i2); jmax = max(jmax, j2);
    }

    if ( T == 1 )
    {
        for ( int i = 0; i < k; ++i )
        {
            L = d[i].i2 - d[i].i1 + 1, H = d[i].j2 - d[i].j1 + 1;
            if ( L < Lmax - 1 &&  H < Lmax - 1 )
                nr_dr++;
        }
        fout << Lmax * Lmax << ' ' << nr_dr << '\n';
    }
    else
    {
        c1 = VI(imax + 1);
        c2 = VI(jmax + 1);

        for (int i = 0; i < x.size(); ++i )
            c1[x[i]]++;
        for (int i = 0; i < y.size(); ++i )
            c2[y[i]]++;

        for (int i = 1; i <= imax; ++i )
            c1[i] += c1[i - 1];
         for (int i = 1; i <= jmax; ++i )
            c2[i] += c2[i - 1];

        b1 = VI(x.size()); // aici - x sortat
        b2 = VI(y.size());

        for ( int i = 0; i < x.size(); ++i )
            b1[c1[x[i]] - 1] = x[i], c1[x[i]]--;

        for ( int i = 0; i < y.size(); ++i )
            b2[c2[y[i]] - 1] = y[i], c2[y[i]]--;

        n = 0, m = 0; int i, j;
        for (size_t k = 0; k < xa.size(); ++k )
        {
            i= GetPos(b1, xa[k]);
            j = GetPos(b2, ya[k]);
            n = max(n, i), m = max(m, j);
            A[i][j] = 1;
        }

        if ( n < M ) n++;
        if ( m < M ) m++;
        WriteMatr(A, n, m);
    }
    fin.close();
    fout.close();
    return 0;
}


int GetPos(VI v, int val)
{
    int i, p2, n = v.size();
    int lo = 0, hi = n, mid;
    while ( lo <= hi )
    {
        mid = lo + (hi - lo) / 2;
        if ( v[mid] == val )
            return mid;
        if ( val < v[mid] )
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return 0;

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
