// OK
// Nr de partitii nedescrescatoare cu cel mai mic termen K
#include <fstream>
using namespace std;

ifstream fin("part.in");
ofstream fout("part.out");

void Back(int k, int suma);
void Write(int k);

int x[101], n, P, nrsol;
int sol[101];

int main()
{
    fin >> n >> P;
    fin.close();
	x[1] = P;
    Back(2, P);
    fout << "back: " << nrsol;
  //  for (int i = 1; i <= n; ++i)
  //        fout << sol[i] << " partitii de cate " << i << '\n';
    fout.close();
    return 0;
}

void Back(int k, int suma)
{
    if (suma == n)
    {
        Write(k - 1);
        return;
    }
    if (k > n) return;
    for (int i = x[k-1];  suma + i <= n; ++i)  // !!! expresie ? varianta_DA : var_NU
    {
        x[k] = i;
        Back(k + 1, suma + i);
     //   x[k] = 0;

    }
}

void Write(int n)
{
    nrsol++;
/*    for (int i = 1; i <= n; ++i)
		fout << x[i] << ' ';
	fout << '\n';
*/
 /*   int m = 0;
    for (int i = 1; i <= n && x[i]; ++i)
         if (x[i]) m++;
    sol[m]++;
*/
}
