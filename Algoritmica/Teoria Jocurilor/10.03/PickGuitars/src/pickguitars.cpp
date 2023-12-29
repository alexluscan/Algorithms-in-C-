#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;


class PickGuitars {
private:
	int memo[60][60];
	vector<int> v;
	int n;
	int total;
	int res;
	
public:
	int maxValue(vector <int> gVal) 
	{		
		n = gVal.size();
		v.resize(n);
		res = -1;
		total = 0;
		int sum = 0;
		
		for (int i = 0; i < n; ++i )
			sum += gVal[i];
			
		for ( int i = 0; i < n; ++i )
		{
			for ( int j = (i + 1) % n, k = 0; i != j; j = (j + 1) % n, k++)
				v[k] = gVal[j];
		
			memset(memo, -1, sizeof(memo));		
			
			res = max(res, sum - GetMax(0, n - 2) );
		}
		return res;
	}
	
	int GetMax(int l, int r)
	{
	//	cout << l << ' ' << r << '\n';
		if ( l > r )
			return 0;
		if ( memo[l][r] != -1 )
			return memo[l][r];
		int total = 0;
		for (int i = l; i <= r; ++i )
			total += v[i];
		int ret = -1;
		for ( int i = l; i <= r; ++i )
			ret = max(ret, total - GetMax(l, i - 1) - GetMax(i + 1, r) );

		return memo[l][r] = ret;
	}
};



int main()
{
	vector<int> v = {2,1,4,1,2,1,8,1}; //{4,8,4}; //{1, 5, 3, 4, 5};
	cout << PickGuitars().maxValue(v);
}
