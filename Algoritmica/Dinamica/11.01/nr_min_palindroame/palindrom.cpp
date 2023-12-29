#include <fstream>
#include <cstring>
using namespace std;
ifstream fin ("palindrom.in");
ofstream fout ("palindrom.out");

bool pal(int i, int j);
void read();
void solve();

char a[105];
int nr[105], n;
const int INF = 0x3f3f3f3f;

int main ()
{
    read();
    solve();
    fout << nr[n - 1];
}

bool pal(int i, int j)
{
    while(i <= j)
    {
        if(a[i] != a[j])
           return false;
        i ++, j --;
    }
    return true;
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
        if(pal(0, i))
           nr[i] = 1;
        else
        {
            nr[i] =  INF;
            for (j = 0; j < i; j ++)
                if(pal(j + 1, i) and nr[j] + 1 < nr[i])
                    nr[i] = nr[j] + 1;

        }
    }
}
