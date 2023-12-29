#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NMAX 205

int N, M, X, K, i, j, k;
int m[NMAX], Q[NMAX], qb, qe;

int adj[NMAX][NMAX], c[NMAX][NMAX], f[NMAX][NMAX];
int u[NMAX], pi[NMAX];

int Ans;

void read(void)
{
    freopen("trasee.in", "r", stdin);
    freopen("trasee.out", "w", stdout);
    scanf("%d %d %d %d", &N, &M, &X, &K);

    memset(adj, 0, sizeof(adj));
    for (k = 0; k < M; k ++)
    {
        scanf("%d %d", &i, &j);
        adj[i][j] = adj[j][i] = 1;
    }
}

void bfs(void)
{
    memset(m, 0xFF, sizeof(m));
    for (m[Q[qb = qe = 0] = X] = 0; qb <= qe; qb ++)
    {
        int node = Q[qb];
        for (i = 1; i <= N; i ++)
            if (adj[node][i] && m[i] == -1)
               m[Q[++ qe] = i] = m[node] + 1;
    }
}

int augment(void)
{
    memset(u, 0, sizeof(u));
    u[Q[qb = qe = 0] = X] = 1;

    int i, node;
    for (; qb <= qe; qb ++)
    {
        node = Q[qb];
        for (i = 1; i <= N + 1; i ++)
            if (c[node][i] - f[node][i] > 0 && !u[i])
            {
               u[Q[++ qe] = i] = 1;
               pi[i] = node;

               if (i == N + 1)
                  return 1;
            }
    }
    
    return 0;
}

void solve(void)
{
    memset(c, 0, sizeof(c));
    memset(f, 0, sizeof(f));

    //build network
    for (i = 1; i <= N; i ++)
        for (j = 1; j <= N; j ++)
            if (adj[i][j] && m[i] + 1 == m[j]) // road i->j
               c[i][j] = 1;

    for (i = 1; i <= N; i ++)
        if (m[i] == K - 1)
           c[i][N + 1] = NMAX;  // infinite capacity


    Ans = 0;
    while (augment())
    {
        int minf = NMAX;
        for (i = N + 1; i != X; i = pi[i])
            if (c[pi[i]][i] - f[pi[i]][i] < minf)
               minf = c[pi[i]][i] - f[pi[i]][i];

        for (i = N + 1; i != X; i = pi[i])
            f[pi[i]][i] += minf, f[i][pi[i]] -= minf;

        Ans += minf;
    }

    printf("%d\n", Ans);
}

int main(void)
{
    read();
    bfs();
    solve();
    return 0;
}
