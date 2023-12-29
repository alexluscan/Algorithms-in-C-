#include <cstdio>
#include <algorithm>
#define NMAX 200005
 
using namespace std;
 
int n,m,i,sol,act;
int s[NMAX],poz[NMAX];
struct punct
{
    int x,y;
}v[NMAX];
 
bool cmp1(punct a,punct b)
{
    return (a.x<b.x);
}
 
bool cmp2(int a,int b)
{
    return(v[a].y < v[b].y);
}
 
void normalizare()
{
    int i,cat=1;
    for(i=1;i<=n;++i)
    {
        while(i+1 <= n && v[poz[i]].y == v[poz[i+1]].y)
        {
            v[poz[i]].y=cat;
            ++i;
        }
        v[poz[i]].y=cat;
        ++cat;
    }
}
 
struct arbore
{
    int val;
    int m;
}A[2*NMAX];
 
void update(int niv,int st,int dr,int l,int r,int val)
{
 
    if(st >= l && dr<=r)
    {
        A[niv].val += val*(dr-st+1);
        A[niv].m+=val;
        return;
    }
    int mij=(st+dr)/2;
    if(A[niv].val != A[niv*2].val + A[niv*2+1].val)
    {
         int p = (A[niv].val-A[niv*2].val-A[niv*2+1].val) / (dr-st+1);
        A[niv*2].val += p * (mij-st+1);
        A[niv*2+1].val += p * (dr-mij);
        A[niv*2].m += p;
        A[niv*2+1].m += p;
    }
 
    if(l <= mij) update(niv*2,st,mij,l,r,val);
    if(r > mij) update(niv*2+1,mij+1,dr,l,r,val);
    A[niv].m=min(A[niv*2].m,A[niv*2+1].m);
    A[niv].val=A[niv*2].val + A[niv*2+1].val;
}
void add(int st,int dr,int val)
{
    update(1,1,n,st,dr,val);
}
int main()
{
    freopen("cadrane.in","r",stdin);
    freopen("cadrane.out","w",stdout);
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    {
        scanf("%d%d",&v[i].x,&v[i].y);
        poz[i]=i;
    }
    sort(v+1,v+n+1,cmp1);
    sort(poz+1,poz+n+1,cmp2);
    normalizare();
     for(i=1;i<=n;++i) s[v[i].y]++;
     for(i=1;i<=n;++i) s[i]+=s[i-1];
    for(i=1;i<=n;++i) add(i,i,n-s[i-1]);
    act=1;
    i=1;sol=0;
    while(i <= n)
    {
        while(v[act].x < v[i].x)
        {
            add(1,v[act].y,-1);
            ++act;
        }
        while(v[i].x == v[i+1].x && i+1<=n)
        {
            add(v[i].y,n,1);
            ++i;
        }
        add(v[i].y,n,1);
        sol = max(sol,A[1].m);
        ++i;
    }
    printf("%d\n",sol);
}
