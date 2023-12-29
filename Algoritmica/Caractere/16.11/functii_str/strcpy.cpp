#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[100] = "Ion", b[100] = "AnaMaria";
	
	cout << strcpy(a, b) << '\b';
	
	cout << a;
	return 0;
}
