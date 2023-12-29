// In cate moduri poate urca o scara cu n trepte, stiind ca la fiecare pas poate sa urce 1, 2, sau k trepte
// Initial este pe treapta 1
#include <fstream>
using namespace std;

const int Mod = 9001, Dim = 1000001;
int nr[Dim]; // nr[i] = nr de moduri de a ajunge pana la orice treapta j <= i

ifstream fin("scari.in");
ofstream fout("scari.out");

int main()
{
    int n, k;
    fin >> n >> k;
    
    nr[1] = nr[2] = 1;
  
    for (int i = 3 ; i <= k; ++i) 
        nr[i] = (2 * nr[i - 1]) % Mod; // = nr[i - 1] daca prelungesti toate drumurile cu un pas pana in i
                                       // + nr[i - 1] daca nu le prelungesti si ramai cu aceleasi drumuri

    for (int i = k + 1 ; i <= n; ++i)
        nr[i] = (2 * nr[i - 1] - nr[i - k - 1] + Mod) % Mod;
        
    fout << nr[n];
}
