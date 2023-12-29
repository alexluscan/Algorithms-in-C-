#include <iomanip>
#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;

using PI = pair<int, int>;
using VI = vector<int>;
using VP = vector<PI>;

int main()
{
	VI v;
	
	int n;
	cin >> n;
	
//	v = vector<int>(n, 100);
	v = VI(n, 100);
	
	for (const int& x : v)
		cout << x << ' ';
}
