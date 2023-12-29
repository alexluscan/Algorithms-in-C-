#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int Teste = 100;
int main()
{
    srand(time(NULL));

    for (int t = 1; t <= Teste; ++t)
    {
        ofstream fout("bancnote.in");

        int n = rand() % 10 + 1;
        int S = rand() % 500 + 50;
        fout << n << ' ' << S << '\n';

        for (int i = 1; i <= n; ++i)
            fout << rand() % 100 + 1 << ' ';
        fout.close();

        system("bancnote2_back.exe");

        ifstream fin1("bancnote.out");
        int nr1;
        fin1 >> nr1;
        fin1.close();

        system("bancnote2_dyn.exe");
        ifstream fin2("bancnote.out");
        int nr2;
        fin2 >> nr2;
        fin2.close();

        if (nr1 == nr2)
        {
            cerr << "OK!\n";
        }
        else
        {
            cerr << "Gresit!\n";
            cerr << nr1 << ' ' << nr2;
            break;
        }
    }
}
