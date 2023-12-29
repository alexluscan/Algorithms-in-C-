#include <stdio.h>
#include <string.h>

#define FIN "trasee.in"
#define FOUT "trasee.out"

#define MAX_N 202
#define INF 0x3f3f3f3f

int G[MAX_N][MAX_N], U[MAX_N], Q[MAX_N];
int K, N, S, D, H[MAX_N][MAX_N], F[MAX_N][MAX_N], Father[MAX_N];

void BFS(void)
{
    int i, L, R;

    memset(U, 0, sizeof(U));
    U[Q[L = R = 0] = S] = 1;
    for (; L <= R; L++)
        for (i = 1; i <= N; i++)
            if (G[Q[L]][i] && !U[i])
            {
                Q[++R] = i;
                U[i] = U[Q[L]] + 1;
            }
}

void build(void)
{
    int i, j;

    memset(H, 0, sizeof(H));
    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++)
            if (U[i] + 1 == U[j] && U[j] <= K && G[i][j])
               H[i][j] = 1;
    D = N + 1;
    for (i = 1; i <= N; i++)
        if (U[i] == K) H[i][D] = INF;
}

int BF(void)
{
    int a, b, i, p, L, R;

    memset(U, 0, sizeof(U));
    U[Q[L = R = 0] = S] = 1;
    for (; L <= R && !U[D]; L++)
        for (i = 1; i <= D; i++)
            if (H[Q[L]][i] - F[Q[L]][i] > 0 && !U[i])
            {
                U[Q[++R] = i] = 1;
                Father[R] = L;
            }
            else
            if (F[i][Q[L]] > 0 && !U[i])
            {
                U[Q[++R] = i] = 1;
                Father[R] = L;
            }

    if (!U[D]) return 0;

    for (p = R; p; p = Father[p])
    {
        a = Q[p];
        b = Q[Father[p]];
        if (H[b][a] - F[b][a] > 0) F[b][a]++;
        else F[a][b]--;
    }

    return 1;
}

int main(void)
{
    int i, j, M, s;

    freopen(FIN, "r", stdin);
    freopen(FOUT, "w", stdout);

    memset(G, 0, sizeof(G));
    scanf("%d %d %d %d", &N, &M, &S, &K);
    for (; M--; )
    {
        scanf("%d %d", &i, &j);
        G[i][j] = G[j][i] = 1;
    }
    BFS();
    build();
    while (BF()) ;

    for (s = 0, i = 1; i < D; i++)
        if (i != S) s += F[S][i];

    printf("%d\n", s);

    return 0;
}
