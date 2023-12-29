#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX_N 260
#define FIN "dep.in"
#define FOUT "dep.out"
#define MOD 666013


typedef vector<int> VI;
int N, M, K, C[MAX_N], cnt[MAX_N], deg[MAX_N], ncomp;
char G[MAX_N][MAX_N], GC[MAX_N][MAX_N];
FILE *in,*out;

void combine(VI &a, VI b)
{
	int i, j;
	VI c(K+1);
	for (i = 0; i <= K; ++i) if (a[i])
		for (j = 0; i+j <= K; ++j) if (b[j])
			c[i+j] = ((long long)a[i]*b[j] + c[i+j])%MOD;
	a = c;
}



VI solve(int n)
{
	int i;
	VI t(K+1, 0), ret(K+1, 0);
	t[0] = 1;
	for (i = 1; i <= ncomp; ++i)
		if (GC[i][n] && deg[i] == deg[n]+1)
			combine(t, solve(i));

	for (i = K; i >= cnt[n]; --i)
		ret[i] = t[i-cnt[n]];
	ret[0] = 1;
	return ret;
}



int main(void) 

{
	int i, j, k;
	in=fopen("dep.in","r");
	out=fopen("dep.out","w");
	fscanf(in,"%d %d %d", &N, &M, &K);
	for (; M; --M)
	{
		fscanf(in,"%d %d", &i, &j);
		G[i-1][j-1] = 1;
	}
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			 G[i][j] |= G[i][k] & G[k][j];


	for (i = 0; i < N; ++i)
	{
		if (C[i]) continue;
		C[i] = ++ncomp;
		for (j = i+1; j < N; ++j)
			if (G[i][j] && G[j][i]) C[j] = C[i];
	}

	for (i = 0; i < N; ++i)
	{
		cnt[C[i]]++;
		for (j = 0; j < N; ++j)
		{
			if (!G[i][j] || GC[C[i]][C[j]] || C[i] == C[j]) continue;
			GC[C[i]][C[j]] = 1;
			deg[C[i]]++;
		}
	}

	VI ret(K+1, 0);
	ret[0] = 1;
	for (i = 1; i <= ncomp; ++i)
		if (!deg[i]) combine(ret, solve(i));
	fprintf(out,"%d\n", ret[K]);
	fclose(in);
	fclose(out);
		return 0;
}
