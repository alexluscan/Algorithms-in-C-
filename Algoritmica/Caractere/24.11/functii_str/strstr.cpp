#include <iostream>
#include <cstring>
using namespace std;

int main()
{	
	char a[] = "Niciodataiod", b[] = "iod";
	
	cout << strstr(a, b); // returneaza adresa primei aparitii a sirului de bytes indicati de b
                          // in sirul de bytes indicat de pointerul a   
	return 0;
}
