#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#define maxn 128

using namespace std;

int n, m, i, j, a, tot;
vector <int> g[maxn];
int viz[maxn], cup_dr[maxn];
string line;

int df(int nod) {
	int i, fiu;
	if (viz[nod])
		return 0;
	viz[nod] = 1;

	for (i = 0; i < g[nod].size(); i++) {
		fiu = g[nod][i];
		if (!cup_dr[fiu]) {
			cup_dr[fiu] = nod;
			return 1;
		}
	}

	for (i = 0; i < g[nod].size(); i++) {
		fiu = g[nod][i];
		if (df(cup_dr[fiu]) == 1) {
			cup_dr[fiu] = nod;
			return 1;
		}
	}

	return 0;
}

int main() {
	freopen("senat.in", "r", stdin);
	freopen("senat.out", "w", stdout);

	scanf("%d%d ", &n, &m);

	for (i = 1; i <= m; i++) {
		getline(cin, line);
		istringstream in(line);
		while (in>>a) 
			g[a].push_back(i);
	}

	for (i = 1; i <= n; i++) {
		memset(viz, 0, sizeof(viz));
		tot += df(i);
	}

	for (i = 1; i <= m; i++)
		if (!cup_dr[i]) {
			printf("0\n");
			return 0;
		}

	for (i = 1; i <= m; i++)
		if (cup_dr[i])
			printf("%d\n", cup_dr[i]);

	return 0;
}

