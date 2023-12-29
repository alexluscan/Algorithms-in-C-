/*
    Constantin Galatan
    Recursivitate indirecta
    Mediana - nth_element
    Complexitate O(n)
*/
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

ifstream fin("expresie.in");
ofstream fout("expresie.out");

typedef vector<int> VI;
typedef VI::iterator IT;

string expr;
int n;
VI v, a;
int i, termen, semn, val, med;

int Expresie();
int Suma();
int Mediana(VI& v);
int Secventa(VI& v);
int SecvMax(IT a, IT b);
int NrNumere();

int main()
{
    getline(fin, expr);
    n = expr.length();

    fout << NrNumere() << '\n';
    fout << Expresie() << '\n';

    fout.close();
    fin.close();
    return 0;
}

int NrNumere()
{
    int cnt(0);
    for ( int i = 0; i < n; ++i )
    {
        if ( expr[i] == '(' || expr[i] == ')' || expr[i] == ',' ||
             expr[i] == '[' || expr[i] == ']' || expr[i] == '-' )
             continue;
        for (cnt++; i < n && expr[i] >='0' && expr[i] <= '9'; i++);
    }
    return cnt;
}

int Expresie()
{
    int ret(0);
    if ( expr[0] == '[')
    {
        i++;
        ret = Mediana(v);
    }
    else
    if ( expr[0] == '(')
    {
        i++;
        ret = Secventa(v);
    }
    else
    if ( expr[0] == '-' || (expr[0] >= '0' && expr[0] <= '9') )
        ret = Suma();
    if ( i < n && expr[i] == ',')
        ret += Suma();
    return ret;
}

int Mediana(VI& v)
{
    if ( i == n || expr[i] == ']')
    {
        i++;
        IT it = (v.begin() + (v.size() + 1) / 2 - 1);
        nth_element(v.begin(), it, v.end());
        int med = *it;
        v.clear();
        return med;
    }

    if ( expr[i] == '[')
    {
        VI a;
        i++;
        med = Mediana(a);
        v.push_back(med);
        return Mediana(v);
    }
    if ( expr[i] == '(')
    {
        VI a;
        i++;
        val = Secventa(a);
        v.push_back(val);
        return Mediana(v);
    }
    if ( expr[i] == ',' )
    {
        i++;
        return Mediana(v);
    }
    semn = 1;
    if ( expr[i] == '-')
        semn = -1, i++;
    termen = 0;
    for  ( ;i < n && expr[i] >= '0' && expr[i] <= '9'; ++i )
        termen = termen * 10 + expr[i] - '0';
    v.push_back(semn*termen);
    return Mediana(v);
}

int Suma()
{
    if ( i == n)
        return 0;
    if ( expr[i] ==')')
        return 0;
    if ( expr[i] == ',' )
    {
        i++;
        return Suma();
    }
    if ( expr[i] == '(')
    {
        VI a;
        i++;
        return Secventa(a) + Suma();
    }
    if ( expr[i] == '[' )
    {
        VI a;
        i++;
        return Mediana(a) + Suma();
    }

    semn = 1;
    if ( expr[i] == '-' )
    {
        semn = -1;
        i++;
    }
    termen = 0;
    for  ( ;expr[i] >= '0' && expr[i] <= '9'; ++i )
        termen = termen * 10 + expr[i] - '0';

    return semn * termen + Suma();

}

int SecvMax(IT a, IT b)
{
    int s = *a, max = *a;
    for ( IT it = a + 1; it != b; ++it )
    {
        if ( s + *it < *it )
            s = *it;
        else
            s += *it;
        if ( s > max )
             max = s;
    }
    return max;
}

int Secventa(VI& v)
{
    if ( i == n || expr[i] == ')')
    {
        i++;
        int secv = SecvMax(v.begin(), v.end());
        v.clear();
        return secv;
    }
    if ( expr[i] == ',' )
    {
        i++;
        return Secventa(v);
    }
    if ( expr[i] == '[')
    {
        VI a;
        i++;
        v.push_back(Mediana(a));
        return Secventa(v);
    }
    if ( expr[i] == '(')
    {
        VI a;
        i++;
        v.push_back(Secventa(a));
        return Secventa(v);
    }

    semn = 1;
    if ( expr[i] == '-')
        semn = -1, i++;
    termen = 0;
    for  ( ;expr[i] >= '0' && expr[i] <= '9'; ++i )
        termen = termen * 10 + expr[i] - '0';
    v.push_back(semn * termen);

    return Secventa(v);
}

