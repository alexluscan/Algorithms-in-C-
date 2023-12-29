#include <iostream>
using namespace std;

int main()
{	
	// numele tablourilor retin adresa primului element al tabloului
	short a[] = {10, 20, 30, 40};
	
	for (int i = 0; i < 3; ++i)
		cout << a + i << " ==> " << *(a + i) << '\n';
	
	// a[i] = *(a + i)
	return 0;
}
