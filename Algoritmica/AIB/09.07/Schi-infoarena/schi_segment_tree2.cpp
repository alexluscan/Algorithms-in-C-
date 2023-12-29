#include <iostream>
#include <cstdio>

#define NMax 30005

using namespace std;

int N, ArbInt[4*NMax], Place[NMax], Q[NMax], NQ;

void Update (int K, int L, int R, int P, int V)
{
    int Mid=(L+R)/2;
    if (L==R)
    {
        ArbInt[K]=V;
        return;
    }
    if (P<=Mid)
    {
        Update (2*K, L, Mid, P, V);
    }
    if (P>Mid)
    {
        Update (2*K+1, Mid+1, R, P, V);
    }
    ArbInt[K]=ArbInt[2*K]+ArbInt[2*K+1];
}

int Query (int K, int L, int R, int S)
{
    int Mid=(L+R)/2;
    if (L==R)
    {
        return Mid;
    }
    if (ArbInt[2*K]>=S)
    {
        return Query (2*K, L, Mid, S);
    }
    return Query (2*K+1, Mid+1, R, S-ArbInt[2*K]);
}

void Read ()
{
    freopen ("schi.in", "r", stdin);
    scanf ("%d", &N);
    for (NQ=1; NQ<=N; ++NQ)
    {
        scanf ("%d", &Q[NQ]);
        Update (1, 1, N, NQ, 1);
    }
    --NQ;
}

void Print ()
{
    freopen ("schi.out", "w", stdout);
    for (int i=1; i<=N; ++i)
    {
        printf ("%d\n", Place[i]);
    }
}

int main()
{
    Read ();
    for (; NQ>0; --NQ)
    {
        int P=Query (1, 1, N, Q[NQ]);
        Place[P]=NQ;
        Update (1, 1, N, P, 0);
        Q[NQ]=0;
    }
    Print ();
    return 0;
}
