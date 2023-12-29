#include <fstream>
using namespace std;

ifstream fin("sclm2.in");
ofstream fout("sclm2.out");
const int MaxN = 100001;
int v[MaxN], Lmax;

int Bs(int x)
{
    int st = 1, dr = Lmax, poz = -1;
    while (st <= dr)
    {
        int m = (st + dr) / 2;
        if(x < v[m])
        {
            poz = m;
            dr = m - 1;
        }
        else
            st = m + 1;
    }
    return poz;
}

int main()
{
    int n, x;
    fin >> n;

    fin >> x;
    Lmax = 1;
    v[Lmax] = x;

    for (int i = 2; i <= n; i++)
    {
        fin >> x;
		if (x >= v[Lmax])
            v[++Lmax] = x;
        else
        {
            int poz = Bs(x);
            v[poz] = x;
        }

    }

    fout << Lmax;

    return 0;
}
