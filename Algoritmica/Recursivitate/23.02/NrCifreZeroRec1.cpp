#include <iostream>
#include <cstring>
using namespace std;

void nr_cif_zero(int n, int& nr)
{
	if (n == 0)
	{
		nr = 1;
		return;
	}
	
	if (n < 10)
	{
		nr = 0;
		return;
	}
	nr_cif_zero(n / 10, nr);
	if (n % 10 == 0)
		nr++;
}

int main()
{
	int nr;
	nr_cif_zero(0, nr);
	cout << nr;
}
