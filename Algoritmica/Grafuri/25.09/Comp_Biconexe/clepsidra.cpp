#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 300010
#define MOD 666013

vector<int> G[MAXN];
int L[MAXN], niv[MAXN], Ans[MAXN], Power[MAXN];
bool s[MAXN];
int N, M;

void Df(int x, int tata)
{
	s[x] = true;
	L[x] = niv[x] = niv[tata] + 1;
	int nr = 1;
	if (x == 1) nr = 0;
	
	for (const int& y : G[x])
	{
		if (y == tata) continue;
		
		if ( !s[y] ) // muchie de arbore
		{	
			Df(y, x);
			if (L[y] >= niv[x])
				++nr;
			L[x] = min(L[x], L[y]);
		}
		else // muchie de intoarcere
			L[x] = min(L[x], niv[y]);
	}
	Ans[x] = Power[nr];
}

int main()
{
	freopen("clepsidra.in","r",stdin);
	freopen("clepsidra.out","w",stdout);
	
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; ++i)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	
	Power[0] = 1; 
	for (int i = 1; i <= N; ++i)
		Power[i] = (Power[i - 1] * 2) % MOD;
	
	for (int i = 1; i <= N; ++i)
		Power[i] = (Power[i] + MOD - 2) % MOD;
	
	Df(1, 0);
	
	for (int i = 1; i <= N; ++i)
		printf("%d\n", Ans[i]);
	return 0;
}
