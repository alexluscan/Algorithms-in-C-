

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char Type[52][52];   // tipul nodului: 1 - uscat('.'); 0 - mlastina('x'); 2 - transformabil('*')
short far Val[52][52];

int N, M;
int L1, C1, L2, C2;

int Nr;

int vi[4] = {0, -1, 1, 0};   // vecini stanga, sus, jos, dreapta
int vj[4] = {-1, 0, 0, 1};
#define ni (i + vi[v])
#define nj (j + vj[v])
#define vinv (3-(v)) // ex  v = 3(dreapta) vinv = 3 -3 = 0(stanga)
                     // sau v = 2(jos)     vinv = 3 - 2 = 1(sus)

short Flow[52][52][4];       // fluxurile nodului (pt 4 directii)
short F[52][52], C[52][52];  // flux intern, capacitate interna
char tv[52][52][2];
char far ci[52*52*2];  // coada de i-uri
char far cj[52*52*2];  // coada de j-uri
char far cd[52*52*2];  // coada de d-uri
int cl, cr;
int TFlow;

#define INF 32666

int bf()
{
    int i, j, d, v;
    memset(tv, -1, sizeof(tv)); //  umple matricea cu un caracter  ii coresp cod ASCII 255)
    for (i = 0; i <= M; i++)
        tv[0][i][0] = tv[0][i][1] = tv[N+1][i][0] = tv[N+1][i][1] = 13;
    for (i = 0; i <= N; i++)
        tv[i][0][0] = tv[i][0][1] = tv[i][M+1][0] = tv[i][M+1][1] = 13;   //'\r'

    ci[0] = L1, cj[0] = C1, cd[0] = 1; 

    for (cl = cr = 0; cl <= cr && tv[L2][C2][0] == -1; cl++) // cl, cr left, right, cd[] sir caracteristic
    {
        i = ci[cl], j = cj[cl], d = cd[cl];  // la inceput, d = 1 ( cu d si !d alterneaza intre tv[i][j][0] si tv[i][j][1]

        if (tv[i][j][!d] == -1 &&  // neselectat // la inceput !d = 0
            ((!d && F[i][j] < C[i][j]) || (d & F[i][j]))) // neselectat si flux intern < cap interna || (d==1 && F[i][j]== 1)
          tv[i][j][!d] = 4,  // vecinul e dublura
          ci[++cr] = i, cj[cr] = j, cd[cr] = !d;  // se mai pune odata pozitia curenta in coada ( acelasi nod)
                                                  // capul cozii(i, j ) are d ; coada (i,.j) are !d
        for (v = 0; v < 4; v++)
          if (tv[ni][nj][!d] == -1 && (d || Flow[ni][nj][vinv])) // flux de la vecin la (i, j)
            tv[ni][nj][!d] = vinv, ci[++cr] = ni, cj[cr] = nj, cd[cr] = !d;
    }
    if (tv[L2][C2][0] == -1) return 0;  // n-am gasit drum de crestere
    for (i = L2, j = C2, d = 0; i != L1 || j != C1;)  // pompez
    {
        v = tv[i][j][d];  // v - directia
        if (v == 4)       // am de pompat pe o muchie interna(nod dublu)
        {                 // d indica sensul fluxului intern prin nodul (i, j)
           F[i][j] += d ? +1 : -1;  // d == 1 => F[i][j]++;  d == 0 => F[i][j]--;
           d = !d;
           continue;
        }
        if (d)
            Flow[i][j][v]--; // fluxul care iese din (i, j) spre directia v
        else
            Flow[ni][nj][vinv]++; // fluxul care iese din vecin spre directia curenta
        i = ni, j = nj, d = !d;   // trec pe vecin
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
     if (Type[i][j] == 2 && tv[i][j][0] != -1 && tv[i][j][1] == -1) // e transformabil si primul nod(al celui dublu) e atins, celalalt nu ( muchia interna e saturata)
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
         Type[i][j] = (c != 'x' && c != 'X') + (c == '*'); // 1 - uscat('.');  0 - mlastina('x') ;transformabil('*') == 2
         if (c == 'M') L1 = i, C1 = j, Type[i][j] = -1;
         if (c == 'T') L2 = i, C2 = j, Type[i][j] = -2;
         C[i][j] = (Type[i][j] == 0) ? 0 : (Type[i][j] == 2) ? 1 : INF; // capacitatea 0 (mlastina), 1 (intre noduri dedublate), INF (nod simplu)
     }                             // C[i][j] - capacitatea interna a nodului (0, 1, INF) // mlast, transf, uscat
    fclose(fi);
}

int main()
{
    read_data();
    solve();
    print();
    return 0;
}
