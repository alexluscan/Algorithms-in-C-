#include <iostream>
#include <vector>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;

int t, n, m, v[100005];

VVI G;
VI L, R;

bool DoMatch(int x)
{
    if ( v[x] ) return false;
    v[x] = true;
    for (const int& y : G[x])
        if ( !R[y] || DoMatch(R[y]) )
        {
            L[x] = y;
            R[y] = x;
            return true;
        }
    return false;
}

int mm;

int main()
{
    cin >> t;
    while (t--)
    {
        mm = 0;
        cin >> n >> m;
        L = R = VI(n, 0);
        G = VVI(n);
        for (int i = 1; i <= n; ++i)
        {
            int x, y;
            cin >> x >> y;
            G[i].push_back(x);
            G[i].push_back(y);
        }

        for (int i = 1; i <= n; ++i)
            if ( !L[i] && DoMatch(i) )
                mm++;
        if (mm == n)
            cout << "DA\n";
        else
            cout << "NU\n";
    }
}
