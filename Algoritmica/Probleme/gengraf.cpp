#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("gengraf.in");
ofstream fout ("gengraf.out");

int n, a[10][10], m;

void afis();
void bac(int i, int j);

int main()
{
    int nr;
    fin >> n;
    m = n * (n - 1) / 2;

    nr = (1 << m);

    fout << nr << '\n';
    bac(1, 2);
}

void afis()
{
    for (int i = 1; i <= n; ++i, fout << '\n')
        for (int j = 1; j <= n; ++j)
            fout << a[i][j] << ' ';

    fout << '\n';
}

void bac(int i, int j)
{
    for (int k = 0; k <= 1; ++k)
    {
        a[i][j] = a[j][i] = k;
        if (i == n - 1 && j == n)
            afis();
        else
            if (j < n)
                bac(i, j + 1);
            else
                bac(i + 1, i + 2);
    }
}
