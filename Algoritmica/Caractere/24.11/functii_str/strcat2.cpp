#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[100] = "Vii pe la mine? ", b[100] = "Niciodata";
	
	strcat(a, b + 4); // concateneaza un sufix al lui b la sf lui a
	
	cout << a;
	return 0;
}
