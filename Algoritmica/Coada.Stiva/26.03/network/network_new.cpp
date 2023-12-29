#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

ifstream fin("network.in");
ofstream fout("network.out");

const int Dim = 105, Inf = 0x3f3f3f3f;

int n, m, flux, fmx, fmin = Inf;
int C[Dim][Dim], F[Dim][Dim], t[Dim];
bool v[Dim];
queue<int> Q;
vector<vector<int>> G;


void Read();
bool Bf(int x, int d);

int main()
{
    Read();
    for ( int k = 2; k <= n; k++ )
    {
        flux = 0;
        memset( F, 0, sizeof(F) );
        memset( t, 0, sizeof(t) );
        while ( Bf(1, k) )
        {
            for ( auto y :G[k] )
            {
                if ( !v[y] || F[y][k] == C[y][k] )
                    continue;
                t[k] = y;
                fmx = Inf;
                for ( int i = k; i != 1; i = t[i] )
                    fmx = min(fmx, C[t[i]][i] - F[t[i]][i]);

                if ( fmx == 0 )
                    continue;

                for ( int i = k; i != 1; i = t[i] )
                {
                    F[t[i]][i] += fmx;
                    F[i][t[i]] -= fmx;
                }
                flux += fmx;
            }

        }
        fmin = min(fmin, flux);

    }
    fout << fmin;
    fin.close();
    fout.close();
    return 0;
}

void Read()
{
    fin >> n >> m;
    int x, y;
    G = vector<vector<int>>(n + 1);

    for ( int i = 1; i <= m; i++ )
    {
        fin >> x >> y;
        C[x][y]++;
        C[y][x]++;
        G[x].push_back(y);
        G[y].push_back(x);
    }
}

bool Bf(int x, int d)
{
    memset(v, 0, sizeof(v));
    Q.push(x);
    v[x] = 1;

    while( !Q.empty() )
    {
        x = Q.front();
        Q.pop();
        if ( x == d )
            continue;
        for ( auto y : G[x] )
        {
            if ( v[y] || F[x][y] == C[x][y] )
                continue;

            v[y] = 1;
            t[y] = x;
            Q.push(y);
        }
    }

    return v[d];

}
