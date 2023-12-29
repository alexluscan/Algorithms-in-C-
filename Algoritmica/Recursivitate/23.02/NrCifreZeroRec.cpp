#include <iostream>
#include <cstring>
using namespace std;

int nr_cif_zero(int n)
{
	if (n == 0)
		return 1;
	if (n < 10)
		return 0;
	if (n % 10 == 0)
		return 1 + nr_cif_zero(n / 10);
	return nr_cif_zero(n / 10);
}

int main()
{
}
