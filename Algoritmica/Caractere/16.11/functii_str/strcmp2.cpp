#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[] = "Maria", b[] = "AnaMaria";
	int x = strcmp(a, b + 3);
	if (x > 0)
		cout << a << " > " << b;
	else
		if (x < 0)
			cout << a << " < " << b;
		else
			cout << a << " == " << b;
	
	return 0;
}
