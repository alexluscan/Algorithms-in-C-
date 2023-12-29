#include <iostream>
#include <cstring>
using namespace std;

// metoda scaderilor
int cmmdc(int a, int b)
{
	if (a == b)
		return a;
	
	if (a > b)
		return cmmdc(a - b, b);
	
	return cmmdc(a, b - a);
}

int main()
{
	cout << cmmdc(24, 16);
}
