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

const int Inf = 0x3f3f3f3f;

int main()
{
	
	int n, m;
	cin >> n >> m;
	a = VVI(n + 1, VI(m + 1, 8));      // a[0], a[1], ..., a[n]   
	
	
	for (VI& l : a)
	{
		for (int& x : l)
			cout << x << ' ';
		cout << '\n';
	}
	
}
