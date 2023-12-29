#include <fstream>
#include <cstring>
using namespace std;
ifstream fin ("palindrom.in");
ofstream fout ("palindrom.out");

void read();
void solve();
void preprocess();

char a[105];
bool p[105][105];
int nr[105], n;
const int INF = 0x3f3f3f3f;

int main ()
{
    read();
    preprocess();
    solve();
    fout << nr[n - 1];
}

void preprocess()
{
    int i, j, l;
    for (i = 0; i < n; i++)
        p[i][i] = true;
    for (l = 2; l <= n; l++)
        for (i = 0; i + l <= n; i++)
        {
            j = i + l - 1;
            if (l == 2)
                p[i][j] = a[i] == a[j];
            else
                p[i][j] = a[i] == a[j] and p[i + 1][j - 1];
        }
}

void read()
{
    fin >> a;
    n = strlen(a);
}

void solve()
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (p[0][i])
           nr[i] = 1;
        else
        {
            nr[i] =  INF;
            for (j = 0; j < i; j ++)
                if(p[j + 1][i] and nr[j] + 1 < nr[i])
                    nr[i] = nr[j] + 1;
        }
    }
}
