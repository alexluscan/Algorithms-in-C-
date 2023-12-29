/***MEM:C***/

/*
Magic Flow Solution
O(N^2*M^2).
Optimized version (i.e. implicit graph)

by Radu Berinde
*/


#ifdef __BORLANDC__
#pragma option -3 -O2
#include <alloc.h>
#else
#define far
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char Type[52][52];
short far Val[52][52];

int N, M;
int L1, C1, L2, C2;

int Nr;

int vi[4] = {0, -1, 1, 0};
int vj[4] = {-1, 0, 0, 1};
#define ni (i + vi[v])   // noul i si noul j
#define nj (j + vj[v])
#define vinv (3-(v))

short Flow[52][52][4];
short F[52][52], C[52][52];
char tv[52][52][2];
char far ci[52*52*2];
char far cj[52*52*2];
char far cd[52*52*2];
int cl, cr;
int TFlow;

#define INF 32666

int bf()
{
    int i, j, d, v;
    memset(tv, -1, sizeof(tv)); 
    for (i = 0; i <= M; i++)
        tv[0][i][0] = tv[0][i][1] = tv[N+1][i][0] = tv[N+1][i][1] = 13;
    for (i = 0; i <= N; i++)
        tv[i][0][0] = tv[i][0][1] = tv[i][M+1][0] = tv[i][M+1][1] = 13;

    ci[0] = L1, cj[0] = C1, cd[0] = 1; 
    tv[L1][C1][1] = 5;

    for (cl = cr = 0; cl <= cr && tv[L2][C2][0] == -1; cl++)
    {
        i = ci[cl], j = cj[cl], d = cd[cl];

        if (tv[i][j][!d] == -1 &&  
            ((!d && F[i][j] < C[i][j]) ||  
            (d & F[i][j])))                
          tv[i][j][!d] = 4, ci[++cr] = i, cj[cr] = j, cd[cr] = !d;

        for (v = 0; v < 4; v++)
          if (tv[ni][nj][!d] == -1 && (d || Flow[ni][nj][vinv]))
            tv[ni][nj][!d] = vinv, ci[++cr] = ni, cj[cr] = nj, cd[cr] = !d;
    }
    if (tv[L2][C2][0] == -1) return 0;
    for (i = L2, j = C2, d = 0; i != L1 || j != C1;)
    {
        v = tv[i][j][d];
        if (v == 4)
        {
           F[i][j] += d ? +1 : -1;
           d = !d;
           continue;
        }
        if (d)
            Flow[i][j][v]--;
        else
            Flow[ni][nj][vinv]++;
        i = ni, j = nj, d = !d;
    }
    return 1;
}

void solve()
{
    while (bf())
      TFlow++;
}

void print()
{
    int i, j;
    FILE *fo = fopen("magic.out", "wt");
    fprintf(fo, "%d\n", TFlow);
    for (i = 1; i <= N; i++)
     for (j = 1; j <= M; j++)
     if (Type[i][j] == 2 && tv[i][j][0] != -1 && tv[i][j][1] == -1)
         fprintf(fo, "%d %d\n", i, j);
    fclose(fo);
}

void read_data()
{
    int i, j;
    char c;
    FILE *fi = fopen("magic.in", "rt");
    fscanf(fi, "%d %d", &N, &M);
    for (i = 1; i <= N; i++)
     for (j = 1; j <= M; j++)
     {
         fscanf(fi, " %c", &c);
         Type[i][j] = (c != 'x' && c != 'X') + (c == '*'); 
         if (c == 'M') L1 = i, C1 = j, Type[i][j] = -1;
         if (c == 'T') L2 = i, C2 = j, Type[i][j] = -2;
         C[i][j] = (Type[i][j] == 0) ? 0 : (Type[i][j] == 2) ? 1 : INF; 
     }
    fclose(fi);
}

int main()
{
    read_data();
    solve();
    print();
    return 0;
}
