// OK
#include <fstream>
using namespace std;

ifstream fin("part.in");
ofstream fout("part.out");

int a[101][101][101];  // a[i][j][k] - nr part ale lui i cu j termeni, ultimul termen  k
int sol[101]; // sol[i] nr de partitii ale lui n cu i termeni
int n;


int main()
{
    fin >> n;
    fin.close();

     for (int i = 1; i <= n; ++i)
     {
         a[i][i][1] = 1;
         a[i][1][i] = 1;
     }

     for (int i = 2; i <= n; ++i)
          for (int j = 2; j <= n; j++)
                    for (int k = 2; k <= n; ++k)
                    {
                        a[i][j][k] += a[i-1][j][k-1];
                        if (i > k) a[i][j][k] += a[i-k][j-1][k];  // posibilitati de inversiuni

                    }
     int nr = 0;
     for (int i = 1; i <= n; ++i)
          for (int k = 1; k <= n; ++k)
                    sol[i] += a[n][i][k], nr += a[n][i][k];

     fout << nr << '\n';
     for (int i = 1; i <= n; ++i)
          fout << sol[i] << " partitii de cate " << i << '\n';
     fout.close();
     return 0;
 }
