/* Suma cifrelor unui numar
 * 
 */ 
#include <iostream>
using namespace std;

int SumaCifrelor(int n)
{
	if (n == 0)
		return 0;
	return n % 10 + SumaCifrelor(n / 10);
	
}

int main()
{
	cout << SumaCifrelor(123);
}
