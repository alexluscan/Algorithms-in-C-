#include <iostream>
#include <algorithm>
using namespace std;

struct pachet{
        double v,w,p;
};

pachet v[1005];

int n,G;

void citire()
{
    int i;
    cin>>n>>G;
    for(i=0;i<n;i++)
        cin>>v[i].w>>v[i].v,v[i].p=v[i].v/v[i].w;
}

bool ord(pachet x,pachet y)
{
    return (x.p>y.p);
}

int main ()
{
    double lt=0.;
    citire();
    sort(v,v+n,ord);
    int i=0;
    while(G>0 && i<n)
    {
        if(G>v[i].w)
        {
            lt=lt+v[i].v;
            G=G-v[i].w;
        }
        else
        {
            double r=G/v[i].w;
            G=0;
            lt=lt+r*v[i].v;
        }
        i++;
    }
    cout<<lt;
}
