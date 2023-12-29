#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin("hotel.in");
ofstream fout("hotel.out");

const int Dim = 100001;

#define md ((l+r)/2)

int n, m, L, R, val, op, M;
int S[4 * Dim], D[4 * Dim], T[4 * Dim], a[Dim], cnt[4 * Dim];

void Build(int x, int l, int r);
void Update(int x, int l, int r);
void Set( int x, int y );
void PushDown( int x, int l, int r );

int main()
{
    fin >> n >> m;


    Build(1, 1, n);
    while ( m--)
	{
		fin >> op;
		if ( op == 1 )
		{
			fin >> L >> M;
			R = L + M - 1;
			val = 0;
			Update(1, 1, n);
		}
		if ( op == 2 )
        {
            fin >> L >> M;
			R = L + M - 1;
			val = 1;
			Update(1, 1, n);
        }
		if ( op == 3 )
        {
            fout << T[1] << '\n';
        }
	}

    fin.close();
    fout.close();
    return 0;
}

void Build(int x, int l, int r)
{

    T[x] = D[x] = S[x] = r - l + 1;

    if ( l >= r )
        return;

    Build(2 * x, l, md);
    Build(2 * x + 1, md + 1, r);


}

void Update(int x, int l, int r)
{


    if ( l > r || l > R || r < L )
        return;


    if ( L <= l && r <= R )
    {
        Set(x, (r - l + 1) * val);
    	return;
    }

    PushDown( x, l, r );


    Update(2 * x, l, md);
    Update(2 * x + 1, md + 1, r);

    S[x] = S[2 * x];
    D[x] = D[2 * x + 1];

    if ( S[x] == md - l + 1 )
        S[x] += S[2 * x + 1];

    if ( D[x] ==  r - md )
        D[x] += D[2 * x];

    T[x] = max(T[2 * x], T[2 * x + 1]);

    T[x] = max(T[x], D[2 * x] + S[2 * x + 1]);
}


void Set( int x, int y )
{
    T[x] = D[x] = S[x] = y;
}

 void PushDown( int x, int l, int r )
{
        if ( T[x] == 0 )
        {
            Set( 2 * x, 0 );
            Set( 2 * x + 1, 0 );
        }

        if ( T[x] == r - l + 1 )
        {
            Set( 2 * x, md - l + 1 );
            Set( 2 * x + 1, r - md);
        }
    }
