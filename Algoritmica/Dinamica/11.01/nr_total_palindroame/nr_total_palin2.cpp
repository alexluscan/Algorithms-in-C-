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
    freopen("palindrom.in", "r", stdin); 
    freopen("palindrom.out", "w", stdout);
    scanf("%d", &n);
    scanf("%s", s + 1);
    
    Dyn();
    Write();
    
    return 0;
}

void Dyn() // PD - mixta
{
    for ( int i = 1; i <= n; i++ ) 
        p[i][i] = true, nrp++;
    
    int j;
    // O(n^2)
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
    int i, j;
      
    printf("Nr max de palindroame: %d\n", nrp);
    
    for ( i = 1; i <= n; i++ )
        printf("%c ", s[i] );
    printf("\n" );
    
    for ( i = 1; i <= n; i++ )
    {
        for ( j = 1; j <= n; j++ )
            printf("%d ", p[i][j] );
        printf("\n" );
    }
}
    
