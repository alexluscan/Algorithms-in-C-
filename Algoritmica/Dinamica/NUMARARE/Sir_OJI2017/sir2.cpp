// OK

#include <fstream>
using namespace std;


const int  Mod  = 20173333;
int a[131072];
int sol[131072];

int main()
{
    ifstream fin("13-sir.in"); ofstream fout("sir.out");
    int n, x, p;

    fin >> p;
    fin >> n >> x;
    if (p == 1)
    {
    }
    else
    {
        sol[1] = 1;
        a[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            a[i] = sol[i - 1];  // pe poz i pun o val noua (urmatoarea)  (dar pana la poz i - 1 fiecare valoare se poate repeta de max x ori)
            sol[i] = sol[i - 1]; // pun valoare noua pe poz i
            
            if (i >= x)
            {
                sol[i] += sol[i - 1] - a[i - x]; // punem aceeasi valoare pe poz i , dar scadem sirurile care incep cu val noua pe poz i - x
                if (sol[i] < 0 )
					sol[i] += Mod;
			}
            else
            {
                sol[i] += sol[i - 1]; // nr de moduri in care putem adauga o val noua + nr moduri in care adaugam aceeasi val ca pe poz i - 1 
                if (sol[i] > Mod)
					sol[i] -= Mod;
			}
        }                                                 // pe poz i (inclusiv) pun cel mult x de i     

       fout << sol[n] << "\n";
   }
   return 0;
}
