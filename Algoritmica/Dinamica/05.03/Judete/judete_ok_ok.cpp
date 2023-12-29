// Time complexity O(n^3)
// OK
#include <stdio.h>
#include <vector>
#include <time.h>
using namespace std;

const int MaxN = 128, Inf = 0x3f3f3f3f;
using VI = vector<int>;

VI adj[MaxN];  // arborele
VI v, nr;      // nr[x] de noduri din subarborele cu radacina in x
int n, K;

void ReadData();
void WriteData();

int main()
{
// long T1=clock();
	freopen ("3-JUDETE.IN", "r", stdin);
	freopen ("judete.out", "w", stdout);

	ReadData();
	WriteData();
    
//	printf ("%lf\n",(double)((double)clock()-T1)/CLK_TCK);
	return 0;
}

VI Df(int x)    // tx[k] -  nr minim de orase intr-un judet a.i. k orase (inclusiv x) nu sunt plasate inca
{
	v[x] = nr[x] = 1;
	VI tx(n + 1, Inf);
	tx[1] = 0;  // daca e frunza (si nu o plasez) atunci nu mai am orase plasate in niciun judet
	        
	for (const int& f : adj[x])
	{
		if ( v[f] ) continue;	
		VI tf = Df(f);
		nr[x] += nr[f];
		 
		VI C(n + 1, Inf);
		for (int j = 0; j <= nr[x]; j++)      
			for (int k = 0; k <= nr[f] && j + k <= nr[x]; k++)   
			{
				C[j + k] = min(C[j + k], max(tx[j], tf[k]));    // nu creez un judet (arbore) din j si k
				if ( k >= K)      
					C[j] =  min(C[j], max({tx[j], tf[k], k})); // creez un judet cu k noduri din fiu					
			}
		tx = C;	
	}			
	return tx;
}

void WriteData()
{
	int T = 1 << 20;
	VI t = Df(1);
	for (int i = K; i <= n; i++)
		T = min(T, max(t[i], i));

	printf ("%d\n", T);
}

void ReadData()
{
	scanf("%d%d", &n, &K);
	v = nr = VI(n + 1);
	int a, b;
	for (int i = 1; i < n; i++)
	{
		scanf ("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
}
