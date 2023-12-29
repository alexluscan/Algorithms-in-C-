#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin ("judete.in");
ofstream fout ("judete.out");

#define eb emplace_back

using VI = vector<int>;
using VVI = vector<VI>;

const int INF = 2e9;
int n, K;
VI v, nr;
VVI arb;

VI DF(int x);

int main()
{
    fin >> n >> K;

    arb = VVI(n + 1);
    v = nr = VI(n + 1);

    for (int i = 1, x, y; i <= n; ++i)
    {
        fin >> x >> y;
        arb[x].eb(y);
        arb[y].eb(x);
    }

    VI t = DF(1);
    int T = 2e9;

    for (int i = K; i <= n; ++i)
        T = min(T, max(t[i], i));

    fout << T;
}

VI DF(int x)
{
    nr[x] = 1;
    v[x] = 1;

    VI tx(n + 1, INF);
    tx[1] = 0;

    for (const auto& f : arb[x])
    {
        if (v[f])
            continue;
        VI tf = DF(f);
        nr[x] += nr[f];

        VI C(n + 1, INF);

        for (int j = 0; j <= nr[x]; ++j)
            for (int k = 0; k <= nr[f] and j + k <= nr[x]; ++k)
            {
                C[j + k] = min(C[j + k], max(tx[j], tf[k]));
                if (k >= K)
                    C[j] = min(C[j], max(k, max(tx[j], tf[k])));
            }

        tx = C;
    }

    return tx;
}
