/* Mecanisme de Apelare (de Transfer) a functiilor in C++ :
 * 1. Apel "Prin Valoare" 
 * 2  Apel "Prin Referinta"
 *	 
 */ 
#include <iostream>
using namespace std;

// & - Operator referinta
void Read(int& y);  // y = Parametru "Tip Referinta" sau "De Iesire"
void Write(int x);  // x = Parametru "Tip Valoare" sau "De Intrare"

int main()
{	
	int x = 123456;
	
	Read(x);  // Apel Prin Referinta  
	Write(x); // Apel Prin Valoare
	
	return 0;
}

// Functia Read nu-si creaza o alta variabila, ci un alt nume (o referinta) pentru argumentul x
void Read(int& y) // y este "O Referinta" la argumentul x
{                 // y este "Un Alias" (Alt Nume) pentru x 
	cin >> y;
}

void Write(int x)
{
	cout << x;
}

