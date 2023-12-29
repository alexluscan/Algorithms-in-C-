/*
	Sursa C++ Problema dreptunghi
	baleiere + arbori de intervale
 	Complexitate: O(N * lg MAXC) }
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abs(x)((x) < 0 ? (-(x)) :(x))

struct edge {
    int x, y1, y2, sgn;
} H[100000], V[100000];

typedef struct edge edge;

int N, Cnt[131072], Sum[131072];

int cmp(const void *i, const void *j)
{
    edge *ei=(edge*) i, *ej=(edge*) j;
    if (ei->x != ej->x)
       return ei->x - ej->x;
    return ej->sgn - ei->sgn;
}

void update(int n, int l, int r, int a, int b, int c)  
{
   int m;
   if (a <= l && r <= b)
      Cnt[n] += c;
   else
   {
    m = (l + r) / 2;
    if (a <= m)
     update(2 * n, l, m, a, b, c);
    if (b > m)
     update(2*n+1,m+1, r, a, b, c);
    }
    Sum[n] = Cnt[n] ? (r - l + 1) :
    (Sum[2 * n] + Sum[2 * n + 1]);
}

int solve(edge E[])
{
    int i, t = 0, P = 0;

    qsort(E,2*N, sizeof(edge), cmp);
    memset(Cnt, 0, sizeof(Cnt));
    memset(Sum, 0, sizeof(Sum));

    for (i = 0; i < 2 * N; i++) // pana la N - 1 sunt capetele de jos; de la N cele de sus
        update(1, 0, 49999, E[i].y1, E[i].y2  -  1, E[i].sgn),
        P += abs(t-Sum[1]),t=Sum[1];
    return P;
}

int main(void)
{
    FILE *f;
    int i, x1, y1, x2, y2;

    f = fopen("drept.in", "r");
    fscanf(f, "%d\n", &N);
    for (i = 0; i < N; i++)
    {
		fscanf(f, "%d %d %d %d",&x1,&y1, &x2, &y2);

        V[i].x = x1, V[i].y1 = y2,     // segmentul din stanga dreptunghiului
        V[i].y2 = y1, V[i].sgn = +1;   // semnul identifica segmentul (stanga sau dreapta)
        V[i+N].x=x2, V[i+N].y1 = y2,   // segm din dreapta al dreptunghiului
        V[i+N].y2=y1, V[i+N].sgn = -1;

        H[i].x = y1, H[i].y1 = x1,     //schimba axa OX cu OY
        H[i].y2 = x2, H[i].sgn = +1;   // segm oriz devin verticale
        H[i+N].x=y2,H[i+N].y1 = x1,
        H[i+N].y2=x2, H[i+N].sgn = -1;
    }
    fclose(f);

    f = fopen("drept.out", "w");
    fprintf(f, "%d\n", solve(V) + solve(H));
    fclose(f);

    return 0;
}
