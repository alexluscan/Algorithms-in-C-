#include <cstdio>
#include <vector>
#define maxn 10100

using namespace std;

int n, m, e, i, j, a, b, sol, ok, nrt, tt;
vector <int> v[maxn];
int viz[2 * maxn];
int cup[2 * maxn], cup_st[maxn];

int cupleaza(int nod) {
	int i, fiu;
	if (viz[nod] == 1)
		return 0;
	viz[nod] = 1;
	
	for (i = 0; i < v[nod].size(); i++) {
		fiu = v[nod][i];
		if (!cup[fiu]) {
			cup[fiu] = nod;
			cup_st[nod] = 1;
			return 1;
		}
	}
	
	for (i = 0; i < v[nod].size(); i++) {
		fiu = v[nod][i];
		if (cup[fiu])
			if (cupleaza(cup[fiu])) {
				cup[fiu] = nod;
				cup_st[nod] = 1;
				return 1;
			}
	}
	
	return 0;
}

void init() {
	int i;
	memset(cup, 0, sizeof(cup));
	for (i = 0; i < 2 * maxn; i++)
		v[i].clear();
	memset(viz, 0, sizeof(viz));
	memset(cup_st, 0, sizeof(cup_st));
}

int main() {
	freopen("java.in", "r", stdin);
	freopen("java.out", "w", stdout);
	
	scanf("%d", &nrt);
	
	for (tt = 1; tt <= nrt; tt++) {
		init();
		scanf("%d%d%d", &n, &m, &e);
		for (i = 1; i <= e; i++) {
			scanf("%d%d", &a, &b);
			b += n;
			v[a].push_back(b);
		}
		
		sol = 0;
		ok = 1;
		while (ok) {
			ok = 0;
			memset(viz, 0, sizeof(viz));
			
			for (i = 1; i <= n; i++) 
				if (!cup_st[i])
					if (cupleaza(i)) {
						sol++;
						ok = 1;
					}
		}
		
		printf("%d\n", sol);
	/*	for (i = n + 1; i <= n + m; i++)
			if (cup[i]) {
				printf("%d %d\n", cup[i], i - n);
			}*/
	}
	return 0;
}
