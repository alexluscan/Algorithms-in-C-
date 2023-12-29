#include <iostream>
using namespace std;

// a, b - Parametri Formali ai functiei
int Suma(int a, int b); // PROTOTIPUL functiei Suma (Antet, Header, Declarare)

int main()
{	
	int x, y;
	cin >> x >> y;
	
	// x, y = ARGUMENTELE functiei (Parametri Efectivi, Parametri Actuali, Param. de Apel)
	cout << Suma(x, y);  // Apelul functiei
	return 0;
}

int Suma(int a, int b) // DEFINITIA functiei
{
	return a + b;
}
