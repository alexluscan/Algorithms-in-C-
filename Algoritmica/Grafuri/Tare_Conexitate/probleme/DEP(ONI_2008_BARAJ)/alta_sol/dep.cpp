#include <stdio.h>
#include <vector>
#include <bitset>
using namespace std;

#define NMAX 270
#define MOD 666013
#define LL long long

int N, M, K;

vector <int> leg[NMAX];
vector <int> legi[NMAX];

vector <int> legci[NMAX];

vector <int> legf[NMAX];

bitset <NMAX> exlegc[NMAX];

int xx[NMAX * NMAX];
int yy[NMAX * NMAX];

int gout[NMAX];

int coada[NMAX];

int ncomp;
vector <int> comp[NMAX];
int ap_comp[NMAX];
int comp_size[NMAX];

int st[NMAX];
char viz[NMAX];

void back1(int x)
{
	viz[x] = 1;

	vector <int> :: iterator it;
	for (it = leg[x].begin(); it != leg[x].end(); ++it)
		if (!viz[*it]) back1(*it);

	st[++st[0]] = x;
}

void back2(int x)
{
	viz[x] = 1;

	comp[ncomp].push_back(x);
	ap_comp[x] = ncomp;

	vector <int> :: iterator it;
	for (it = legi[x].begin(); it != legi[x].end(); ++it)
		if (!viz[*it]) back2(*it);
}

int din[NMAX][NMAX];

int ant[NMAX];
int cur[NMAX];

void solve(int x)
{
	vector <int> :: iterator it;

	for (it = legf[x].begin(); it != legf[x].end(); ++it)
		solve(*it);

	memset(ant, 0, sizeof(ant));

	ant[ comp_size[x] ] = 1;
	int y, i, j;

	for (it = legf[x].begin(); it != legf[x].end(); ++it) {
		y = *it;

		for (i = 0; i <= K; i++) {
			if (!ant[i]) continue;
			for (j = 0; j <= K && i + j <= K; j++) {
				if (!din[y][j]) continue;
				cur[i + j] += ((LL) ant[i] * din[y][j]) % MOD;
				if (cur[i + j] >= MOD) cur[i + j] -= MOD;
			}
		}

		memcpy(ant, cur, sizeof(ant));
		memset(cur, 0, sizeof(cur));
	}
	ant[0] = 1;

	memcpy(din[x], ant, sizeof(ant));
}

int main()
{
	int i, x, y;
	
	freopen("dep.in", "r", stdin);
	freopen("dep.out", "w", stdout);

	scanf("%d %d %d", &N, &M, &K);

	for (i = 1; i <= M; i++) {
		scanf("%d %d", &x, &y);

		xx[i] = x; yy[i] = y;

		leg[x].push_back(y);
		legi[y].push_back(x);
	}

	// componente tare conexe

	for (i = 1; i <= N; i++)
		if (!viz[i]) back1(i);

	memset(viz, 0, sizeof(viz));
	for (i = st[0]; i >= 1; i--) {
		if (viz[ st[i] ]) continue;

		ncomp++;
		back2(st[i]);
	}

	for (i = 1; i <= ncomp; i++) comp_size[i] = comp[i].size();


/*	int j;
	for (i = 1; i <= ncomp; i++) {
		for (j = 0; j < comp_size[i]; j++) printf("%d ", comp[i][j]);
		printf("\n");
	}
	printf("\n");
*/
	for (i = 1; i <= M; i++) {
		x = ap_comp[xx[i]]; y = ap_comp[yy[i]];

		if (x == y) continue;
		if (exlegc[x][y] == 1) continue;
		exlegc[x][y] = 1;
		legci[y].push_back(x);
		gout[x]++;
	}

	// sortare topologica si legaturile finale

	int p = 0, q = -1;
	for (i = 1; i <= ncomp; i++)
		if (!gout[i]) {
			legf[0].push_back(i);
			coada[++q] = i;
		}

	vector <int> :: iterator it;
	while (p <= q) {
		x = coada[p++];
		for (it = legci[x].begin(); it != legci[x].end(); ++it) {
			y = *it;
			gout[y]--;
			if (!gout[y]) {
				legf[x].push_back(y);
				coada[++q] = y;
			}
		}
	}		

	solve(0);

	printf("%d\n", din[0][K]);
	
return 0;
}

