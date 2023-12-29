// prof. Constantin Galatan
#include <iostream>
#include <iomanip>

#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

#define IN     "furtuna.in"
#define OUT    "furtuna.out"
#define MAX_N    402          // exista nodul n + 1 in reteaua de transport
#define MAX_M    2001
#define MAX_COST 301
#define INF INT_MAX / 2

FILE* fout = fopen(OUT, "w");

typedef int TAB2[MAX_N][MAX_N];
typedef int TAB1[MAX_N];
TAB2 t;  //  timp minim
TAB1 tr, cb, nr, graf, p, q;  // turisti, cabane, nr_max_turisti/cabana, reteaua de transport, predecesorii, coada
TAB2 cap, f;   // capacitat, flux
int Tmin;
int n, m, S, D, T, C;  // noduri, muchii, sursa, dest, turisti, cabane

void Read();
void Roy_Floyd();
void Solve();
void Write();

int main()
{
    Read();
    Solve();
    Write();
    return 0;
}

void Read()
{
   FILE* fin = fopen(IN, "r");
   int i, j, k, x, y, time;
   fscanf(fin, "%d %d %d %d", &n, &m, &T, &C);       // turisti, cabane
   for ( i = 1; i <= n; i++ )
   for ( j = 1; j <= n; j++ )
      t[i][j] = (i != j) ? INF : 0;

   for ( i = 0; i < m; i++ )
   {
      fscanf(fin, "%d %d %d", &x, &y, &time);
      t[x][y] = t[y][x] = time;
   }

   for ( i = 1; i <= T; i++ )
      fscanf(fin, "%d", tr + i);
   for ( i = 1; i <= C; i++ )
      fscanf(fin, "%d %d", cb + i, nr + i);

   S = 0, D = n + 1; // un nod din afara grafului
   for ( i = 1; i <= T; i++ )
      cap[0][tr[i]] = 1;
   for ( i = 1; i <= C; i++ )
      cap[cb[i]][D] = nr[i];

   graf[0] = S; graf[T+C+1] = D;
   for(k = 1; k <= T + C; k++ )        // pun toate nodurile reprezentand (turisti + cabane) intr-un singur sir
      graf[k] = (k <= T) ? tr[k]: cb[k - T];

   fclose(fin);
}

void Roy_Floyd()
{
   for (int k = 1; k <= n; k++ )
      for (int i = 1; i <= n; i++ )
         for (int j = 1; j <= n; j++ )
            t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
}

bool BFS()
{
   int i, j, h = 0, t = 0;
   q[h] = S;
   for ( i = 0; i <= T + C + 1; i++ )
      p[graf[i]] = -1;
   while ( h <= t )
   {
      for ( i = q[h++], j = 0; j <= T + C + 1; j++ )
         if ( p[graf[j]] == -1 && cap[i][graf[j]] > f[i][graf[j]] )
         {

            q[++t] = graf[j];
            p[graf[j]] = i;
            if ( graf[j] == D ) return true;
         }
   }

   return false;
}

int MaxFlow(int Time)
{
   int flow, i, j;
   for ( i = 1; i <= T; i++ )
      for ( j = 1; j <= C; j++ )
         cap[tr[i]][cb[j]] = (t[tr[i]][cb[j]] <= Time) ? 1 : 0;

   memset(f, 0, sizeof(f));
   for (flow = 0; BFS(); flow++ )
      for (i = D; i != 0; i = p[i])
         f[p[i]][i]++, f[i][p[i]]--;

   return flow;
}

void Solve()
{
   Roy_Floyd();
   int Tmax = MAX_COST * MAX_M;
   int l = 1, r = Tmax, m;
   while ( l <= r )
   {
      m = (l + r) / 2;
      int Fl = MaxFlow(m);

      if ( Fl == T )
         Tmin = m, r = m - 1;
      else
         l = m + 1;
   }
}

void Write()
{
   fprintf(fout, "%d\n", Tmin);
   fclose(fout);
}

