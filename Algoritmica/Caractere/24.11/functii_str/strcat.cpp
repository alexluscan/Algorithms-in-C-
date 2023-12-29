#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[100] = "Vii pe la mine?", b[100] = "Niciodata";
	
	strcat(a, b); // concateneaza (adauga) la sf lui a pe b
	
	cout << a;
	return 0;
}
