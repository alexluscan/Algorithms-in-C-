//nr de partitii crescatoare a lui n,   a. i. termenul maxim din orice partitie este CEL MULT K
#include <fstream>
using namespace std;

ifstream fin("part.in");
ofstream fout("part.out");

void Back(int k, int suma);
void Write(int k);

int x[101], n, K, nrsol;

int main()
{
    fin >> n >> K;
    fin.close();
	
    Back(1, 0);
    fout  << nrsol;

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
    for (int i = (k == 1) ? 1 : x[k-1];  i <= K && suma + i <= n; ++i)  
    {
        x[k] = i;
        Back(k + 1, suma + i);
    }
}

void Write(int n)
{
    nrsol++;
/*   for (int i = 1; i <= n; ++i)
		fout << x[i] << ' ';
	fout << '\n';
*/
}
