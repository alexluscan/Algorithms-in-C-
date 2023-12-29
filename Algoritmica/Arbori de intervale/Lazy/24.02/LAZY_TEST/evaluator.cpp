// OK
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

const int TESTE = 1000;

int main()
{
    ofstream fout("rez.txt");
    srand(time(0));
    for (int test = 1; test <= TESTE; ++test)
    {
        ofstream out("sir.in");
     //   int T  = rand() % 5 + 1;
        int n = rand() % 1000 + 1; // trebuie setata o limita pentru care brut-ul sa poata rula ok
        int m = rand() % 1000 + 1;
        
        out << n << ' ' << m << '\n';

        for (int i = 1; i <= n; ++i)
			out << rand() % 2000 - 1000 << ' ';
		out << '\n';
        for (int i = 1; i <= m; ++i)
        {
			int op = rand() % 2 + 1;
			int x = rand() % n;
			int y = x + (rand() % (n - x));
            out << op << ' ' << x << ' ' << y << ' ';
             if ( op == 1 )
				out << rand() % n - n / 2 << '\n';
			else 
				out << '\n';
        }

        out.close();

        int result1; // rezultatul dat de sursa (dinamica)
        int result2; // rezultatul dat de brut (back)

            // rulez prima sursa
      // system("start /wait sursa.exe"); // pe windows
        system("./brut");
        system("./lazy_test");
        

        ifstream in1("lazy.out");
        ifstream in2("brut.out");
        in2 >> result2;
        in1 >> result1;
        if (result1 == result2)
        {
              cerr << "OK!\n"; // afisare la standard error (ca sa apara sigur in terminal)
            //fout << "OK!\n";
            
        }
        else
        {
              cerr << "WRONG! " << result1 << ' ' << result2 << '\n'; // e gresit, deci eval-ul se opreste (break) si afiseaza cele doua rezultate
              //fout << "WRONG! " << result1 << ' ' << result2 << '\n'; // e gresit, deci eval-ul se opreste (break) si afiseaza cele doua rezultate
              break;
        }

        in1.close();
        in2.close();
    }
    fout.close();
 //   system("pause"); // doar pe windows, pentru a apuca sa citesti mesajele afisate
}
