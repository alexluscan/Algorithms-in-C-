# include <cstdio>
# include <algorithm>
# define Mod 31607
# define NMax 253
using namespace std;

bool uz[NMax][NMax];     //unde sunt jetoanele
int maxx[NMax][NMax];    //cate jetoane strang pana intr-un punct
int nr[NMax][NMax][NMax];//cate moduri sunt

int x, y, sol, N, M, K, L, dist;

int main ()
{
    int i, j, k;
    freopen ("drumuri.in", "r", stdin);
    freopen ("drumuri.out","w", stdout);
    scanf ("%d %d %d %d", &N, &M, &K, &L);

    for (i=1; i<=M; ++i)
    {
        scanf ("%d %d", &x, &y);
        uz[x][y] = 1;
    }
    if (uz[1][1]) nr[1][1][1] = 1, maxx[1][1] = 1;
             else nr[1][1][0] = 1;
    for (i=1; i<=N; ++i)
    {
        for (j=1; j<=N; ++j)
        {
            if (i==1 && j==1) continue;
            maxx[i][j] = max(maxx[i-1][j], maxx[i][j-1]);
            if (!uz[i][j])
            {
                for (k=0; k<=maxx[i][j]; ++k)
                    nr[i][j][k] = (nr[i-1][j][k] % Mod + nr[i][j-1][k] % Mod) % Mod;
            }
            else
            {
                ++maxx[i][j];
                for (k=1; k<=maxx[i][j]; ++k)
                    nr[i][j][k] = (nr[i-1][j][k-1] % Mod + nr[i][j-1][k-1] % Mod) % Mod;
            }
        }
    }
    for (i=1; i<=N; ++i)
        for (j=1; j<=N; ++j)
        {
            dist = i+j-1;
            if (dist == L) sol = (sol + nr[i][j][K]) % Mod;
        }
    printf ("%d\n", sol);
    return 0;
}
