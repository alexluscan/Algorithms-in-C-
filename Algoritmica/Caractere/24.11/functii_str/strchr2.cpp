#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[] = "Niciodata";
	
	if (strchr(a, 'x') != 0)
		cout << "gasit";
	else
		cout << "nu exista";

	return 0;
}
