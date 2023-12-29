#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

ifstream fin ("suma5.in");
ofstream fout ("suma5.out");

using VI = vector<int>;
using VVI = vector<VI>;

const int dim = 63370, INF = 0x3f3f3f3f;
int n, m, v[dim], t[dim];

VVI G, D;

void Afisare(int i)
{
    cout << i << ' ';
    if (i == 1)
    {
        fout << i << ' ';
        return;
    }
    else
    {
        Afisare(t[i]);
        fout << i << ' ';
    }
}

int main()
{
    fin >> n;
    for (int i = 1; i <= n; ++i)
        fin >> v[i];

    for (m = 1; m * (m + 1) * (2 * m + 1) / 6 < n; ++m);

    fout << m;

    G = D = VVI(m + 1);

    int s = 0;
    for (int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <= i * i; ++j)
            G[i].emplace_back(v[s + j]), D[i].emplace_back(INF);

        s += i * i;
    }

    D[1][0] = G[1][0];
    s = 0;
    for (int i = 1; i < m; ++i)
    {
        s += i * i;
        for (int j = 0; j < i * i; ++j)
        {
            if (D[i + 1][j] > D[i][j] + G[i + 1][j])
            {
                D[i + 1][j] = D[i][j] + G[i + 1][j];
                t[j + s + 1] = s - i * i + j + 1;
            }
            if (D[i + 1][j + 1] > D[i][j] + G[i + 1][j + 1])
            {
                D[i + 1][j + 1] = D[i][j] + G[i + 1][j + 1];
                t[j + s + 2] = s - i * i + j + 1;
            }
            if (D[i + 1][j + i + 1] > D[i][j] + G[i + 1][j + i + 1])
            {
                D[i + 1][j + i + 1] = D[i][j] + G[i + 1][j + i + 1];
                t[j + s + i + 1] = s - i * i + j + 1;
            }
            if (D[i + 1][j + i + 2] > D[i][j] + G[i + 1][j + i + 2])
            {
                D[i + 1][j + i + 2] = D[i][j] + G[i + 1][j + i + 2];
                t[j + s + i + 2] = s - i * i + j + 1;
            }
        }
    }

    int mi = INF, pmi;

    for (int i = 0; i < m * m; ++i)
    {
        if (D[m][i] < mi)
        {
            mi = D[m][i];
            pmi = (m - 1) * m * (2 * m - 1) / 6 + i + 1;
        }
    }
    fout << ' ' << mi << '\n';

    Afisare(pmi);
}
