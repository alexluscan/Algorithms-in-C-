/* Mecanisme de Apelare (de Transfer) a functiilor in C++ :
 * 1. Apel "Prin Valoare"
 * 2. Apel "Prin Referinta";
 */ 
#include <iostream>
using namespace std;

// a, b - Parametri Formali ai functiei
int Suma(int a, int b); // PROTOTIPUL functiei Suma (Antet, Header, Declarare)

int main()
{	
	int x, y;
	cin >> x >> y;
	cout << Suma(x, y);  // Apelul "Prin Valoare"
	// Valorile din argumentele x si y se copiaza (transfera) in parametri a si b
	return 0;
}

int Suma(int a, int b) // DEFINITIA functiei
{
	return a + b;
}
