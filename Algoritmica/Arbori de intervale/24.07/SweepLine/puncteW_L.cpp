/* Sursa C++ Problema "Puncte"
 * Rezolvare: arbori de intervale + rafinament Willard-Lueker
 * Complexitate: O(N*lg N) preprocesare + O(lg N) query */

#include <stdio.h>
#include <stdlib.h>
#define MAXN 100000
#define LGN  18

struct point  {
	int x, y;
} P[MAXN];

typedef struct point point;

int N, M, x1, y1, x2, y2;
int X[MAXN], T[LGN][MAXN], Ptr[LGN][MAXN][2];

int cmp(const void *i, const void *j)
{
	return ((point *)i)->x - ((point *)j)->x;
}

void build(int lv, int l, int r)
{
	int m = (l + r) >> 1, i, j, k;
 	if (l == r) { T[lv][l] = P[l].y; return;}
 	build(lv+1, l, m), build(lv+1, m+1, r);
 	for (i=l, j=m+1, k=l; i <= m || j <= r; )
 	   if (j>r || (i <= m && T[lv + 1][i] < T[lv + 1][j]))
 			Ptr[lv][k][0]=i, Ptr[lv][k][1]=j - 1,
    		T[lv][k++] = T[lv + 1][i++];
    	else
    		Ptr[lv][k][0]=i-1, Ptr[lv][k][1] = j,
    		T[lv][k++] = T[lv + 1][j++];
}

int search(int A[], int l, int r, int v)
{
	int p, step;
  	if (v < A[l]) return l - 1;
  	for (step=1; step<(r - l + 1);step<<= 1);
    	for (p = l; step; step >>= 1)
    		 if (p + step <= r && A[p + step] <= v)
    		   p += step;
    return p;
}

int query(int lv,int l,int r,int p1,int p2)
{
    int m, t = 0;
    if (x1 <= l && r <= x2)
    {
       if (p2 < l || p1 > r) return 0;
       if (p1<l && r<p2) return (r-l + 1);
       if (T[lv][p1] == T[0][y1]) p1--;
       t = p2 - p1;
    }
    else
    {
     	m = (l + r) >> 1;
    	if (x1 <= m)
  		t += query(lv + 1, l, m, Ptr[lv][p1][0],
  		Ptr[lv][p2][0]);
    	if (x2 > m) t += query(lv + 1, m + 1, r, Ptr[lv][p1][1], Ptr[lv][p2][1]);
    }
    return t;
}

int main(void)
{
    FILE *fin, *fout;
    int i;

    fin = fopen("puncte.in", "r");
    fout = fopen("puncte.out", "w");
    fscanf(fin, "%d %d", &N, &M);
    for (i = 0; i < N; i++)
      fscanf(fin, "%d %d",&P[i].x,&P[i].y);

    qsort(P, N, sizeof(point), cmp);
    for (i = 0; i < N; i++) X[i] = P[i].x;

    build(0, 0, N - 1);

    for (; M; M--)
    {
		fscanf(fin, "%d %d %d %d", &x1, &y2, &x2, &y1);
      	if (x2 < X[0] || x1 > X[N - 1] || y2 < T[0][0] || y1 > T[0][N - 1])
          fprintf(fout, "0\n");
    	else
     	{
     		x1 = search(X, 0, N-1, x1-1)+1,
     		x2 = search(X, 0, N-1, x2);
     		y1 = search(T[0],0,N-1,y1-1) + 1,
     		y2 = search(T[0], 0, N - 1, y2);
			fprintf(fout,"%d\n", query(0,0,N-1,y1,y2));
        }
    }
    fclose(fin), fclose(fout);
    return 0;
}


