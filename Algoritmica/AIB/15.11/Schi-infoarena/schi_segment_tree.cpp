#include<stdio.h>
#define nmax 30005
int i, x, n, poz, s;
int v[nmax], sum[65600], rez[nmax];

void update(int st, int dr, int nod)
{
    if (st==dr)
        sum[nod]+=x;
    else
    {
        long mij=(st+dr)/2;
        if (poz<=mij)
            update(st,mij,2*nod);
        else
            update(mij+1,dr,2*nod+1);
        sum[nod]=sum[2*nod]+sum[2*nod+1];
    }
}

void query(int st, int dr, int nod)
{
    if (st==dr)
        poz=st;
    else
    {
        long mij=(st+dr)/2;
        if (s+sum[2*nod]>=x)
            query(st,mij,2*nod);
        else
        {
            s+=sum[2*nod];
            query(mij+1,dr,2*nod+1);
        }
    }
}

int main()
{
    freopen("schi.in","r",stdin);
    freopen("schi.out","w",stdout);
    scanf("%ld",&n);
    for (i=1;i<=n;i++)
    {
        scanf("%ld",&v[i]);
        poz=i;  x=1;    update(1,n,1);
    }
    for (i=n;i>=1;i--)
    {
        s=0;    x=v[i];
        query(1,n,1);
        rez[poz]=i;
        x=-1;
        update(1,n,1);
    }
    for (i=1;i<=n;i++)
        printf("%ld\n",rez[i]);
    return 0;
}
