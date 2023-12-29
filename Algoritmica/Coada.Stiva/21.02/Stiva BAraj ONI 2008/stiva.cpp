#include <fstream.h>
#include <cstring>
using namespace std;

ofstream fout("stiva.in");
ifstream fin("stiva.out");
	
#define NMax 1001

int n;
char s[NMax+1];
int NrMin[NMax][NMax]; // NrMin[i][j] = nr minim de operatii push pt a obtne secventa s[i...j]
         
int main()
{	
	int d, t, j;
	fin >> s;
	n = strlen(s);

	for (int i = 0; i < n; i++) 
		NrMin[i][i] = 1;
		
	for (int d = 2; d <= n; d++)
		for (int i = 0; i + d - 1 < n; i++)
		{
			j = i + d - 1;
			NrMin[i][j] = 1 + NrMin[i][j - 1]; // push(s[j])
			
			for (int t = i; t < j; t++)
				if (s[t] == s[j])
					if (NrMin[i][t] + NrMin[t + 1][j - 1] < NrMin[i][j])
						NrMin[i][j] = NrMin[i][t] + NrMin[t + 1][j - 1];
		 }
		 
	// 2 * nr oper push, pt ca nr op push == nr op pop si se adauga n operatii pop
	fout << 2 * NrMin[0][n - 1] + n << '\n';
	fout.close();
	return 0;
}


