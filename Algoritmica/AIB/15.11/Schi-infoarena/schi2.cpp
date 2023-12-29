// ok
#include <fstream>
#define N 100100
using namespace std;

ifstream fin("schi.in");
ofstream fout("schi.out");

int sol[N], v[N], n, A[N];

void Update(int pos, int v)
{
    for(int x = pos; x <= n; x += x & -x)
        A[x] += v;
}

int Query(int pos)
{
    int sum = 0;
    for(int x = pos; x ; x -= x & -x)
        sum += A[x];
    return sum;
}

int Bs(int p)
{
    int st = 1, dr = n, sol = n;
    while (st <= dr)
    {
        int mij = (st + dr) >> 1;
        if (Query(mij) >= p)
        {
            sol = mij;
            dr = mij - 1;
        }
        else
            st = mij + 1;
    }
    return sol;
}

int main ()
{
    fin >> n;
    for (int i = 1; i <= n; ++i)
    {
        fin >> v[i];
        Update(i, 1);
    }
    int pos;
    for ( int i = n; i >= 1; --i)
    {
        pos = Bs(v[i]);
        Update(pos, -1);
        sol[pos]=i;
    }
    
    for (int i = 1; i <= n; ++i)
		fout << sol[i] << '\n';
		
	fin.close();
	fout.close();
    return 0;
}
