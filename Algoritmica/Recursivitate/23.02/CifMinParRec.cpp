#include <iostream>
#include <cstring>
using namespace std;

int cifminpar(int n) 
{
	if (n == 0)
		return 0;
	if (n < 10)
	{
		if (n % 2 == 0)
			return n;
		return -1;
	}
	
	int res = cifminpar(n / 10);
	
	if (n % 2 == 0)
	{
		if (res == -1)
			return n % 10;
		return min(n % 10, res);
	}
	
	return res;
}

int main()
{
	cout << cifminpar(0);
}
