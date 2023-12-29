/* Se dau n segmente orizontale si verticale. 
 * Sa se determine numarul punctelor de intersectie.
 * Complexitate: O(N * lg MAXC)
 */
#include <stdio.h>
#include <algorithm>
using namespace std;

struct Entry {
    int x, y1, y2, sgn;
    bool operator < (const Entry& e) const
    {
		return x < e.x || (x == e.x && sgn > e.sgn);
	}
};

Entry A[50000]; // retine capetele (stanga si dreapta) a seg, orizontale si segmentele verticale
int N, T[131072];
long long Res;


int query(int n, int l, int r, int a, int b)
{
   if (a <= l && r <= b)  // recompun [a, b] din intervale [l, r] din arbore
       return T[n];       // ies, pt ca interv atasate fiilor nu mai pot aduce alte intevale pt completarea lui [a, b]
	
    int m, t = 0;   
	m = (l + r) / 2;
	
    if (a <= m) 
		t += query(2 * n, l, m, a, b);
    if (b > m)  
		t += query(2 * n + 1, m + 1, r,  a, b);
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
       update(2*n + 1,m + 1, r, p, v);
}

int main()
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
         A[n].x = x1, A[n].sgn = 0,  
         A[n].y1 = y1, A[n++].y2 = y2; // capatul de jos si cel de sus
    }
    fclose(f);

    sort(A, A + n); // sorteaza capetele dupa x, apoi dupa sgn: 
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

