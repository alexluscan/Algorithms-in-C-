#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN  100005

vector<int> adj[MAXN], niv, low, ans, con;
stack<pair<int, int>> stk;
int n;

void read_in()
{
    ifstream in("pamant.in");
    int cnt_edges, x, y;

    for (; cnt_edges > 0; -- cnt_edges) 
    {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    in.close();
}

void DF(int x, int fn, int number)
{
    int critical = false;
    int sons = 0;

    niv[x] = low[x] = number;
    for (auto y :  adj[x]) 
    {
        if (y == fn)   continue ;
        if (niv[y] == -1) 
        {
            stk.push({x, y});
            DF(y, x, number + 1);
            low[x] = min(low[x], low[y]);
            critical |= (low[y] >= niv[x]);
            sons ++;
        }
        else
            low[x] = min(low[x], niv[y]);
    }
    
    if (x != fn) 
    {
        if (critical)
            ans.push_back(x);
    } else if (sons > 1)
        ans.push_back(x);
}

int main(void)
{
    read_in();
    niv.resize(n + 1), niv.assign(n + 1, -1);
    low.resize(n + 1);

    for (int i = 1; i <= n; ++ i) if (niv[i] == -1)
        con.push_back(i), DF(i, i, 0);

    ofstream out("pamant.out");
    sort(con.begin(), con.end());
    out << con.size() << "\n";
    for (int i = 0; i < (int) con.size(); ++ i)
        out << con[i] << " ";  
    out << "\n";

    sort(ans.begin(), ans.end());
    out << ans.size() << "\n";
    for (int i = 0; i < (int) ans.size(); ++ i)
        out << ans[i] << " ";  
    
    out.close();

    return 0;
}

