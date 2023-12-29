#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[100] = "Vii pe la mine?", b[100] = "Niciodata";
	
	strcpy(a + 4, b + 4);
	
	cout << a;
	return 0;
}
