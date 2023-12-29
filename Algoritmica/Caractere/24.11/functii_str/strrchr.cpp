#include <iostream>
#include <cstring>
using namespace std;

// string reverse char

int main()
{	
	char a[] = "Niciodata";
	
	cout << strrchr(a, 'i'); // returneaza adresa ultimei aparitii a caracterului 'i'
                             // in sirul de bytes indicat de pointerul a   
	return 0;
}
