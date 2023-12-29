#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin ("arbore4.in");
ofstream fout ("arbore4.out");

#define int long long
#define eb emplace_back
using VI = vector<int>;
using VVI = vector<VI>;

const int MaxN = 1e5 + 5, Mod = 666013;
int n, fac[MaxN], inv[MaxN];
VVI G;
VI nr, sol;

int Comb(int n, int k);
void Precal();
int Plog(int a, int b);

void DFS(int x, int dad)
{
    nr[x] = 1;
    for (const auto& y : G[x])
    {
        if (y == dad)
            continue;
        DFS(y, x);
        nr[x] += nr[y];
    }
}

void DF(int x, int dad)
{
    sol[x] = 0;
    int nbr = 1;
    long long aux = 1ll;
    for (const auto& y : G[x])
    {
        if (y == dad) continue;
        DF(y, x);
        aux = (aux * sol[y]) % Mod;
        aux = (aux * Comb(nr[x] - nbr, nr[y])) % Mod;
        nbr += nr[y];
    }

    sol[x] = aux;
}

main()
{
    fin >> n;
    G = VVI(n + 1);
    nr = sol = VI(n + 1);

    for (int i = 1, x, y; i < n; ++i)
    {
        fin >> x >> y;
        G[x].eb(y);
        G[y].eb(x);
    }

    Precal();

    DFS(1, 0);
    DF(1, 0);

    fout << sol[1];
}

void Precal()
{
    fac[0] = inv[0] = 1;

    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % Mod;
        //inv[i] = Plog(fac[i], Mod - 2);

    inv[n] = Plog(fac[n], Mod - 2);
    for (int i = n - 1; i >= 1; --i)
        inv[i] = (1LL * inv[i + 1] * (i + 1)) % Mod;
}

int Comb(int n, int k)
{
    long long aux = 1LL;
    aux = (aux * fac[n]) % Mod;
    aux = (aux * inv[k]) % Mod;
    aux = (aux * inv[n - k]) % Mod;

    return aux;
}

int Plog(int a, int b)
{
    long long res = 1LL;
    while (b)
    {
        if (b % 2)
            res = (1LL * res * a) % Mod;
        b /= 2;
        a = (1LL * a * a) % Mod;
    }

    return res;
}
