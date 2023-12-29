#include <iostream>
#include <cstring>
using namespace std;

int main()
{	
	char a[] = "Niciodataiod", b[] = "Iod";
	
	if (strstr(a, b) != 0)
		cout << "gasit";
	else
		cout << "nu exista";
	return 0;
}
