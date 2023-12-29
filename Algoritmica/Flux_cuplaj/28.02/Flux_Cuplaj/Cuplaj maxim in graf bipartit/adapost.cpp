#include <cstdio>
#include <math.h>
#include <vector>
#include <cstring>
#include <algorithm>
#define maxn 805
#define inf 0x3f3f3f3f

using namespace std;

struct punct {
	int x, y;
};

int n, i, j;
double aa, bb;
punct v[maxn];
int viz[maxn], cup_st[maxn], cup_dr[maxn];
long long dist_min, cost_min;
int dist[maxn][maxn];
int cb[maxn * maxn], nr;
int ok;
vector <int> g[maxn], cst[maxn];
int up[maxn];
int dmin[maxn];
int f[maxn][maxn], c[maxn][maxn], cost[maxn][maxn];
int src, dst;
int heap[2 * maxn], heap_sz, sum, poz_heap[maxn];

inline int distanta(punct a, punct b) {
	return (int) sqrt(1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y));
}

inline int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

inline void build_graf(int dmax) {
	int i, j;
	for (i = 1; i <= 2 * n; i++)
		g[i].clear();
	for (i = 1; i <= n; i++) {
		for (j = n + 1; j <= 2 * n; j++) 
			if (dist[i][j] <= dmax) {
				g[i].push_back(j);
			}
	}
		
}

void cupleaza(int nod, int pt) {
	int i, fiu;

	if (viz[nod])
		return;
	viz[nod] = 1;

	if (pt == 0) {
		for (i = 0; i < g[nod].size(); i++) {
			fiu = g[nod][i];
			cupleaza(fiu, 1);
			if (ok) {
				cup_st[nod] = fiu;
				cup_dr[fiu] = nod;
				return;
			}
		}
	}

	else {
		if (cup_dr[nod]) 
			cupleaza(cup_dr[nod], 0);
		else {
			ok = 1;
			return;
		}
	}
}

inline bool posibil(int dmax) {
	int i, nr = 0;
	build_graf(dmax);

	memset(cup_st, 0, sizeof(cup_st));
	memset(cup_dr, 0, sizeof(cup_dr));

	for (i = 1; i <= n; i++) 
		if (!cup_st[i]) {
			ok = 0;
			memset(viz, 0, sizeof(viz));
			cupleaza(i, 0);
			nr += ok; 
		}

	if (nr == n)
		return true;
	return false;

}

void bsearch(int left, int right) {
	int m;
	while (left <= right) {
		m = (left + right) / 2;
		if (posibil(cb[m])) {
			if (cb[m] < dist_min)
				dist_min = cb[m];
			right = m - 1;
		}
		else
			left = m + 1;
	}
}

inline void afis(long long nr) {
	printf("%lld.", nr / 1000000);
	int aux = nr % 1000000;
	if (aux)
		while (aux < 100000) {
			printf("0");
			aux *= 10;
		}
	printf("%lld ", nr % 1000000);
}

void build_graf_flux() {
	src = 0; dst = 2 * n + 1;
	for (i = src; i <= dst; i++)
		g[i].clear();
	for (i = 1; i <= n; i++) {
		g[src].push_back(i);
		cst[src].push_back(0); cst[i].push_back(0);
		g[i].push_back(src);
		c[src][i] = 1;
	}

	for (i = n + 1; i <= 2 * n; i++) {
		g[i].push_back(dst);
		g[dst].push_back(i);
		cst[dst].push_back(0); cst[i].push_back(0);
		c[i][dst] = 1;
	}

	for (i = 1; i <= n; i++)
		for (j = n + 1; j <= 2 * n; j++)
			if (dist[i][j] <= dist_min) {
				g[i].push_back(j);
				cst[i].push_back(dist[i][j]);
				g[j].push_back(i);
				cst[j].push_back(-dist[i][j]);
				c[i][j] = 1;
			}
	memset(viz, 0, sizeof(viz));
}

inline void init() {
	memset(dmin, 0x3f, sizeof(dmin));
	dmin[src] = 0;
	ok = 0;
}

inline void swap(int &a, int &b) {
	int aux;
	aux = a; a = b; b = aux;
}

inline void heap_up(int no) {
	int nod = no, ss;
	while (nod > 1) {
		ss = nod / 2;
		if (dmin[heap[nod]] < dmin[heap[ss]]) {
			swap(heap[nod], heap[ss]);
			poz_heap[heap[nod]] = nod;
			poz_heap[heap[ss]] = ss;
			nod = ss;
		}
		else
			break;
	}
}

inline void heap_down(int no) {
	int nod = no, l, r;
	while (2 * nod <= heap_sz) {
		l = 2 * nod; r = 2 * nod + 1;
		if (dmin[heap[nod]] > min(dmin[heap[l]], dmin[heap[r]])) {
			if (dmin[heap[l]] < dmin[heap[r]]) {
				swap(heap[nod], heap[l]);
				poz_heap[heap[nod]] = nod;
				poz_heap[heap[l]] = l;
				nod = l;
			}
			else {
				swap(heap[nod], heap[r]);
				poz_heap[heap[nod]] = nod;
				poz_heap[heap[r]] = r;
				nod = r;
			}
		}
		else
			break;
	}
}

inline int dijkstra() {
	int i, j, nod, fiu, fmin;

	for (i = src; i <= dst; i++)
		for (j = 0; j < g[i].size(); j++) {
			fiu = g[i][j];
			if (dmin[i] != inf && dmin[fiu] != inf)
				cst[i][j] += dmin[i] - dmin[fiu];
		}

	init();

	for (i = src; i <= dst; i++) {
		heap[i + 1] = i;
		poz_heap[i] = i + 1;
	}

	heap_sz = dst + 1;

	while (heap_sz > 1 && dmin[heap[1]] != inf) {
		nod = heap[1];
		int gs = g[nod].size();
		for (i = 0; i < gs; i++) {
			fiu = g[nod][i];
			if (f[nod][fiu] < c[nod][fiu] && dmin[nod] + cst[nod][i] < dmin[fiu]) {		
				dmin[fiu] = dmin[nod] + cst[nod][i];
				up[fiu] = nod;
				heap_up(poz_heap[fiu]);
			}
		}

		heap[1] = heap[heap_sz];
		heap[heap_sz] = dst + 1;
		heap_sz--;
		heap_down(1);
	}

	if (dmin[dst] == inf) 
		return 0;

	ok = 1;

	for (i = dst; i != src; i = up[i]) {
		f[up[i]][i] ++;
		f[i][up[i]] --;
	}

	sum += dmin[dst];
	return sum;
}

void flux() {
	memset(dmin, 0x3f, sizeof(dmin));
	dmin[0] = 0;

	for (i = dst + 1; i < 2 * maxn; i++)
		heap[i] = dst + 2;
	ok = 1;
	while (ok) {
		ok = 0;
		cost_min += dijkstra();
	}
}


int main() {
	freopen("adapost.in", "r", stdin);
	freopen("adapost.out", "w", stdout);

	scanf("%d", &n);
	for (i = 1; i <= 2 * n; i++) {
		scanf("%lf%lf", &aa, &bb);
		v[i].x = (int) (aa * 1000000);
		v[i].y = (int) (bb * 1000000);
	}

	dist_min = inf;
	for (i = 1; i <= n; i++)
		for (j = n + 1; j <= 2 * n; j++) {
			dist[i][j] = distanta(v[i], v[j]);
			dist[j][i] = dist[i][j];
			nr++;
			cb[nr] = dist[i][j];
		}

	sort(cb + 1, cb + nr + 1);

	bsearch(1, nr);
	afis(dist_min);

	build_graf_flux();
	flux();

	afis(cost_min);
	

	return 0;
}
