#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class PickGuitars {
public:
	int maxValue(const vector<int>& guitarValues)
	{
		n = guitarValues.size();
		v = guitarValues;
		
		
		int res = -1;
		int total = 0;
		for (const int& x : v)
			total += x;
		
		for (int i = 0; i < n; ++i)
		{
			v.clear();
			for (int k = i + 1; k < n; k++)
				v.push_back(guitarValues[k]);
			
			for (int k = 0; k < i; k++)
				v.push_back(guitarValues[k]);
			
			memset(dp, -1, sizeof(dp));
			res = max(res, total - SMax(0, n - 2));
		}
		
		return res;
	}
	
	int SMax(int l, int r)
	{
		
		cout << l << ' ' << r << '\n';
		if (l > r) return 0;
		
		if (dp[l][r] != -1)
			return dp[l][r];
			
		int total = 0;	
		for (int i = l; i <= r; ++i)
			total += v[i];
			
		int res = -1;
		for (int i = l; i <= r; ++i)
			res = max(res, total - SMax(l, i - 1) - SMax(i + 1, r));
		
		return dp[l][r] = res;
	}
	
private:
	int n;
	vector<int> v;
	int dp[55][55];
};


int main()
{
	cout << PickGuitars().maxValue({2,1,4,1,2,1,8,1});
}
