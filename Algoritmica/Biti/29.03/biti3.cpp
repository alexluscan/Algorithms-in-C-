// Setarea unui bit (il facem 1)
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

	
	int i = 2;
	
	// Set Bit
//	msk = msk | (1 << i);
	msk |= 1 << i;
	
	B2(msk);
}
