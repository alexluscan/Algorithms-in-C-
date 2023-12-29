// Nr TOTAL de palindroame intr-un sir
// O(N * N)
#include <stdio.h>
#define Max 101

int n;
bool p[Max][Max];
char s[Max];
int nrp;

void Read();
void Dyn();
void Write();

int main()
{
    Read();
    Dyn();
    Write();
    
    return 0;
}

void Read()
{
    int i = 0;
    char c;
    
    FILE *fin = fopen("palindrom.in", "rt" );
    fscanf(fin, "%d\n", &n );
    for ( i = 1; i <= n; i++ )
        fscanf(fin, "%c", &s[i] );
        
    fclose(fin);
}

void Dyn() // PD O(n^2)
{
	// initializare diagonala principala
    for ( int i = 1; i <= n; i++ ) 
        p[i][i] = true, nrp++;
    
    // O(n^2)
    int j;
    for ( int d = 1; d <= n; d++ )       // d - lungimea secventei - 1
        for ( int i = 1; i + d <= n; i++ ) // i - capatul din stanga
        {
			j = i + d;
            if ( d == 1 )  // interval format din 2 elemente
				p[i][j] = s[i] == s[j];
            else  
				p[i][j] = (s[i] == s[j]) && p[i + 1][j - 1];
		
			if ( p[i][j] ) nrp++;
        }    
}    

void Write()
{
    FILE *fout =fopen("palindrom.out", "wt" );    
    fprintf(fout, "Nr max de palindroame: %d\n", nrp);
    
    for ( int i = 1; i <= n; i++ )
        fprintf(fout, "%c ", s[i] );
    fprintf(fout, "\n" );
    
    for ( int i = 1; i <= n; i++ )
    {
        for ( int j = 1; j <= n; j++ )
            fprintf(fout, "%d ", p[i][j] );
        fprintf(fout, "\n" );
    }
    fclose(fout);
}
    
