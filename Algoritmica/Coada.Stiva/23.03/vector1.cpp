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
	VI v = {10, 20, 30, 40}; // vector vid
	
	VP a = {{1, 3}, {4, 5}, {3, 7}};
	
	for (PI& p : a)
		cout << p.first << ' ' << p.second << '\n';
		
	PI p = {10, 30};
}
