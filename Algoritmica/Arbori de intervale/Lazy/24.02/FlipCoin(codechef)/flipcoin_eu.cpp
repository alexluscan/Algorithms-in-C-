#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

//ifstream fin("flipcoin.in");
//ofstream fout("flipcoin.out");

#define md (l+r)/2

const int Dim = 100001;

int n, m, op, L, R, ans;
int T[4 * Dim];
bool C[4 * Dim];

void Update(int x, int l, int r);
void PushDown(int x, int l, int r);
int Query(int x, int l, int r);

int main()
{
    cin >> n >> m;
    while ( m )
    {
        m--;
        cin >> op >> L >> R;
        L++;
        R++;
        if ( op == 0 )
        {
            Update(1, 1, n);

        }
        else
            cout << Query(1, 1, n) << '\n';

    }
//    fin.close();
//    fout.close();
    return 0;
}

void Update(int x, int l, int r)
{
    PushDown(x, l, r);
    if ( l > r || r < L || R < l )
        return;

    if ( L <= l && r <= R )
    {
        C[x] ^= 1;
        PushDown(x, l, r);
        return;
    }




    Update(2 * x, l, md);
    Update(2 * x + 1, md + 1, r);

    T[x] = T[2 * x] + T[2 * x + 1];
}

void PushDown(int x, int l, int r)
{

    if ( C[x] )
        T[x] = r - l + 1 - T[x];



    if ( l != r )
    {
        C[2 * x] ^= C[x];
        C[2 * x + 1] ^= C[x];
    }

    C[x] = 0;
}

int Query(int x, int l, int r)
{
    if ( l > r || r < L || R < l )
        return 0;
    if ( L <= l && r <= R )
    {
        if ( C[x] == 1 )
            PushDown(x, l, r);
        return T[x];
    }

    PushDown(x, l, r);

    return (Query(2 * x, l, md) + Query(2 * x + 1, md + 1, r));
}
