#include <iostream>
using namespace std;



int main()
{	
	int a = 20;
	int* p;     // declar un pointer la int
	
	p = &a;      // & - Operator Adresa
	
	cout << p << ' ' << *p;  // *p = valoarea de la adresa respectiva
	// * = Operator de Dereferire (de dereferentiere)
	return 0;
}
