#include <iostream>
using namespace std;

void B2(int x)
{
	if (x == 0)
		return;
	B2(x / 2);
	cout << x % 2;
}

int main()
{
	int x = 10;
	B2(x); cout << '\n';
	
//	x <<= 1;
	B2(x << 3); cout << '\n';
	
	B2(x >> 2);
	
}
