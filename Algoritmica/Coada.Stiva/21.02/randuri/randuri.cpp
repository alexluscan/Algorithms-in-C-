#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

#define MAX_ROWS 102
#define MAX_COLS 102

ifstream fin("randuri.in");
ofstream fout("randuri.out");

#define max(x,y) ((x)>(y)?(x):(y))

unsigned char  E[MAX_ROWS][MAX_ROWS];     // E[i][j] - nr max de randuri care se pot elimina in intervalul [i, j]
char R[MAX_ROWS][MAX_COLS];     // randurile
int  L;
int  SC[MAX_ROWS][MAX_ROWS];

int Common(char a[], char b[])  // cel mai lung subsir comun
{
   unsigned char C[MAX_COLS][MAX_COLS] = { 0 };    // C[i][j] - cel mai lung subsir comun secventelor a[i..m-1] si b[j..n-1]
   int m = strlen(a),  n = strlen(b);
   for (int i = m - 1; i >= 0; i--)
      for (int j = n - 1; j >= 0; j--)
	 if( a[i] == b[j] )
	    C[i][j] = C[i+1][j+1] + 1;
	 else
	    C[i][j] = max(C[i+1][j], C[i][j+1]);
   return C[0][0];
}
    
void Precompute()
{
   for (int i = 0; i < L; i++)
      for (int j = i; j < L; j++)
	 SC[i][j] = Common(R[i], R[j]) > 6;
}

void EraseRows()
{
   int i, j, k, d, max, erased;

   for (i = 0; i < L; i++)      // initializari;  pentru a putea sterge un rand,
      E[i][i] = 0;              // intervalul [i,..j] trebuie sa contina cel putin 3 randuri
   for (i = 0; i < L - 1; i++)
      E[i][i + 1] = 0;

   for (d = 2; d < L; d++)
      for (i = 0; i < L - d ; i++)
      {
    	 j = i + d;
	 max = -1;
	 for (k = i + 1; k <= j - 1; k++)
	 {
	    int erased = E[i][k] + E[k][j];
	    if ( SC[i][j] && erased == d - 2 ) erased++;
	    if ( erased > max ) max = erased;
	 }
	 E[i][j] = max;
      }
}

void Read()
{
   for ( L = 0; fin.getline(R[L], 252); L++ );
   fin.close();
}

void Write()
{
   fout << int(E[0][L - 1]) << '\n';
   fout.close();
}

int main()
{
   Read();
   Precompute();
   EraseRows();
   Write();
   return 0;
}
