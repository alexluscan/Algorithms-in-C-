#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("text.in");

using VI = vector<int>;
using VVI = vector<VI>;

VI L, R;
VI G[2];
bool v[200000 + 5];

bool DoMatch(int x)
{
    int y;
    if ( v[x] ) return false;
    v[x] = true;
    y = G[0][x];
        if ( !R[y] || DoMatch(R[y]) )
        {
            L[x] = y;
            R[y] = x;
            return true;
        }
    y = G[1][x];
        if ( !R[y] || DoMatch(R[y]) )
        {
            L[x] = y;
            R[y] = x;
            return true;
        }
    return false;
}

int main()
{
    int t, n, m, mm;
    cin >> t;
    while(t--)
    {
        mm = 0;
        int x, y;
        cin >> n >> m;
        L = R = G[0] = G[1] = VI(2 * n + 1);
        for (int i = 1; i <= 2 * n; ++i)
        {
            L[i] = R[i] = 0;
            G[0][i] = G[1][i] = 0;
            v[i] = 0;
        }
        for (int i = 1; i <= n; ++i)
        {
            cin >> x >> y;
            G[0][i] = x;
            G[1][i] = y;
        }

        bool found_path = false;
        do
        {
            memset(v, false, sizeof(v));
            found_path = false;
            for (int i = 1; i <= n; ++i)
                if ( !L[i] && DoMatch(i) )
                {
                    mm++;
                    found_path = true;
                }
        } while ( found_path );
        if (mm == n)
            cout << "DA\n";
        else
            cout << "NU\n";
    }
}
