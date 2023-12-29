#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

const int TESTE = 100;

int main()
{
    srand(time(0));

    for (int test = 1; test <= TESTE; ++test)
    {
        ofstream out("part.in");

        int N = rand() % 100 + 1; // trebuie setata o limita pentru care brut-ul sa poata rula ok
        out << N << ' ';

		int K = max(min(N - 1, rand() % 100 + 1), 1); // trebuie setata o limita pentru care brut-ul sa poata rula ok
        out << K << '\n';
        out.close();

        int result1; // rezultatul dat de sursa (dinamica)
        int result2; // rezultatul dat de brut (back)

        // rulez prima sursa
       //system("start /wait part2_nou.exe"); // pe windows
        system("./part_min_k_pd");

        ifstream in1("part.out");
        in1 >> result1;
        in1.close();

        // rulez brut-ul
        system("./part_min_K_back");
        // pe linux e: system("./brut");

        ifstream in2("part.out");
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
