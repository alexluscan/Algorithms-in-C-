#define TuTTy "Cosmin-Mihai Tutunaru"
#include<cstdio>
#include<vector>
#include<algorithm>
#define infile "pamant.in"
#define outfile "pamant.out"
#define nMax 100013

using namespace std;

vector <int> comp;
vector <int> crit;
vector <int> v[nMax];
bool vz[nMax];
int ord[nMax];
int curOrd;
int n, m;

void getComp(int x) {
  vz[x] = true;

  for(unsigned i = 0; i < v[x].size(); ++i)
    if(!vz[v[x][i]])
      getComp(v[x][i]);
}

void getCrit(int x, int f) {
  ord[x] = ++curOrd;

  for(unsigned i = 0; i < v[x].size(); ++i)
    if(!ord[v[x][i]]) {
      getCrit(v[x][i], x);
      if(ord[v[x][i]] > ord[x] && v[x].size() > 1)
        crit.push_back(x);
    }

  for(unsigned i = 0; i < v[x].size(); ++i)
    if(v[x][i] != f)
      ord[x] = min(ord[x], ord[v[x][i]]);
}

void read() {
  scanf("%d %d\n", &n, &m);
  for(int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d\n", &x, &y);
    v[x].push_back(y);
    v[y].push_back(x);
  }
}

void solve() {
  for(int i = 1; i <= n; ++i)
    if(!vz[i]) {
      comp.push_back(i);
      getComp(i);
      getCrit(i, 0);
    }

  sort(crit.begin(), crit.end());
  crit.resize(unique(crit.begin(), crit.end()) - crit.begin());
}

void write() {
  printf("%d\n", comp.size());
  for(unsigned i = 0; i < comp.size(); ++i)
    printf("%d ", comp[i]);
  printf("\n");

  printf("%d\n", crit.size());
  for(unsigned i = 0; i < crit.size(); ++i)
    printf("%d ", crit[i]);
  printf("\n");
}

int main() {
  freopen(infile, "r", stdin);
  freopen(outfile, "w", stdout);

  read();
  solve();
  write();

  fclose(stdin);
  fclose(stdout);
  return 0;
}
