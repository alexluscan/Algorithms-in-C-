#include<stdio.h>
#include<algorithm>
#define max(i,j) i>j?i:j
using namespace std;
int n,p,lim;
int v[1024],poz[16],x[4100],d[4100][1024];

int bit(int a)
{
	int nr=0;
	while(a)
	{
		a=a&(a-1);
		nr++;
	}
	return nr;
}

bool cmp(int a, int b)
{
	return (bit(a)<bit(b));
}

int main()
{
	freopen("morcovi.in","r",stdin);
	freopen("morcovi.out","w",stdout);
	scanf("%d",&n);
	int i,j,k;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&v[i]);
		d[0][i]=v[i];
	}
	scanf("%d",&p);
	lim=(1<<p)-1;
	for(i=0;i<p;i++)
		scanf("%d",&poz[i]);
	for(i=0;i<=lim;i++)
		x[i]=i;
	sort(x,x+lim+1,cmp);
	for(i=0;i<=lim;i++)
		for(j=1;j<=n;j++)
			for(k=0;k<p;k++)
				if((i&(1<<k))==0)
				{
					if(j+poz[k]<=n)
						d[i+(1<<k)][j+poz[k]]=max(d[i+(1<<k)][j+poz[k]],d[i][j]+v[j+poz[k]]);
					if(j-poz[k]>=1)
						d[i+(1<<k)][j-poz[k]]=max(d[i+(1<<k)][j-poz[k]],d[i][j]+v[j-poz[k]]);
				}
	int maxim=-1;
	for(i=1;i<=n;i++)
		if(d[lim][i]>maxim)
			maxim=d[lim][i];
	printf("%d\n",maxim);
	return 0;
}
