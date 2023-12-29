/* Se da un rucsac de capacitate G (Kg)
    si un sir de n TIPURI de obiecte de valori v[1], .., v[n]
                                   si greutati g[1],..., g[n].

    Sa se gaseasca val maxima care poate fi transportate in rucsac, daca:
    1. Acelasi obiect poate fi utilizat de mai multe ori
    2. Rucsacul nu trebuie sa fie plin
*/

#include <fstream>
using namespace std;

ifstream fin("bancnote.in");
ofstream fout("bancnote.out");

const int NrOb = 500,
          GMAX = 1000;

int v[NrOb];  // valorile bancnotelor
int nr[GMAX]; // nr[j] nr de posibilitati sa obtin suma j
int n, S;     // nr de tipuri de bancnote, suma care trebuie platita

void CitesteDate();
void Knapsack();

int main()
{
    CitesteDate();
    Knapsack();

    if (nr[S])
        fout << nr[S];
    else
        fout << 0;

    return 0;
}

void Knapsack() // O(n * G)
{
    nr[0] = 1;
    for (int i = 1; i <= n; ++i)    // pentru fiecare tip de bancnota
        for (int j = 0; j + v[i] <= S; ++j) // pentru fiecare suma j posibila
            if (nr[j])
                nr[j + v[i]] += nr[j];
}

void CitesteDate()
{
    fin >> n >> S;
    for (int i = 1; i <= n; ++i)
        fin >> v[i];
}
