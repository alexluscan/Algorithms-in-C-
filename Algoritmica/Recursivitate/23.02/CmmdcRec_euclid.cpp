#include <iostream>
#include <cstring>
using namespace std;

// metoda scaderilor
int cmmdc(int a, int b)
{
	if (b == 0)
		return a;
	return cmmdc(b, a % b);
}

int main()
{
	cout << cmmdc(24, 16);
}
