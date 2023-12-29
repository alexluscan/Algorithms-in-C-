#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("partitiinumar.in");
ofstream fout ("partitiinumar.out");

void bac(int k);
void afisare(int k);

int n, v[50], s;

int main()
{
    fin >> n;
    v[0] = 1;
    bac(1);
}

void bac(int k)
{
    for (int i = v[k - 1]; i <= n; ++i)
    {
        v[k] = i;
        s += i;
        if (s < n)
            bac(k + 1);
        else if (s == n)
                afisare(k);
        s -= i;
    }
}

void afisare(int k)
{
    for (int i = 1; i <= k; ++i)
        fout << v[i] << ' ';

    fout << '\n';
}
