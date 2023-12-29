#include <iostream>
#include <cstring>
using namespace std;

void factorial(int n, int& f)
{
	if (n == 0)
	{
		f = 1;
	}
	
	factorial(n - 1, f);
	f *= (n - 1);
}

int main()
{
}
