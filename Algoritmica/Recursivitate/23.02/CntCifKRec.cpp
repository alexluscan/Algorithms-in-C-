#include <iostream>
#include <cstring>
using namespace std;

void cnt_cif(int n, int k, int& c)
{
	if (n < 10)
	{
		c = n >= k;
		return;
	}
	
	cnt_cif(n / 10, k, c);
	if (n % 10 >= k)
		c++;
}

int main()
{
}
