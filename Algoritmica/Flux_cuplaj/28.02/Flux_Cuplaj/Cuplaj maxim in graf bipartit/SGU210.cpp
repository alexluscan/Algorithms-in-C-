#include <cstdio>
#include <algorithm>
#include <vector>
#define maxn 410

using namespace std;

int a[maxn];
vector <int> v[maxn];
int n, i, j, nr, t;
int cup_st[maxn], cup_dr[maxn];
int ok, viz[maxn], x[maxn];

void cupleaza(int nod, int pt) {
    int i, j, fiu;
    
    if (pt == 1) {
        if (viz[nod])
            return;
        viz[nod] = 1;
        
        for (i = 0; i < v[nod].size(); i++) {
            fiu = v[nod][i];
            cupleaza(fiu, 0);
            if (ok) {
                cup_st[nod] = fiu;
                cup_dr[fiu] = nod;
                return;   
            }
        }
    }
    else {
        if (cup_dr[nod])
            cupleaza(cup_dr[nod], 1);   
        else {
            ok = 1;
            return;   
        }
    }   
}

bool cmp(int xa, int xb) {
	if (a[xa] > a[xb])
		return true;
	return false;
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("data.in", "r", stdin);
        freopen("data.out", "w", stdout);
    #endif
    
    
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (i = 1; i <= n; i++) {
        scanf("%d", &nr);
        for (j = 1; j <= nr; j++) {
            scanf("%d", &t);
            v[i].push_back(t);
        }
		x[i] = i;
    }
    
	sort(x + 1, x + n + 1, cmp);
    
    for (i = 1; i <= n; i++)
        if (!cup_st[x[i]]) {
            ok = 0;
            memset(viz, 0, sizeof(viz));
            cupleaza(x[i], 1);   
        }
     
    for (i = 1; i <= n; i++)
        printf("%d ", cup_st[i]);       

    return 0;
}

