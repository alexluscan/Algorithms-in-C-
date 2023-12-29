#include <iostream>
using namespace std;

void bac(int);
void afisare();

int n, f[10], v[15], m;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        f[i] = i;

    m = n * (n + 1) / 2;

    bac(1);
}

void bac(int k)
{
    for (int i = 1; i <= n; ++i)
    {
        v[k] = i;
        if (f[i])
        {
            --f[i];
            if (k == m)
                afisare();
            else
                bac(k + 1);
            ++f[i];
        }
    }
}

void afisare()
{
    for (int i = 1; i <= m; ++i)
        cout << v[i];

    cout << '\n';
}
