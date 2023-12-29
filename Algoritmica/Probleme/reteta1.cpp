#include <fstream>
#include <iomanip>
#include <bitset>
using namespace std;

ifstream fin ("reteta1.in");
ofstream fout ("reteta1.out");

int n, m, msk[20], mask, c[25], t[20];
double res, ct[20], cmin = 2000000000;
bool ok;

int main()
{
    int k, a;
    fin >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        fin >> t[i] >> k;
        for (int j = 1; j <= k; ++j)
        {
            fin >> a;
            msk[i] |= (1 << (a - 1));
        }
    }

    for (int i = 0; i < n; ++i)
        fin >> c[i];

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
            if (msk[i] & (1 << j))
                ct[i] += c[j];

        if (t[i] == 2)
            ct[i] /= 2;
    }

    for (int j = 0; j < (1 << m); ++j)
    {
        mask = 0;
        res = 0;
        ok = true;
        for (int i = 0; i < m; ++i)
            if (j & (1 << i))
            {
                if (msk[i] & mask)
                {
                    ok = false;
                    break;
                }
                else
                {
                    mask |= msk[i];
                    res += ct[i];
                }
            }

        if (ok && mask == ((1 << n) - 1))
            if (res < cmin)
                cmin = res;
    }

    fout << setprecision(1) << fixed << cmin;
}
