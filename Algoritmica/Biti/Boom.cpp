#include<stdio.h>
#include<vector>
#define inf 1000000000 //1000000000
#define nmax ((1<<20)+3) //((1<<20)+3)
using namespace std;
int n,m,nr,nm;
int b[53],c[53];
int h[nmax],p[nmax],d[nmax],pr[nmax],s[nmax],sol[nmax];

void up(int i)
{
	int j=i>>1,aux;
	while(j && d[h[i]]<d[h[j]])
	{
		aux=h[i];
		h[i]=h[j];
		h[j]=aux;
		p[h[j]]=j;
		p[h[i]]=i;
		i=j;
		j=j>>1;
	}
}

void down(int i)
{
	int j,k,aux;
	while(i<nr)
	{
		k=i;
		j=i<<1;
		if(j<=nr && d[h[j]]<d[h[k]])
			k=j;
		j=(i<<1)+1;
		if(j<=nr && d[h[j]]<d[h[k]])
			k=j;
		if(d[h[k]]<d[h[i]])
		{
			aux=h[i];
			h[i]=h[k];
			h[k]=aux;
			p[h[i]]=i;
			p[h[k]]=k;
			i=k;
		}
		else
			return;
	}
}

void dijkstra()
{
	int i,j,k;
	while(h[1])
	{
		i=h[1];
		for(j=1;j<=m;j++)
		{
			k=i&b[j];
			k=(k>>1)|(k<<1)&nm;
			if(d[i]+c[j]<d[k])
			{
				pr[k]=i;
				s[k]=j;
				if(d[k]==inf)
				{
					d[k]=d[i]+c[j];
					h[++nr]=k;
					p[k]=nr;
					up(nr);
				}
				else
				{
					d[k]=d[i]+c[j];
					up(p[k]);
				}
			}
		}
		h[1]=h[nr];
		p[h[1]]=1;
		nr--;
		down(1);
	}
}

int main()
{
	freopen("boom.in","r",stdin);
	freopen("boom.out","w",stdout);
	scanf("%d%d",&n,&m);
	nm=(1<<n)-1;
	int i,j,x,l;
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&c[i],&l);
		b[i]=nm;
		for(j=1;j<=l;j++)
		{
			scanf("%d",&x);
			b[i]=b[i]-(1<<(x-1));
		}
		
	}
	d[nm]=0;
	for(i=0;i<nm;i++)
		d[i]=inf;
	h[nr=1]=nm;
	p[nm]=1;
	dijkstra();
	printf("%d\n",d[0]);
	
	i=0;
	while(pr[i])
	{
		sol[++sol[0]]=s[i];
		i=pr[i];
	}
	printf("%d\n",sol[0]);
	for(i=sol[0];i>=1;i--)
		printf("%d\n",sol[i]);
	return 0;
}
