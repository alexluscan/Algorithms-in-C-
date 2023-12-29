#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin ("euro.in");
ofstream fout ("euro.out");

const int dim = 4e3 + 5, D = 8e3 + 5;
int t, n, vm;
int v[dim], mn[D], res[D];

int main()
{
    fin >> t;
    while(t--)
    {
        fin >> n >> vm;

        for (int i = 1; i <= n; ++i)
            fin >> v[i];

        for(int i = 1; i <= vm; ++i)
        {
            mn[i] = -1;
            res[i] = vm + 1;
        }

        sort(v + 1, v + n + 1);

        for (int i = 1; i <= n; ++i)
        {
            for (int j = vm; j > v[i]; --j)
                mn[j] = max(mn[j], mn[j - v[i]]);
            mn[v[i]] = v[i];

            for (int j = 0; j <= vm; ++j)
                if (mn[j] != -1)
                    res[j] = min(res[j], v[i] - mn[j]);
        }

        for (int i = 1; i <= vm; ++i)
            if (res[i] == vm + 1)
                fout << "-1 ";
            else
                fout << res[i] << ' ';

        fout << '\n';
    }
}
