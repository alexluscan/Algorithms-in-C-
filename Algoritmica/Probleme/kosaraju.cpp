#include <fstream>
using namespace std;

ifstream fin ("roy-floyd.in");
ofstream fout ("roy-floyd.out");

struct Edge{
    int x, y, c;
};

Edge E[105];
int n, m, a[105][105];

int main()
{
    fin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            a[i][j] = 1e9;

    for (int i = 1; i <= n; ++i)
        a[i][i] = 0;

    for (int i = 1; i <= m; ++i)
    {
        fin >> E[i].x >> E[i].y >> E[i].c;
        a[E[i].x][E[i].y] = E[i].c;
    }

    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j)
                if (a[i][j] > a[i][k] + a[k][j])
                    a[i][j] = a[i][k] + a[k][j];

    for (int i = 1; i <= n; ++i, fout << '\n')
        for (int j = 1; j <= n; ++j)
            if (a[i][j] == 1e9)
                fout << "-1 ";
            else
                fout << a[i][j] << ' ';

}
