// OK
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



int P,  N,X;
const int MOD = 20173333;
int pw[55005];

void Desc(int x)
{
	
    int e = 0, d = 2;
    while (x != 1)
    {
        e = 0;
        while(x % d == 0)
        {
            x /= d;
            e++;
        }
        pw[d] += e;
        d++;
        if ( d * d > x)
            d = x;
    }
}

void Desc1(int x)
{
    int e = 0, d = 2;
    while (x != 1)
    {
        e = 0;
        while (x % d == 0)
        {
            x /= d;
            e++;
        }
        pw[d] -= e;
        d++;
        if (d * d > x)
            d = x;
    } 
}

int Comb(int n, int k)
{
    for (int i = n; i >= n - k + 1; --i)
        Desc(i);
    for (int i = 2; i <= k; ++i)
        Desc1(i);
    int s = 1;
    for (int i = 2; i <= 50002; ++i)
        for (int j = 1; j <= pw[i]; ++j)
            s = (1LL * s * i) % MOD;
    return s;
}

int p1()
{
    return Comb(N - 1, X - 1);
}

int p2()
{
    vector<int> a (N + 1);
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i <= N; ++i)
    {
        a[i] = a[i - 1];   // totalul pana la poz i - 1 maresc numarul curent cu 1
        if (i > X)
            a[i] = ((a[i - 1] + a[i] // totalul pana la poz i - 1 (la poz i raman cu numarul anterior
            - a[i - X - 1] + MOD)) % MOD;    // normal ar trebui a[i - X], dar a[i - X] include si secventele anterioare care continua cu acelasi numar
        else                                 // a[i - X - 1] contin numai secvente care la poz i incepe o secventa noua
            a[i] = (a[i - 1] + a[i]) % MOD;
    }
    return a[N]; 
}


int main()
{
//	ifstream cin("sir.in");
//	ofstream fout("sir.out");
    cin >> P >> N >> X;
    if (P == 1)
        cout << p1() << '\n';
    else
        cout << p2() << '\n';
    return 0;
}
