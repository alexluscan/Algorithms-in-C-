#include <iomanip>
#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

// Type Aliasing
using VI  = vector<int>;
using VVI = vector<VI>;

//vector<vector<int>> a;
VVI a;

int main()
{
	
	int n, m;
	cin >> n >> m;
	a = VVI(n + 1, VI(m + 1));      // a[0], a[1], ..., a[n]   
	
	
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
			cout << a[i][j] << ' ';
		cout << '\n';
	}
	
}
