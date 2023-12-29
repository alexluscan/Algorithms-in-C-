/* Sursa C++ Problema "Segment"
   Complexitate: O(N * lg MAXC)
 */
#include <stdio.h>
#include <stdlib.h>

struct entry {
    int x, y1, y2, sgn;
} A[50000];

typedef struct entry entry;

int N, T[131072];
long long Res;

int cmp(const void *i,const void *j)
{
   entry *ei = (entry *) i, *ej = (entry *) j;

    if (ei->x != ej->x)
       return ei->x - ej->x;    // ordoneaza dupa x
    return ej->sgn - ei->sgn;   // la x egal ordoneaza dupa sgn
}

int query(int n, int l, int r, int a, int b)
{
    int m, t = 0;   // t putea fi un sir global

   if (a <= l && r <= b)  // recompun [a, b] din intervale [l, r] din arbore
       return T[n];       // ies, pt ca interv atasate fiilor nu mai pot aduce alte intevale pt completarea lui [a, b]

	m = (l + r) / 2;
    if (a <= m) t += query(2 * n, l, m, a, b);
    if (b > m)  t +=query(2*n+1,m+1,r, a, b);
    return t;
}

void update(int n, int l, int r, int p, int v) // v trebuie adaugat in toate intervalele care-l contin pe p
{
    int m = (l + r) / 2;

    T[n] += v;
    if (l == r) return;   // updatez inclusiv frunza care e intervalul[p,p]
    if (p <= m)           // p apartine sigur intervalului [l,m]
       update(2 * n, l, m, p, v); // drumul spre frunza e unic, deci else
    else
       update(2*n+1,m+1, r, p, v);
}

int main(void)
{
    FILE *f;
    int i, n, x1, y1, x2, y2;

    f = fopen("segment.in", "r");
    fscanf(f, "%d", &N);             // nr segmente
    for (n = i = 0; i < N; i++)
    {
     	fscanf(f, "%d %d %d %d", &x1, &y1, &x2, &y2);    // in sirul A plasam si puncte si segmente :
     	                                                 //  
      	if (y1 == y2)     // orizontal       
        	A[n].x = x1, A[n].sgn = +1,   //capatul din stanga
       		A[n++].y1 = y1,               // y2 nu are rost sa-l mai completez
        	A[n].x = x2, A[n].sgn = -1,   // capatul din dreapta
        	A[n++].y1 = y1;
      	else
        if (x1 == x2)    // vertical
         A[n].x = x1, A[n].sgn = 0,  // capatul de jos
         A[n].y1=y1,A[n++].y2 = y2;
    }
    fclose(f);

    qsort(A, n, sizeof(entry), cmp); // sorteaza capetele dupa x, apoi dupa sgn: 
                                     // la acelasi x: sorteaza dupa capat stanga, segm vertical, capat dreapta 
    for (i = 0; i < n; i++)
    if (A[i].sgn == 0)       // segm vertical
       Res += query(1, 0, 49999, A[i].y1, A[i].y2); // nr de intersectii ale lui cu segm orizontale
    else
       update(1, 0, 49999, A[i].y1, A[i].sgn); // introduce sau scoate un capat de segm in arbore (cu + sau - )

    f = fopen("segment.out", "w");
    fprintf(f, "%lld\n", Res);
    fclose(f);

    return 0;
}

