#include <fstream>
using namespace std;

ifstream fin("sumagauss2.in");
ofstream fout("sumagauss2.out");

int main()
{
    long long S, sq, aux, n, m, d;
    fin >> S;
    S *= 2;
    for (d = 1; d * d <= S; d++)
        if (S % d == 0)           
        {
            aux = d + S / d - 1;
            if (aux % 2 == 0)       
            {
                n = aux / 2;
                m = n - d;
                fout << n << ' ' << m << '\n';
            }
        }
    
    return 0;
}

