#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

/*
D[i][j] = numarul de posibilitati de a pune primii i concurenti in j grupe (toti concurentii dintr-o grupa sunt pe acelasi loc)

Daca punem concurentul i intr-o grupa existenta avem j grupe dintre care putem alege (ordinea concurentilor dintr-o grupa nu conteaza).
Daca punem concurentul intr-o noua grupa, atunci aceasta grupa poate fi pe locul 1, locul 2, ..., locul j. Astfel avem tot j posibilitati.

D[i][j] = D[i - 1][j - 1] * j + D[i - 1][j] * j = (D[i - 1][j - 1] + D[i - 1][j]) * j

Rezultatul este D[N][1] + D[N][2] + ... + D[N][N].
Implementarea trebuie facuta pe numere mari.

*/

int N;
int D[2][102][202];
int result[202];

void add(int A[], int B[])
{
    A[0] = max(A[0], B[0]);
    for (int i = 1; i <= A[0]; ++i)
    {
        A[i] += B[i];
        if (A[i] >= 10)
        {
            A[i + 1] += A[i] / 10;
            A[i] %= 10;
            if (i == A[0]) ++A[0];
        }
    }
}
void inm(int A[], int x)
{
    for (int i = 1; i <= A[0]; ++i)
        A[i] *= x;
    for (int i = 1; i <= A[0]; ++i)
        if (A[i] >= 10)
        {
            A[i + 1] += A[i] / 10;
            A[i] %= 10;
            if (i == A[0]) ++A[0];
        }
}


int main()
{
    ifstream fin("race.in");
    ofstream fout("race.out");

    fin >> N;

    int act = 0;
    D[act][1][0] = D[act][1][1] = 1;

    for (int i = 2; i <= N; ++i)
    {
        act = !act;
        memset(D[act], 0, sizeof(D[act]));

        for (int j = 1; j <= i; ++j)
        {
            add(D[act][j], D[!act][j - 1]);
            add(D[act][j], D[!act][j]);
            inm(D[act][j], j);
        }
    }

    for (int i = 1; i <= N; ++i)
        add(result, D[act][i]);
    for (int i = result[0]; i >= 1; --i)
        fout << result[i];
    fout << '\n';

    fin.close();
    fout.close();
}
