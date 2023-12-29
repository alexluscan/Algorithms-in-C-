#include <fstream>
#include <map>
#include <vector>
 
using namespace std;
 
const int N_MAX = 1e5;
 
ifstream fin("cadrane.in");
ofstream fout("cadrane.out");
 
int N, M;
pair<int, int> p[N_MAX + 5];
 
map<int, int> y;
int cnt[N_MAX + 5];
int leaves[N_MAX + 5];
 
struct { int val, mn; } st[4 * N_MAX + 5];
 
map<int, vector<int>> x;
 
int ans;
 
void BuildSegmentTree(int node, int l, int r) {
   if (l == r) {
      st[node].mn = st[node].val = leaves[l];
      return;
   }
 
   int ls = node << 1, rs = ls + 1;
   int m = (l + r) >> 1;
 
   BuildSegmentTree(ls, l, m);
   BuildSegmentTree(rs, m + 1, r);
 
   st[node].mn = min(st[ls].mn, st[rs].mn);
}
 
void Update(int node, int l, int r, int ul, int ur, int val) {
   if (ur < l || r < ul)
      return;
 
   if (ul <= l && r <= ur) {
      st[node].val += val;
      st[node].mn += val;
      return;
   }
 
   int ls = node << 1, rs = ls + 1;
   int m = (l + r) >> 1;
 
   st[ls].val += st[node].val;
   st[ls].mn += st[node].val;
   st[rs].val += st[node].val;
   st[rs].mn += st[node].val;
   st[node].val = 0;
 
   Update(ls, l, m, ul, ur, val);
   Update(rs, m + 1, r, ul, ur, val);
 
   st[node].mn = min(st[ls].mn, st[rs].mn);
}
 
int main() {
   fin >> N;
   for (int i = 0; i < N; ++i) {
      fin >> p[i].first >> p[i].second;
      y[p[i].second] = 0;
   }
 
   for (auto& it : y)
      it.second = ++M;
   for (int i = 0; i < N; ++i) {
      ++cnt[y[p[i].second]];
      x[p[i].first].push_back(y[p[i].second]);
   }
 
   for (int i = 1, s = N; i <= M; s -= cnt[i++])
      leaves[i] = s;
   BuildSegmentTree(1, 1, M);
 
   for (const auto& it : x) {
      for (int y : it.second)
         Update(1, 1, M, y + 1, M, 1);
      ans = max(ans, st[1].mn);
      for (int y : it.second)
         Update(1, 1, M, 1, y - 1, -1);
   }
 
   fout << ans << "\n";
   return 0;
}
