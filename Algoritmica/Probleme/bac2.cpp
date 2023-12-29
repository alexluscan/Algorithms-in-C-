#include <iostream>
using namespace std;

void bac(int);
void afisare();

int n, f[2], v[32], p;

int main()
{
    int x = 1;
    cin >> n;
    f[1] = __builtin_popcount(n);
    for (p = 1; n >= x; ++p)
    {
        x = x * 2;
    }
    --p;
    f[0] = p - f[1];

    bac(1);
}

void bac(int k)
{
    for (int i = 0; i <= 1; ++i)
    {
        v[k] = i;
        if (f[i] > 0)
        {
            --f[i];
            if (k == p)
                afisare();
            else
                bac(k + 1);
            ++f[i];
        }
    }
}

void afisare()
{
    for (int i = 1; i <= p; ++i)
        cout << v[i];

    cout << '\n';
}
