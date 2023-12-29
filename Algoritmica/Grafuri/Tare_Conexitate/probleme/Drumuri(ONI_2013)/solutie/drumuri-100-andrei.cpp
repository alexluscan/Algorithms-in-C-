#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int lg = 150005;

bool fst[lg];
vector<int> v[lg], w[lg], vec[lg], rev_vec[lg];
vector<pair<int, int> > muchii;
vector<int> top_sort;
int postordine[lg];
vector<vector<int> > comps;
int which[lg];
int nr_tare;
int cnt[2][lg];
int n, m;
bool good[lg];
int index[lg];

void df1(int nod) {
  fst[nod] = true;

  for (int i = 0; i < (int)v[nod].size(); i++) {
    if (fst[v[nod][i]] == false) {
      df1(v[nod][i]);
    }
  }

  postordine[++postordine[0]] = nod;
}
void df2(int nod) {
  comps[comps.size() - 1].push_back(nod);
  fst[nod] = false;
  which[nod] = nr_tare;

  for (int i = 0; i < (int)w[nod].size(); i++) {
    if (fst[w[nod][i]] == true) {
      df2(w[nod][i]);
    }
  }
}

void doSort(int nod) {
  fst[nod] = true;

  for (int i = 0; i < (int)vec[nod].size(); i++) {
    if (fst[vec[nod][i]] == false) {
      doSort(vec[nod][i]);
    }
  }

  top_sort.push_back(nod);
}

void calcAll(vector<int> top, vector<int> rec[lg], int s) {
  for (int i = 0; i < (int)top.size(); i++) {
    index[top[i]] = i;
  }

  for (int i = 0; i < (int)top.size(); i++) {
    cnt[s][top[i]]++;

    int mn = -1;
    for (int j = 0; j < (int)rec[top[i]].size(); j++) {
      if (mn == -1 || index[rec[top[i]][j]] < index[mn]) {
        mn = rec[top[i]][j];
      }
    }
    if (mn != -1) {
      cnt[s][mn] += cnt[s][top[i]];
    }
  }
}

int main() {
  freopen("drumuri.in", "rt", stdin);
  freopen("drumuri.out", "wt", stdout);

  scanf("%d%d", &n, &m);

  for (int i = 1; i <= m; i++) {
    int x, y;

    scanf("%d%d", &x, &y);

    v[x].push_back(y);
    w[y].push_back(x);

    muchii.push_back(make_pair(x, y));
  }

  for (int i = 1; i <= n; i++) {
    if (fst[i] == false) {
      df1(i);
    }
  }

  for (int i = n; i > 0; i--) {
    if (fst[postordine[i]] == true) {
      nr_tare++;

      comps.push_back(vector<int>());

      df2(postordine[i]);
    }
  }

  for (int i = 1; i <= n; i++) {
    //printf("%d %d\n", i, which[i]);
  }

  for (int i = 0; i < m; i++) {
    if (which[muchii[i].first] != which[muchii[i].second]) {
      vec[which[muchii[i].first]].push_back(which[muchii[i].second]);

      rev_vec[which[muchii[i].second]].push_back(which[muchii[i].first]);
    }
  }

  for (int i = 1; i <= nr_tare; i++) {
    if (fst[i] == false) {
      doSort(i);
    }
  }

  calcAll(top_sort, rev_vec, 0);

  reverse(top_sort.begin(), top_sort.end());

  for (int i = 0; i < (int)top_sort.size(); i++) {
    //printf("%d\n", top_sort[i]);
  }

  calcAll(top_sort, vec, 1);

  for (int i = 1; i <= nr_tare; i++) {
    //printf("%d %d\n", i, cnt[0][i] + cnt[1][i]);
  }

  int nr_rez = 0;
  for (int i = 1; i <= nr_tare; i++) {
    if (cnt[0][i] + cnt[1][i] == nr_tare + 1) {
      for (int j = 0; j < (int)comps[i - 1].size(); j++) {
        nr_rez++;
        good[comps[i - 1][j]] = true;
      }
    }
  }

  printf("%d\n", nr_rez);
  for (int i = 1; i <= n; i++) {
    if (good[i] == true) {
      printf("%d ", i);
    }
  }
  printf("\n");

  return 0;
}

