#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream fin ("film.in");
ofstream fout ("film.out");

struct film{
    double b, e;
    int p;
};

film v[1005];
int n, nr[1005], ma;

bool Op(film a, film b)
{
    return a.b < b.b;
}

int main()
{
    fin >> n;

    for (int i = 1; i <= n; ++i)
    {
        fin >> v[i].b >> v[i].e;
        v[i].p = i;
    }

    sort(v + 1, v + n + 1, Op);

    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (v[j].e > v[i].b)
                nr[j]++;

    for (int i = 1; i <= n; ++i)
        if (nr[j] > ma)
            ma = nr[j];

    fout << nr[j] << " filme";
}
