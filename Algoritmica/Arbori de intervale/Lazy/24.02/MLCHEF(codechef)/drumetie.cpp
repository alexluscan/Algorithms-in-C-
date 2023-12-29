#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
const i64 inf(1e18);
class Arbore {
public:
    Arbore() {}
    Arbore(const int& _n) : n(_n) {
        arb = vector<i64>(2 * n, inf);
    }
    inline void Update(const int& pos, const i64& val) {
        int p(pos + n - 1);
        arb[p] = val;
        while (p > 0) {
            arb[p >> 1] = min(arb[p], arb[p ^ 1]);
            p >>= 1;
        }
    }
    inline i64 Query(const int& l, const int& r) const {
        i64 res(1e18);
        int st(l + n - 1), dr(r + n);
        while (st < dr) {
            if (st & 1)
                res = min(res, arb[st++]);
            if (dr & 1)
                res = min(res, arb[--dr]);
            st >>= 1, dr >>= 1;
        }
        return res;
    }
private:
    int n;
    vector<i64> arb;
};
namespace FastRead {
    const int Dim(1e6);
    char buff[Dim];
    int pos, len;
    inline char nc() {
        if (pos == len) {
            pos = 0;
            len = fread(buff, 1, Dim, stdin);
            if (!len) return EOF;
        }
        return buff[pos++];
    }
    template<class T> inline void Read(T& x) {
        char ch;
        int sgn(1);
        while (!isdigit(ch = nc()))
            if (ch == '-')
                sgn = -1;
        x = ch - '0';
        while (isdigit(ch = nc()))
            x = x * 10 + (ch - '0');
        x *= sgn;
    }
}
using namespace FastRead;
int n, x, k, a;
i64 curr;
int main() {
    Read(n);
    Arbore arb(n);
    vector<vector<int>> tomark(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (const int& x : tomark[i])
            arb.Update(x, inf);
        Read(x), Read(k);
        curr = x;
        if (i > 1)
            curr += arb.Query(max(1, i - k), i - 1);
        arb.Update(i, curr);
        if (i + k < n)
            tomark[i + k + 1].emplace_back(i);
    }
    cout << curr;
    return 0;
}
