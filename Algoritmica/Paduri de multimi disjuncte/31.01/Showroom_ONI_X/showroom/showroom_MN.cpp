#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>

#define MAXL 1002
#define MAXC 103
#define MOD 9001


using namespace std;

set<string> m;
set<string>::iterator itset;
vector<string> v;
vector<string>::iterator itstring;
string s, str, buf;


set<string> L[MAXL];

vector<int> W[MAXL];

int n, a, r, k, N, i, j, p, maxim, pmaxim, sol, pz, ratia, start, modulo;


int T[MAXL*MAXC+2];
int F[MAXL*MAXC+2];

int R[MAXC];
int S[MAXL];
int X[MAXL];
int fact[50002];

int poz(vector<string> v, string s) {
    vector<string>::iterator itstring;
    itstring = lower_bound (v.begin(), v.end(), s);
    return itstring - v.begin();

}

int rad(int x) {
    while (T[x] >= 0)
        x = T[x];
    return x;
}

void invmod(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
    } else {
        int x0, y0;
        invmod(b, a%b, x0, y0);
        x = y0;
        y = x0-(a/b)*y0;
    }

}

int invers(int a, int n) {
    int x,y;
    invmod(a, n, x, y);
    return x%n >=0 ? x%n : x%n+n;
}

int comb(int n, int k) {
    if (k>n)
        return 1;
    int a = fact[n];
    int b = fact[k];
    int c = fact[n-k];
    int aux = (a * invers(b, MOD)) % MOD;
    return aux * invers(c, MOD) % MOD;
}

int main() {
    ifstream fin ("showroom.in");
    ofstream fout ("showroom.out");
    fin>>n>>start>>ratia>>modulo;

    fin.get();

    for (int i=1;i<=n;i++) {
        getline (fin, str);

        stringstream ss(str);
        while (ss >> buf) {
            L[i].insert(buf);
            m.insert(buf);
        }

    }

    for (itset = m.begin(); itset!=m.end(); itset++) {
        v.push_back(*itset);
    }

    for (i=1;i<=n;i++) {
        for (itset = L[i].begin(); itset!=L[i].end(); itset++) {
            pz = lower_bound(v.begin(), v.end(), *itset) - v.begin();
            W[i].push_back(pz);
        }

    }

    for (i=0;i<=MAXL*MAXC; i++)
        T[i] = -1;
    for (i=1;i<=n;i++) {
        maxim = 0;
        for (j=0;j<W[i].size();j++) {
            //W[i][j] este codul unei masini
            R[j] = rad(W[i][j]);
            if (-T[R[j]] > maxim) {
                maxim = -T[R[j]];
                pmaxim = R[j];
            }
        }
        for (j=0;j<W[i].size();j++) {
            if (R[j]!=pmaxim) {
                T[pmaxim] += T[R[j]];
                T[R[j]] = pmaxim;
            }
        }

    }
/*
    for (i=0;i<v.size();i++)
        if (T[i]<0)
            sol++;
*/

    for (i=1;i<=n;i++) {
        for (j=0;j<W[i].size();j++) {
            r = rad(W[i][j]);
            if (F[r] == 0) {
                S[++sol] = -T[r];
                F[r] = 1;
            }
        }
    }

    X[1] = start;
    for (i=2;i<=sol;i++)
        X[i] = (X[i-1] + ratia) % modulo;

    fact[0] = 1;
    for (i=1;i<=50000;i++)
        fact[i] = (fact[i-1]*i) % MOD;

    int prod = 1;
    for (i=1;i<=sol;i++) {
        prod *= comb(S[i], X[i]);
        prod %= MOD;
    }

    fout<<sol<<"\n"<<prod<<"\n";
    return 0;
}
