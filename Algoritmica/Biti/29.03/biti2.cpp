// Testarea unui bit
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

	// Test Bit
	int i = 3;
	
	if (msk & (1 << i))
		cout << "bitul " << i << " este setat (este 1)";
	else
		cout << "bitul " << i << " NU este setat (este 0)";
	

}
