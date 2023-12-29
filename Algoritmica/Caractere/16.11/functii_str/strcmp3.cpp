#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[200] = "Mariana", b[200] = "AnaMaria";
	int x = strncmp(a + 1, b + 4, 3);
	if (x > 0)
		cout << a << " > " << b;
	else
		if (x < 0)
			cout << a << " < " << b;
		else
			cout << a << " == " << b;
	
	return 0;
}
