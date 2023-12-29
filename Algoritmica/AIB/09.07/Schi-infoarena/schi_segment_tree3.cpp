#include <fstream>
#include <vector>
#define DIM 31000
using namespace std;

int n;
int A[4*DIM]; // cate pozitii nearse avem pe interv
int d[DIM], s[DIM];
int x, y, X, sol;

void Build(int,int,int);
void Query(int,int,int);
void Update(int,int,int);

int main()
{
    ifstream fin("schi.in");
    fin >> n;
    for (int i = n; i >= 1; --i)
        fin >> d[i];
    fin.close();

    Build(1, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        sol = 0;
        X = d[i]; // a x-a pozitie nearsa
        Query(1, 1, n);
        Update(1, 1, n);

        s[sol] = n - i + 1;

    }

    ofstream fout("schi.out");
    for (int i = 1; i <= n; ++i)
        fout << s[i] << '\n';
    fout.close();

    return 0;
}

void Build(int nod, int st, int dr)
{
    if (st == dr)
    {
        A[nod] = 1;
        return;
    }
    int mij = (st + dr) / 2;
    Build(2*nod, st, mij);
    Build(2*nod+1, mij+1, dr);
    A[nod] = A[2*nod] + A[2*nod+1];
}

void Query(int nod, int st, int dr)
{
    if (st == dr)
    {
        sol = st;
        return;
    }
    int mij = (st + dr) / 2;
    if (A[2*nod] >= X)
        Query(2*nod, st, mij);
    else
    {
        X -= A[2*nod];
        Query(2*nod+1, mij+1, dr); // caut a (X - A[2*nod]) - a pozitie din intervalul din dreapta
    }
}

void Update(int nod, int st, int dr)
{
    if (st == dr)
    {
        A[nod] = 0;
        return;
    }
    int mij = (st + dr) / 2;
    if (sol <= mij) Update(2*nod, st, mij);
    else Update(2*nod+1, mij+1, dr);
    A[nod] = A[2*nod] + A[2*nod+1];
}
