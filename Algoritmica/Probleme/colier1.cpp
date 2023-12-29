#include <fstream>
#include <iostream>
using namespace std;

ifstream fin ("colier.in");
ofstream fout ("colier.out");

void bac(int);

int n, m, c[15], v[15], x[15], sol[15], sma, uz[15], sp;

int main()
{
    fin >> n >> m;

    for (int i = 1; i <= n; ++i)
        fin >> c[i] >> x[i];

    bac(1);

    for (int i = 1; i <= m; ++i)
        fout << sol[i] << ' ';
}

void bac(int k)
{
    for (int i = 1; i <= n; ++i)
    {
        v[k] = i;
        cout << k << " ";
        if (uz[i] == 0)
        {
            uz[i] = 1;
            sp += x[i];

            if (k == 1 || c[v[k]] != c[v[k - 1]])
                if (k == m)
                {
                    if (sp > sma && c[v[m]] != c[v[1]])
                    {
                        sma = sp;
                        for (int i = 1; i <= m; ++i)
                            sol[i] = v[i];
                    }
                }
                else
                    bac(k + 1);
            uz[i] = 0;
            sp -= x[i];
        }
    }
}
