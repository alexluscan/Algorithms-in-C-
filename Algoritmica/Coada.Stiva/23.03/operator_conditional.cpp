#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;
	
	int c;
	if (a > b)
		c = a;
	else
		c = b;
		
	// operator ternar (conditional)
	c = a > b ? a : b;
	
	cout << c;
}

