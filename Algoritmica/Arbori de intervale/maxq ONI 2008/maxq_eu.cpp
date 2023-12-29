#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin("maxq.in");
ofstream fout("maxq.out");

#define md ((l+r)/2)

const int Dim = 200001, Inf = 0x3f3f3f3f;

int n, m, op, a, b, A[Dim];
long long ans, sum;
long long M[4 * Dim], L[4 * Dim], R[4 * Dim], S[4 * Dim];

void Build(int x, int l, int r);
void Update(int x, int l, int r);
void Query(int x, int l, int r);

int main()
{
    fin >> n;
    for ( int i = 1; i <= n; i++ )
        fin >> A[i];
    fin >> m;
    Build(1, 1, n);
    while ( m )
    {
        m--;
        fin >> op >> a >> b;
        if ( op == 0 )
        {
            a++;
            Update(1, 1, n);
        }
        else
        {
            sum = ans = 0;
            a++;
            b++;
            Query(1, 1, n);
            fout << ans << '\n';
        }
    }
    fin.close();
    fout.close();
    return 0;
}

void Build(int x, int l, int r)
{
    if ( l == r )
    {
        S[x] = A[l];
        M[x] = L[x] = R[x] = max(A[l], 0);
        return;
    }

    Build(2 * x, l, md);
    Build(2 * x + 1, md + 1, r);

    S[x] = S[2 * x] + S[2 * x + 1];
    L[x] = max(L[2 * x], S[2 * x] + L[2 * x + 1]);
    R[x] = max(R[2 *x + 1], R[2 * x] + S[2 * x + 1]);

    //M[x] = max(L[x], R[x]);
    M[x] = max(M[2 * x + 1], M[2 * x]);
    M[x] = max(M[x], R[2 * x] + L[2 * x + 1]);
}

void Update(int x, int l, int r)
{
    if ( l == r )
    {
        S[x] = b;
        M[x] = L[x] = R[x] = max(b, 0);
        return;
    }
    if ( a <= md )
        Update(2 * x, l, md);
    else
        Update(2 * x + 1, md + 1, r);

    S[x] = S[2 * x] + S[2 * x + 1];
    L[x] = max(L[2 * x], S[2 * x] + L[2 * x + 1]);
    R[x] = max(R[2 * x + 1], R[2 * x] + S[2 * x + 1]);

    //M[x] = max(L[x], R[x]);
    M[x] = max(M[2 * x + 1], M[2 * x]);
    M[x] = max(M[x], R[2 * x] + L[2 * x + 1]);
}

void Query(int x, int l, int r)
{

    if (a <= l && r <= b)
    {
		if ( sum < 0 )
            sum = 0;
		ans = max(ans, max(sum + L[x], M[x]));

        sum = max(sum + S[x], R[x]);
	}
	else
    {
		if (  a <= md  )
            Query(2 * x, l, md);
        if ( b > md)
            Query(2 * x + 1, md + 1, r);
    }
}
