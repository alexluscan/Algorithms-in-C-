// OK
/**
 * Operation 1: Increment the elements within range [L, R] with value val
 * Operation 2: Get max element within range [L, R]
 * O(log n) / query
 */
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int Inf = 0x3f3f3f3f, Dim = 20000;
int a[Dim];

class SegTree {
public:
	SegTree(int _n) : n(_n) 
	{
		Max = cnt = vector<long long>(4 * n); 
		Build(1, 0, n - 1);
	}
	
	void Update(int _L, int _R, int v)
	{
		L = _L; R = _R;
		Update(1, 0, n - 1, v);
	}
	
	long long Query(int _L, int _R)
	{
		L = _L; R = _R;
		return Query(1, 0, n - 1);
	}
	
protected:	
	void Update(int x, int l, int r, int v)
	{
		if ( L <= l && r <= R )
		{
			Max[x]  += v;   // update current node
			cnt[x] += v;    // flag current node
			return;         // we're lazy: don't bother to update the sons  
		}
		
		PushDown(x, l, r); // we can't be lazy anymore
		
		int m = (l + r) / 2;
		if ( L <= m ) Update(2 * x, l, m,  v);
		if ( m < R  ) Update(2 * x + 1, m + 1, r, v);

		if ( l != r )      // if this node has children 
			Max[x] = max(Max[2 * x], Max[2 * x + 1]);
	} 
	
	long long Query(int x, int l, int r)
	{
		if ( L <= l && r <= R )
			return Max[x]; 
		
		PushDown(x, l, r);   // push the information down the tree
		
		int m = (l + r) / 2;
		int q1 = -Inf, q2 = -Inf;
		
		if ( L <= m )
			q1 = Query(2 * x, l, m);
		if ( m < R )
			q2 = Query(2 * x + 1, m + 1, r);
			
		return Max[x] = max(q1, q2); 
	}
	
	void PushDown(int& x, int &l, int &r)
	{
		if ( l < r && cnt[x] )          // x has children and it's flagged 
		{
			cnt[2 * x]     += cnt[x];   // flag the children
			cnt[2 * x + 1] += cnt[x];     
			Max[2 * x]       += cnt[x]; // update the children with flag
			Max[2 * x + 1]   += cnt[x];
			cnt[x] = 0;                 // clear the flag
		}
	}
	
	void Build(int x, int l, int r)
	{
		if ( l == r )
		{
			Max[x] = a[l];
			return;
		}
		
		int m = (l + r) / 2;
		Build(2 * x, l, m);
		Build(2 * x + 1, m + 1, r);
		Max[x] = max(Max[2 * x], Max[2 * x + 1]);
	}
	
private:
	int n, L, R;
	vector<long long> cnt, Max;
};

int n, m;
ifstream fin("sir.in");
ofstream fout("lazy.out");

int main()
{
	fin >> n >> m;
	for (int i = 0; i < n; ++i)
		fin >> a[i];
	
	SegTree s(n);	

	int op, L, R, val;
	while ( m-- )
	{
		fin >> op;
		fin >> L >> R;
		if (op == 1 )
		{
			fin >> val;
			s.Update(L, R, val);
		}
		else
			fout << s.Query(L, R) << '\n';
	}
	fin.close();
	fout.close();
}


