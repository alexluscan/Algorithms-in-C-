/* Problema Bancnotelor
    Sa se gen. toate posibilitatile de a plti o suma S
    cu n tipuri de bancnote, de val. v[1], .., v[n];
    stiind ca:
    1. Exista oricate bancnote din fieacre tip
    2. NU este obligatorie utilizarea tuturor tipurilor de bancnote
*/

#include <fstream>
using namespace std;

ifstream fin("bancnote.in");
ofstream fout("bancnote.out");


int x[20]; // x[k] - nr de bancnote de tipul k
int v[20]; // valorile bancnotelor
int n;     // nr de TIPURI de bancnote
int S;     // suma care trebuie platita

void ReadData();
void Bancnote(int k, int s); // s = x[1]*v[1] + ... + x[k - 1]* v[k - 1]
void Write(int k);

int main()
{
    ReadData();
    Bancnote(1, 0);
}

void Bancnote(int k, int s)
{
    if (s == S)
    {
        Write(k - 1);
        return;
    }
    if (k > n) return;

    for (int i = 0; s + i * v[k] <= S; ++i)
    {
        x[k] = i;
        Bancnote(k + 1, s + i * v[k]);
    }
}

void Write(int k)
{
    fout << S << " = ";
    for (int i = 1; i < k; ++i)
        if (x[i])
            fout << x[i] << "*" << v[i] << " + ";
    if (x[k])
        fout << x[k] << "*" << v[k];
    fout << '\n';
}


void ReadData()
{
    fin >> n >> S;
    for (int i = 1; i <= n; ++i)
        fin >> v[i];
}
