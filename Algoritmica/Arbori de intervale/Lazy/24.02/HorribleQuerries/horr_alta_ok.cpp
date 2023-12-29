// AC SPOJ (3.30 SEC)

#include<stdio.h>

long long v[500000];
long long a[500000];
inline long long getvalue( int x, int low, int high)
{
	return a[x] + (high-low+1)*v[x];
}

long long update( long long x, long long down, long long up, long long low, long long high,long long value)
{
	long long mid = (low+high)/2;
	if( down <= low && high <= up)
	{
		v[x] += value;
		return 0;
	}
	if(low > up || high < down)  return 0;
	v[2*x] += v[x];
	v[2*x+1] += v[x];
	v[x] = 0;
	update( 2*x, down,up, low,mid,value);
	update(2*x+1 , down,up, mid+1, high,value);
	a[x] = getvalue(2*x, low, mid) + getvalue(2*x+1 , mid+1,high);
	return 0;
}

long long query( long long x, long long down, long long up, long long low, long long high)
{
	long long mid = (low+high)/2;
	if( down <= low && high<=up)
		return a[x] + v[x]*( high-low+1);
	if( low > up || high < down) return 0;
	v[2*x] += v[x];
	v[2*x+1] += v[x];
	a[x] = getvalue(2*x, low, mid) + getvalue(2*x+1 , mid+1,high);
	v[x] =0;
	return query( 2*x,down,up, low, mid)+query(2*x+1, down,up, mid+1, high);
}

int main()
{
	long long t,n,p,quer,vr,val,i,q;
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&quer);
		for(i=0;i<=4*n;i++) a[i] =0,v[i] =0;
		while(quer--)
		{
			scanf("%lld%lld%lld",&vr,&p,&q);
			if(!vr)
			{
				scanf("%lld",&val);
				update( 1,p,q,1,n,val);
			}
			else
				printf("%lld\n",query( 1, p, q, 1, n));
		}
	}
	return 0;
}
