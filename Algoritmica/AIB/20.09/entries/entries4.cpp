#include <fstream>
#define IN "entries.in"
#define OUT "entries.out"
using namespace std;

void Union(int,int);
int Find(int);
void cit();

int n=0,N;
int t[10000001],h[10000001];

int main()
{
    cit();    
}

void cit()
{
    int i,j,x1,x2,r1,r2;
    ifstream f(IN);
    f>>N;
    for(i = 1; i <= N;i ++)   
        {
                f>>x1>>x2>>j;
                if(x1>n)n=x1;
                if(x2>n)n=x2;
        }                    
    for(i = 1; i <= n; i ++)
        {
                t[i]=i;             
                h[i]=0;
        }        
    f.close();

    ifstream f1(IN);
    ofstream g(OUT);
    f1>>N;
    for(i = 1; i <= N ; i ++)
        {
                f1>>x1>>x2>>j;
                r1=Find(x1);r2=Find(x2);
                
                if(j==1)if(r1!=r2)Union(r1,r2);
                if(j==2)if(r1==r2)g<<"1\n";
                                else g<<"0\n";
        }    
    f1.close();
    g.close();
}

void Union(int x, int y)
{
	if (h[x] > h[y]) t[y] = x;
		else
		{
			t[x] = y;
			if (h[x] == h[y]) ++h[y];
		}
}
int Find(int x)      // cautare cu compresie
{
	if ( x != t[x] ) t[x] = Find(t[x]);
	return t[x];
}

/*nt Find( int nod )   // cautare cu compresie iterativ
{
	long int rad = nod;
	while( rad != t[rad] )
		rad = t[rad];
	long int f;
	while( nod != rad )
	{
		f = t[nod];
		t[nod] = rad;
		nod = f;
	}
	return rad;
}*/

