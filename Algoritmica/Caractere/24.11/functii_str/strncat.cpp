#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[100] = "Vii pe la mine? ", b[100] = "Niciodata";
	
	strncat(a, b + 4, 3); // concateneaza o secventa a lui b la sf lui a
	
	cout << a;
	return 0;
}
