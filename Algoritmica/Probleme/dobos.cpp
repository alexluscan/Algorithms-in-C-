#include <iostream>
#include <fstream>
using namespace std;

ifstream fin ("graf.in");
ofstream fout ("graf.out");

struct Edge{
    int x, y, c;
};

Edge e[1005];
int n, m, a[1005][1005], ma[1005][1005];

int main()
{
    fin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            a[i][j] = 1e9;
    for (int i = 1; i <= n; ++i)
            a[i][i] = 0;

    for (int i = 1; i <= m; ++i)
    {
        fin >> e[i].x >> e[i].y >> e[i].c;
        a[e[i].x][e[i].y] = e[i].c;
    }

    for(int k = 1; k <= n; k ++)
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= n; j ++)
                if(a[i][j] > a[i][k] + a[k][j])
                    a[i][j] = a[i][k] + a[k][j];


    for (int i = 1; i <= n; ++i, fout << '\n')
        for (int j = 1; j <= n; ++j)
            if (a[i][j] != 1e9)
                fout << a[i][j] << ' ';
            else
                fout << "-10 ";
}
