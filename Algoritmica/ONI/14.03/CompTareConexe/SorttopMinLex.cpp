#include <vector>
#include <set>
#include <iostream>
using namespace std;

using VI  = vector<int>;
using VVI = vector<VI>;

VVI G;
int n, m;
set<int> S; 
VI gi; /// gi[x] = gradul interior al nodului x

void CitesteGraf();
void SortTop();

int main()
{
    CitesteGraf();
    SortTop();
    return 0;
}


void SortTop()
{
    for (int x = 1; x <= n; x++)
        if (gi[x] == 0)
            S.insert(x);
    int x;
    while (!S.empty())
    {
        
        x = *(S.begin());
        S.erase(x);  // log(size)
        cout << x << " ";
        
        for (int y : G[x])
        {
            gi[y]--;
            if (gi[y] == 0)
                S.insert(y);
        }
    }
}

void CitesteGraf()
{
    cin >> n >> m;
    G = VVI(n + 1);
    gi = VI(n + 1);
    int x, y;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        G[x].push_back(y);
        gi[y]++;
    }
}
