#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[] = "Ana", b[] = "AnaMaria";
	int x = strcmp(a, b);
	if (x > 0)
		cout << a << " > " << b;
	else
		if (x < 0)
			cout << a << " < " << b;
		else
			cout << a << " == " << b;
	
	return 0;
}
