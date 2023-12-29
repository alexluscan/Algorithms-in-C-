void Union(int x, int y)
{
	if (h[x] > h[y]) p[y] = x;
		else
		{
			p[x] = y;
			if (h[x] == h[y]) ++h[y];
		}
}

int Find(int x)      // cautare cu compresie
{
	if ( x != p[x] ) p[x] = Find(p[x]);
	return p[x];
}

int Find( int nod )   // cautare cu compresie iterativ
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
}