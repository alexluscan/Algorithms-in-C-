#include <iostream>
#include <cstring>
using namespace std;

int main()
{	
	char a[] = "Salut prieteni!"; 
	
	cout << a << '\n';
	
	int n = strlen(a); // O(Lung)
	for (int i = 0; i < n; ++i)
		cout << a[i];
	cout << '\n';
	
	for (int i = 0; a[i] != '\0'; ++i)
		cout << a[i];
	cout << '\n';
		
	for (int i = 0; a[i] != 0; ++i)
		cout << a[i];
	cout << '\n';
	
	// recomandabil
	for (int i = 0; a[i]; ++i)
		cout << a[i];
	cout << '\n';
	
	
	for (char* p = a; *p; ++p)
		cout << *p;      // *p = valoarea de la adresa din p
	
	return 0;
}
