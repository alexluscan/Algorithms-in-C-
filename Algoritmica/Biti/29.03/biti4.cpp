// Clear bit (il facem 1)
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
	int msk = 10;
	B2(msk); cout << '\n';

	
	int i = 1;
	
	// Clear Bit
	if (msk & (1 << i)) // daca bitul i este 1
		msk ^= 1 << i;  // il fac 0
	
	B2(msk);
}
