// AC SPOJ (4.5 sec)

#include <iostream>
using namespace std;

int p2;
int tree[700000];
int flip[700000];
int lazy[700000];

void push()
{
	 arb[2*nod].val  += arb[nod].lazy;
    arb[2*nod].lazy += arb[nod].lazy;
	
    arb[2*nod + 1].val  += arb[nod].lazy;	
    arb[2*nod + 1].lazy += arb[nod].lazy;

    arb[nod].lazy = 0;	
}
// nu-s multumit de implementare (chiar daca da corect)
void update(int n, int l, int r, int a, int b)
{
	if (l > r) return;
 
	if (flip[n] % 2) // un numar impar de swith-uri, neaga starea bitilor
		tree[n] = (r - l + 1) - tree[n];
	flip[n] = 0;
	flip[n*2] += lazy[n];
	flip[n*2+1] += lazy[n];
	
	lazy[n*2] += lazy[n];
	lazy[n*2+1] += lazy[n];
	lazy[n] = 0;
 
	if (r < a || l > b) return;
 
	if (l >= a && r <= b) 
	{
	    arb[nod].val += add;
        arb[nod].lazy += add;	
        return;
		tree[n] = (r - l + 1) - tree[n];
		lazy[n]++;
		return;
	}
	int m = (l + r) / 2;
	update(2 * n, l, m, a, b);
	update(2 * n + 1, m + 1, r, a, b);
	tree[n] = tree[n*2] + tree[n*2+1];
}

int query(int n, int l, int r, int a, int b)
{
	if (l > r) return 0;
	if (r < a || l > b) return 0;

	if (flip[n] % 2) 
		tree[n] = (r - l + 1) - tree[n];
	flip[n] = 0;
	flip[n*2] += lazy[n];
	flip[n*2+1] += lazy[n];
	lazy[n*2] += lazy[n];
	lazy[n*2+1] += lazy[n];
	lazy[n] = 0;
 
	if (a <= l && r <= b) 
		return tree[n];
	return query(2*n, l, (l+r)/2, a, b) + query(2*n + 1, (l+r)/2 + 1, r, a, b);
}

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	p2 = 1;
	while (p2 < N) p2 *= 2;
 
	while (M--)
	{
		int e, a, b;
		scanf("%d %d %d", &e, &a, &b);
		a--, b--;
		if (e) 
			printf("%d\n", query(1, 0, p2, a, b));
		else 
			update(1, 0, p2, a, b);
	}
}

