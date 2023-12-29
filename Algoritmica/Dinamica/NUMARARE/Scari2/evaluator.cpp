#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

const int TESTE = 100;


const int MOD = 10000;

int main()
{
    srand(time(0));

    for (int test = 1; test <= TESTE; ++test)
    {
        ofstream out("scari.in");

        int N = rand() % MOD + 1; // trebuie setata o limita pentru care brut-ul sa poata rula ok
        int M = rand() % MOD + 1; //
        if ( N > M)
			out << N << ' ' << M << '\n';
		else
			out << M <<  ' ' << N;

        out.close();

        int result1; // rezultatul dat de sursa (dinamica)
        int result2; // rezultatul dat de brut (back)

        // rulez prima sursa
       // system("start /wait fotbal_din.exe"); // pe windows
        system("./scari_aib2");

        ifstream in1("scari.out");
        in1 >> result1;
        in1.close();

        // rulez brut-ul
       // system("start /wait fotbal_back.exe");
        system("./scari_n");

        ifstream in2("scari.out");
        in2 >> result2;
        in2.close();

        if (result1 == result2)
        {
            cerr << "OK!\n"; // afisare la standard error (ca sa apara sigur in terminal)
        }
        else
        {
            cerr << "WRONG! " << result1 << ' ' << result2 << '\n'; // e gresit, deci eval-ul se opreste (break) si afiseaza cele doua rezultate
            break;
        }
    }

 //   system("pause"); // doar pe windows, pentru a apuca sa citesti mesajele afisate
}

