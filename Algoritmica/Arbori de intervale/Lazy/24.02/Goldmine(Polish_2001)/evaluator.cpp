#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

const int TESTE = 100;

/*
Fisierele sursa.exe, brut.exe si evaluator.exe trebuie sa se afle in acelasi folder in momentul rularii!
*/

int main()
{
    ofstream fout("rez.txt");
    srand(time(0));
    for (int test = 1; test <= TESTE; ++test)
    {
        ofstream out("puncte.in");
     //   int T  = rand() % 5 + 1;
        int W = rand() % 100 + 1; // trebuie setata o limita pentru care brut-ul sa poata rula ok
        int H = rand() % 100 + 1;
        int N = rand() % 500 + 50;

        out << W << ' ' << H << '\n';
        out << N << '\n';

        for (int i = 1; i <= N; ++i)
                out << rand() % 1000 - 500 << ' ' << ' ' << rand() % 1000 - 500 << '\n';

        out.close();

        int result1; // rezultatul dat de sursa (dinamica)
        int result2; // rezultatul dat de brut (back)

            // rulez prima sursa
            //system("start /wait sursa.exe"); // pe windows
        system("./puncte_brut");
        system("./puncte_ok");

        ifstream in1("puncte.out");
        ifstream in2("puncte.ok");
        in2 >> result2;
        in1 >> result1;
        if (result1 == result2)
        {
                //cerr << "OK!\n"; // afisare la standard error (ca sa apara sigur in terminal)
            fout << "OK!\n";
        }
        else
        {
                //  cerr << "WRONG! " << result1 << ' ' << result2 << '\n'; // e gresit, deci eval-ul se opreste (break) si afiseaza cele doua rezultate
                fout << "WRONG! " << result1 << ' ' << result2 << '\n'; // e gresit, deci eval-ul se opreste (break) si afiseaza cele doua rezultate
                //  break;
        }

        in1.close();
        in2.close();
    }
    fout.close();
 //   system("pause"); // doar pe windows, pentru a apuca sa citesti mesajele afisate
}
