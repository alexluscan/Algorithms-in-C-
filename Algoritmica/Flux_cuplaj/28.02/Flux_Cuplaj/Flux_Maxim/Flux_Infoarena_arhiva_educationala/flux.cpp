#include <stdio.h>
#include <vector>
 
using namespace std;
 
#define NMAX 1024
#define pb push_back
#define sz size()
#define mp make_pair
#define INF 0x3f3f3f3f
 
int C[NMAX][NMAX];
int F[NMAX][NMAX];
int t[NMAX];
vector<int> G[NMAX];
int N, M;
int cd[NMAX];
int viz[NMAX];
 
int BF()
{
    int i, j, nod, V;
 
    cd[0] = 1;
    cd[1] = 1;
    memset(viz, 0, sizeof(viz));
    viz[1] = 1;
 
    for (i = 1; i <= cd[0]; i++)
    {
        nod = cd[i];
        if (nod == N) continue;
        for (j = 0; j < G[nod].sz; j++)
		{
			V = G[nod][j];
			if (C[nod][V] == F[nod][V] || viz[V]) continue;
			viz[V] = 1;
			cd[ ++cd[0] ] = V;
			t[V] = nod;
		}
    }
 
    return viz[N];
}
 
int main()
{
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);
 
    int i, flow, fmin, x, y, z, nod;
 
    scanf("%d %d ", &N, &M);
 
    for (i = 1; i <= M; i++)
    {
        scanf("%d %d %d ", &x, &y, &z);
        C[x][y] += z;
        G[x].pb(y);
        G[y].pb(x);
    }
 
    for (flow = 0; BF();)
        for (i = 0; i < G[N].sz; i++)
        {
            nod = G[N][i];
            if (F[nod][N] == C[nod][N] || !viz[nod]) continue;
            t[N] = nod;
             
            fmin = INF;
            for (nod = N; nod != 1; nod = t[nod])
                fmin = min(fmin, C[t[nod]][nod] - F[t[nod]][nod]);
            if (fmin == 0) continue;
             
            for (nod = N; nod != 1; nod = t[nod])
            {
                F[ t[nod] ][nod] += fmin;
                F[nod][ t[nod] ] -= fmin;
            }
 
            flow += fmin;
        }
 
    printf("%d ", flow);
    return 0;
}
