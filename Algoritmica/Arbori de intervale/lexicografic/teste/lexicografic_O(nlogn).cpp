#include <bits/stdc++.h>
using namespace std;

const int inf = 1 << 30;
const int NMAX = 250005;

int t, n, a[NMAX];
int L, R;
int mn[4 * NMAX];   // mn[x] = poz minimului din a[] in intervalul [st, dr], pt elementele nemutate
int sum[4 * NMAX];  // sum[x] = nr de elemente nemutate din [st, dr]
long long k;

void UpdateSum(int x, int st, int dr, int poz, int val)
{
    if (st == dr)
        sum[x] = val;
    else
    {
        int mij = (st + dr) / 2;
        if (poz <= mij)
            UpdateSum(2 * x, st, mij, poz, val);
        else
            UpdateSum(2 * x + 1, mij + 1, dr, poz, val);
        sum[x] = sum[2 * x] + sum[2 * x + 1];
    }
}

void UpdateMin(int x, int st, int dr, int poz, int val)
{
    if (st == dr)
        mn[x] = val; // [st, dr] contine numai a[val]
    else
    {
        int mij = (st + dr) / 2;
        if (poz <= mij)
            UpdateMin(2 * x, st, mij, poz, val);
        else
            UpdateMin(2 * x + 1, mij + 1, dr, poz, val);
        mn[x] = a[mn[2 * x]] <= a[mn[2 * x + 1]] ? mn[2 * x] : mn[2 * x + 1];
    }
}

int QuerySum(int x, int st, int dr)
{
    if (L <= st && dr <= R)
        return sum[x];
    else
    {
        int mij = (st + dr) / 2, val = 0;
        if (L <= mij) val += QuerySum(2 * x, st, mij);
        if (R > mij)  val += QuerySum(2 * x + 1, mij + 1, dr);

        return val;
    }
}

// returneaza poz in sirul a[] a primelor k + 1 valori nemutate
int QueryPoz(int x, int st, int dr, long long lim)
{
    if (st == dr)
        return st;
    else
    {
        int mij = (st + dr) / 2;
        if (sum[2 * x] >= lim)
            return QueryPoz(2 * x, st, mij, lim);
        else
            return QueryPoz(2 * x + 1, mij + 1, dr, lim - sum[2 * x]);
    }
}

// returneaza pozitia minimului in intervalul [st, dr] - pt valorile nemutate
int QueryMin(int x, int st, int dr)
{
    if (L <= st && dr <= R)
        return mn[x];
    else
    {
        int mij = (st + dr) / 2, poz = 0;  // am pus a[0] = inf
        if (L <= mij)
        {
            int ans = QueryMin(2 * x, st, mij);
            if (a[ans] < a[poz])
                poz = ans;
        }
        if (R > mij)
        {
            int ans = QueryMin(2 * x + 1, mij + 1, dr);
            if (a[ans] < a[poz])
                poz = ans;
        }
        return poz;
    }
}

int main()
{
    ifstream fin("4-lexicografic.in");
    ofstream fout("lexicografic.out");
    ios_base::sync_with_stdio(false);

    fin >> t;
    while (t--)
    {
        fin >> n >> k;
        a[0] = inf;
        for (int i = 1; i <= n; i++)
        {
            fin >> a[i];
            UpdateSum(1, 1, n, i, 1);
            UpdateMin(1, 1, n, i, i);
        }

        for (int i = 1; i <= n; i++)
        {
            // afla k + 1 nemutate
            int poz = QueryPoz(1, 1, n, k + 1);

            // afla min din [1, poz]
            L = 1, R = poz;
            int pm = QueryMin(1, 1, n); // pozitia minimului

            fout << a[pm] << ' ';
            L = 1, R = pm;
            k -= QuerySum(1, 1, n) - 1;
            UpdateSum(1, 1, n, pm, 0);
            UpdateMin(1, 1, n, pm, 0);
        }

        fout << "\n";

        // clear
        for (int i = 1; i <= n * 4; i++)
            mn[i] = sum[i] = 0;
    }

    return 0;
}
