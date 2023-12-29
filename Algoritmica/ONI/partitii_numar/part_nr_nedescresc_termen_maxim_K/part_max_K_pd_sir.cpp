// OK 
// Nr de partitii crescatoare a lui n cu cel mai mare termen K
// O(n * k)
#include <fstream>
using namespace std;

ifstream fin("part.in");
ofstream fout("part.out");

void Debug();

int a[500];   // a[i] - nr de partitii a lui i cu ultimul (cel mai mare) termen j
int n, k;     // k - cel mai mare termen al oricarei partitii 

int main()
{
	fin >> n >> k;

	
	a[0] = 1;
        
    for (int j = 1; j <= k; ++j)
        for (int i = j; i <= n; ++i)
            a[i] += a[i - j];
   
	fout << a[n];
	
	fin.close();
	fout.close();
}

