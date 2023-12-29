#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define N_MAX 256

int N, M, X, K;

vector<int> A[N_MAX];
short F[N_MAX][N_MAX];
int T[N_MAX];
int Flow;

void bf ()
{
    queue<int> q;
    int dist[N_MAX];
    int x;

    memset(dist, 0, sizeof(dist));

    q.push(X);
    dist[X] = 1;
    N++;
    for (; !q.empty();)
    {
        x = q.front();
        q.pop();

        if (dist[x] == K)
        {
            A[x].push_back(N);
            continue;
        }

        for (vector<int>::iterator it = A[x].begin();
            it != A[x].end(); it++)
            if (dist[*it] == 0)
            {
                q.push(*it);
                dist[*it] = dist[x] + 1;
            }
    }
}

bool bf2 ()
{
    queue<int> q;
    int i, x;
    
    for (i = 1; i <= N; i++)
        T[i] = -1;

    q.push(X);
    T[X] = 0;
    for (; !q.empty();)
    {
        x = q.front();
        q.pop();

        for (vector<int>::iterator it = A[x].begin();
            it != A[x].end(); it++)
            if (*it == N ||
                (T[*it] == -1 && (F[x][*it] == 0 || F[*it][x] == 1)))
        {
            q.push(*it);
            T[*it] = x;
            if (*it == N)
                return true;
        }
    }    
    
    return false;
}

void pump ()
{
    int x;
    Flow++;
    for (x = N; x != X; x = T[x])
        F[T[x]][x] = 1 - F[T[x]][x];
}

void flow ()
{
    while (bf2())
        pump();
}

void solve ()
{
    bf();
    flow();
    
    printf("%d\n", Flow);
}

void read_solve ()
{
    int i, a, b;
    
    freopen("trasee.in", "r", stdin);
    freopen("trasee.out", "w", stdout);
    
    scanf("%d%d%d%d", &N, &M, &X, &K);    
    for (i = 0; i < M; i++)
    {
        scanf("%d%d", &a, &b);
        A[b].push_back(a);
        A[a].push_back(b);
    }
    
    solve();
}

int main ()
{
    read_solve();
    return 0;
}
