// OK
#include <fstream>
#include <iostream>
using namespace std;

#define DIM 20001

struct segment {
    int x, y1, y2, sgn;
} a[5*DIM],aux;

int n, c;
long long aria;
long long sum[10*DIM];
int nrs[10*DIM];

void cit();
void qsort(int, int);
void Sweep();
void Update(int,int,int,int,int,int);
void afis();

int main()
{
    cit();
    qsort(1, n);
    Sweep();
    afis();
    return 0;
}    

void cit()
{
    ifstream fin("mar10.in");
    fin>>n;
    int i,xsj,ysj,xds,yds,k=1;
    for(i=1;i<=n;i++)
    {
        fin>>xsj>>ysj>>xds>>yds;
        a[k].x=xsj;
        a[k].y1=ysj;
        a[k].y2=yds;
        a[k++].sgn=1;
        a[k].x=xds;
        a[k].y1=ysj;
        a[k].y2=yds;
        a[k++].sgn=-1;
    }
    n*=2;
    fin.close();
}        

void qsort(int st,int dr)
{
    int piv,i,j;
    piv=a[st].x;
    i=st-1;
    j=dr+1;
    do
    {
        do { i++; } while ( a[i].x < piv );
        do { j--; } while ( a[j].x > piv );
        if ( i <= j )
        {
            aux=a[i];
            a[i]=a[j];
            a[j]=aux;
        }
    } while ( i <= j);
    if(i<dr)qsort(i,dr);
    if(j>st)qsort(st,j); 
}    

void Sweep()
{
    for(c=1;c<=n;c++)
    {
        aria+=sum[1]*(a[c].x-a[c-1].x);
        Update(1, 0, 30001, a[c].y1, a[c].y2 - 1, a[c].sgn);    
    }
}

void Update(int i,int l, int r, int a, int b, int semn)
{
    if ( a <= l && b >= r)
    {
        nrs[i] += semn;
        if (nrs[i] > 0)
            sum[i] = r - l + 1;
        else sum[i] = sum[2*i] + sum[2*i + 1];
        return;
    }    
    int m =(l + r) / 2;
    if (a <= m)    
        Update(i*2, l, m, a, b, semn);
    if (b > m)
        Update(i*2+1, m + 1, r, a, b, semn);    
    
    if (nrs[i] )
		sum[i] = r - l + 1;
	else
        sum[i]=sum[i*2] + sum[2*i + 1];
}                        

void afis()
{
    ofstream fout("mars.out");
    fout << aria;
    fout.close();
}    
