/* Se da un rucsac de capacitate G (Kg)
    si un sir de n OBIECTE de valori v[1], .., v[n]
                                   si greutati g[1],..., g[n].

    Sa se gaseasca val maxima care poate fi transportate in rucsac, daca:
    1. Acelasi obiect NU poate fi utilizat de mai multe ori
    2. Rucsacul nu trebuie sa fie plin
*/

#include <fstream>
using namespace std;

ifstream fin("knapsack.in");
ofstream fout("knapsack.out");

const int NrOb = 500,
          GMAX = 1000;

int v[NrOb];  // valori
int g[NrOb];  // greutatile
int c[GMAX];  // c[j] val maxima pt j kg
int n;        // nr de tipuri de obiecte
int G;        // capacitatea rucsacului
int vmax;

void CitesteDate();
void Knapsack();

int main()
{
    CitesteDate();
    Knapsack();
    fout << vmax;

    return 0;
}

void Knapsack() // O(n * G)
{
    int maxj = 0;
    for (int j = 0; j <= GMAX; ++j)
        c[j] = -1; // necalculat

    c[0] = 0;
    for (int i = 1; i <= n; ++i)    // pentru fiecare obiect
        for (int j = maxj, maxj += g[i]; j >= 0; --j) // pentru fiecare greutate posibila
            if (c[j] != -1 && c[j + g[i]] < c[j] + v[i])
            {
                c[j + g[i]] = c[j] + v[i];
                vmax = max(vmax, c[j + g[i]]);
            }
}

void CitesteDate()
{
    fin >> n >> G;
    for (int i = 1; i <= n; ++i)
        fin >> g[i] >> v[i];
}
