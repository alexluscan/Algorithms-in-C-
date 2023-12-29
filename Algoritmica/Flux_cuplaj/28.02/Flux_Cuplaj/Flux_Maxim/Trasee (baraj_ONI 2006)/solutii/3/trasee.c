#include <stdio.h>
#include <string.h>

#define MAX_N 205
#define INF 1000666
#define FIN "trasee.in"
#define FOUT "trasee.out"
#define FOR(i, a, b) for (i = (a); i < (b); i++)

int N, M, X, Y, K, G[MAX_N][MAX_N], deg[MAX_N], Res;
int Q[MAX_N], D[MAX_N], D2[MAX_N], up[MAX_N], C[MAX_N][MAX_N], F[MAX_N][MAX_N];

void BFS(int src, int D[])
{
    int ql, qr, n, *p;

    memset(D, 0, MAX_N*sizeof(int));
    for (D[Q[ql = qr = 0] = src] = 1; ql <= qr; ql++)
        for (p = G[n = Q[ql]]; *p; p++) if (!D[*p]) D[Q[++qr] = *p] = D[n]+1;
}

int augment(void)
{
    int ql, qr, n, i;

    memset(up, 0, sizeof(up));
    for (up[Q[ql = qr = 0] = X] = -1; ql <= qr; ql++)
        for (n = Q[ql], i = 1; i <= Y; i++)
        {
            if (C[n][i] <= F[n][i] || up[i]) continue;
            up[Q[++qr] = i] = n;
            if (i == Y) return 1;
        }
    return 0;
}

int main(void)
{
    int i, j, *p;
    
    freopen(FIN, "r", stdin);
    freopen(FOUT, "w", stdout);

    scanf("%d %d %d %d", &N, &M, &X, &K);
    for (; M > 0; M--)
    {
        scanf("%d %d", &i, &j);
        G[i][deg[i]++] = j;
        G[j][deg[j]++] = i;
    }
    Y = N+1;

    if (K == 1) { printf("1\n"); return 0; }

    BFS(X, D);
    FOR (i, 1, N+1)
    {
        if (D[i] != K) continue;
        
        BFS(i, D2); C[i][Y] = INF;
        FOR (j, 1, N+1) for (p = G[j]; *p; p++)
            if (D[j]+D2[*p] == K || D2[j]+D[*p] == K)
               C[j][*p] = C[*p][j] = 1;
    }

    for (Res = 0; augment(); Res++)
        for (i = Y; i != X; i = up[i])
            F[up[i]][i]++, F[i][up[i]]--;

    printf("%d\n", Res);
    
    return 0;
}
