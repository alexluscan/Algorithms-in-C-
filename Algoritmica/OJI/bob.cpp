#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin ("bob.in");

int nrbin(char a[])
{
    int res = 0, l = strlen(a);
    for (int i = l - 1; i >= 0; --i)
        res += (a[i] - '0') * (1 <<(l - i - 1));
    return res;
}

int cer, t, n, k;
int a[200005];

int main()
{
    cin >> cer >> t;
    while (t--)
    {
        char aux[25];
        cin >> n >> k;
        cin.get();
        for (int i = 1; i <= n; ++i)
        {
            cin >> aux;
            a[i] = nrbin(aux);
        }
        int nr = 0, cmb = 0;
        for (int i = 1; i <= n; ++i)
        {
            cmb |= a[i];
            if (cmb == ((1 << k)  - 1))
            {
                ++nr;
                cmb = 0;
            }
        }
        cout << nr << '\n';
    }
}
