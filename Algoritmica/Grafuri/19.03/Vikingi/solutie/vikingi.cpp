#include <stdio.h>

#define INF 30000

short int nr[2002][2];
int V, C;            // vikingi, corabii
int c, v, vi;
short m, maxim;

int main()
{
    freopen("vikingi.in", "r", stdin);
    freopen("vikingi.out", "w", stdout);
    
    scanf("%d", &V);
    scanf("%d", &C);
    int f = 1, l = 0;    
    for ( v = 1; v <= V; v++ ) // cu o singura corabie, trebuie efectuate exact v lansari
        nr[v][l] = v;            

    for ( c = 2; c <= C; c++, f = !f, l = !l )
    {
	    for ( v = 1; v <= V; v++ )        
	    {
	        m = INF;
            for ( vi = 1; vi <= v; vi++)  
            {
               if ( nr[v-vi][f] > nr[vi-1][l]) 
                  maxim = nr[v-vi][f];
               else
                  maxim = nr[vi-1][l];
               if ( m > maxim + 1 )
                  m = maxim + 1;               
            }   
            nr[v][f] = m;
        }   
        int identice = 1;                  // Daca coloana actuala nu difera de cea precedenta
        for ( v = 1; v <= V; v++ )         // oprim totul
           if ( nr[v][0] != nr[v][1] )
           {
              identice = 0;
              break;
           }
       if ( identice ) break;   
    }   
                         
    printf("%d\n", nr[V][l]);
     
   return 0;
}   
