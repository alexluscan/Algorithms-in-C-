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
        ofstream out("horrible.in");
        int T  = rand() % 5 + 1;
        int N = rand() % 10000 + 1; // trebuie setata o limita pentru care brut-ul sa poata rula ok
        int C = rand() % 200 + 1;
        int v;
        out << T << '\n';
        while ( T-- )
        {

            out << N << ' ' << C << '\n';
            int p, q, op;
            for (int i = 1; i <= C; ++i)
            {
                p = rand() % 7000 + 1;
                op = rand() % 2;
                v = rand() % 3000;
                if ( op == 0 )
                    out << op <<  ' ' << p << ' ' << p + rand() % (10000 - p )
                        << ' ' << v << '\n';
                else
                    out << op << ' ' << p << ' ' << p + rand() % (10000 - p )
                        << '\n';

            }
        }
        out.close();

            int result1; // rezultatul dat de sursa (dinamica)
            int result2; // rezultatul dat de brut (back)

            // rulez prima sursa
            //system("start /wait sursa.exe"); // pe windows
            system("./horriblequeries2");
            system("./horriblequeries_fara_lazy");

            ifstream in1("horrible.out");
            ifstream in2("horrible.ok");

            while ( in2 >> result2 )
            {
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
            }
            in1.close();
            in2.close();

    }
    fout.close();
 //   system("pause"); // doar pe windows, pentru a apuca sa citesti mesajele afisate
}
