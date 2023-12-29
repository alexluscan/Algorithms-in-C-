
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define NMAX 200001

ifstream fin("heapuri.in");
ofstream fout("heapuri.out");

int H[NMAX], a[NMAX], poz[NMAX];
int i, n, p, cod, x, N;

void Swap(int i, int j)
{
    swap(H[i], H[j]);
    poz[H[i]] = i;
    poz[H[j]] = j;
}

void UpHeap(int u) {
    H[++n] = u;
    u = n;
    while (u != 1 && a[H[u]] < a[H[u / 2]])
        Swap(u, u / 2), u /= 2;
}

void DownHeap(int u) {
    u = poz[u];  // poz[u] - poz in H a lui A[u]
    Swap(u, n--); // nodul care se insereaza e trimis la coada heap-ului pe poz n si ramane in afara lui (n--)
    while (true)
    {
        int m = u;
        if (u * 2 <= n && a[H[u * 2]] < a[H[u]])
            m = u * 2;
        if (u * 2 + 1 <= n && a[H[u * 2 + 1]] < a[H[m]])
            m = u * 2 + 1;
        if (u == m)
            break;
        Swap(u, m);
        u = m;
    }
}

int main()
{
    fin >> N;
    for (i = 1; i <= N; ++i)
    {
        fin >> cod;
        if ( cod == 3 )
        {
            fout << a[H[1]] << '\n';
            continue;
        }
        fin >> x;
        if (cod == 1)
        {
            a[++p] = x;
            poz[p] = p;
            UpHeap(p);
        }

        if ( cod == 2 )
            DownHeap(x);
    }
    fin.close();
    fout.close();
    return 0;
}
