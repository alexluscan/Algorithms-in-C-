#include <stdio.h>
#include <string.h>
#define INF 0x3f3f3f3f
#define MAX_N 256

int G[MAX_N][MAX_N], R[MAX_N][MAX_N], U[MAX_N], st[MAX_N], N, M, S, D, K;
int T[MAX_N];

void bf()
{
    int node, ql, qr, i;

    memset(U, 0, sizeof(U));
    U[st[0] = S] = 1;
    for (ql = 0, qr = 1; ql < qr; ql++)
    for (node = st[ql], i = 0; i < N; i++)
        if (U[node] < K && G[node][i])
        {
            if (!U[i])
                st[qr++] = i, R[node][i] = 1, U[i] = U[node] + 1;
            else
                if (U[i] == U[node] + 1) R[node][i] = 1;
        }
    for (i = 0; i < N; i++)
        if (U[i] == K) R[i][D] = INF;
}

int Path()
{
    int node, ql, qr, i;

    for (i = 0; i <= D; i++) T[i] = -1;
    T[st[0] = S] = S;
    for (ql = 0, qr = 1; ql < qr; ql++)
    for (node = st[ql], i = 0; i <= D; i++)
        if (R[node][i] > 0 && T[i] == -1)
            T[st[qr++] = i] = node;
    if (T[D] == -1) return 0;
    for (node = D; node != S; node = T[node])
        R[T[node]][node]--,
        R[node][T[node]]++;
    return 1;
}

int main()
{
    int flow, i, x, y;
    
    freopen("trasee.in", "r", stdin);
    freopen("trasee.out", "w", stdout);
    scanf("%d %d %d %d", &N, &M, &S, &K);
    S--;
    for (i = 0; i < M; i++)
        scanf("%d %d", &x, &y),
        x--, y--,
        G[x][y] = G[y][x] = 1;

    D = N;
    bf();
    for (flow = 0; Path(); flow++);
    printf("%d\n", flow);

    return 0;
}
