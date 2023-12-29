#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;

ifstream fin ("pm.in");
ofstream fout ("pm.out");

#define eb emplace_back

using VI = vector<int>;
using VVI = vector<VI>;

VVI G;
const int dim = 105;
int n, m, c[105], a[105], tim[105], t[105], mx[105], maxi;
bool v[105];
stack<int> st;

inline void DF(int x);
inline void DFS(int x);

int main()
{
    fin >> n;
    for (int i = 1; i <= n; ++i)
        fin >> c[i];
    int N;

    G = VVI(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        int x;
        fin >> N;
        for (int j = 1; j <= N; ++j)
        {
            fin >> x;
            G[x].eb(i);
        }
    }

    for (int i = 1; i <= n; ++i)
        if (!v[i])
            DF(i);
    for (int i = 1; i <= n; ++i)
        if (t[i] == 0)
        {
            tim[i] = c[i];
            mx[i] = c[i];
            DFS(i);
        }
    for (int i = 1; i <= n; ++i)
        maxi = max(maxi, tim[i]);
    fout << maxi << '\n';
    for (int i = 1; i <= n; ++i)
    {
        int val = tim[i] - c[i];
        fout << val << ' ' << maxi - mx[i] + val << '\n';
    }
}

inline void DF(int x)
{
    v[x] = true;
    for (const auto& y : G[x])
        if (!v[y])
        {
            t[y] = x;
            DF(y);
        }
    //st.push(x);
}

inline void DFS(int x)
{
    v[x] = true;
    for (const auto& y : G[x])
        {
            tim[y] = max(tim[y], c[y] + tim[x]);
            mx[y] = max(mx[y], tim[y]);
            DFS(y);
            mx[x] = max(mx[x], mx[y]);
        }

}

