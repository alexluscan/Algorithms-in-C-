// OK
/**
 * Operation 1: Increment the elements within range [L, R] with value val
 * Operation 2: Get max element within range [L, R]
 * O(log n) / query
 */

#include <fstream>
#include <algorithm>
using namespace std;

#define Dim 20000
#define Inf 0x3f3f3f3f

long long  a[Dim], n, m;
long long Max[4 * Dim], L, R; // Max - (segment tree)
long long cnt[4 * Dim];

void Build(int x, int l, int r) 
{
  	if (l > r) return; // Out of range

  	if (l == r) 
  	{ 
		Max[x] = a[l]; 
		return;
	}
	int m = ( l + r) / 2;
	Build(2 * x, l, m); 
	Build(2 * x + 1, m + 1, r); 

	Max[x] = max(Max[2 * x], Max[2 * x + 1]); 
}

void Update(int x, int l, int r, int val) 
{
  	if (cnt[x] != 0)          // This node needs to be updated
  	{ 
   		Max[x] += cnt[x];    // Update it
		if (l != r) 
		{                              
			cnt[2 * x]     += cnt[x]; // Flag the children
    		cnt[2 * x + 1] += cnt[x];  
		}

   		cnt[x] = 0; 
  	}
  	
   if (l > r || l > R || r < L)    // Out of range
		return;
	
	if (L <= l && r <= R)
  	{ 
    	Max[x] += val;
		if (l != r)                // this node has sons
		{
			cnt[2 * x]     += val;  
			cnt[2 * x + 1] += val;
		}
    	return;
	}

	int m = (l + r ) / 2;

	Update(2 * x, l, m, val); 
	Update(2 * x + 1, m + 1, r, val); 

	Max[x] = max(Max[2 * x], Max[2 * x + 1]); 
}

long long Query(int x, int l, int r) 
{
	if (cnt[x] != 0) 
	{ 
		Max[x] += cnt[x]; // Update it

		if (l != r)
		{
			cnt[2 * x]     += cnt[x]; // Mark child as lazy
			cnt[2 * x + 1] += cnt[x]; // Mark child as lazy
		}

		cnt[x] = 0; // Reset it
	}
	
	if (L > r || l > R || r < L) return -Inf; // Out of range
	if (L <= l && r <= R)         // Current segment is totally within range [i, j]
		return Max[x];

	int m = (l + r) / 2;

	return max( Query(2 * x, l, m), Query(2 * x + 1, m + 1, r) );
}

ifstream fin("sir.in");
ofstream fout("lazy.out");

int main() 
{
	fin >> n >> m;
	for (int i = 0; i < n; i++) 
		fin >> a[i];

	Build(1, 0, n - 1);
	int op, val;
	while ( m--)
	{
		fin >> op >> L >> R;
		if ( op == 1 ) // update
		{
			fin >> val;
			Update(1, 0, n - 1, val);
		}
		else
			fout << Query(1, 0, n - 1) << '\n';
	}
	fin.close();
	fout.close();
}

