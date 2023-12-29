/* Mecanisme de Apelare (de Transfer) a functiilor in C++ :
 * 1. Apel "Prin Valoare" 
 * 2  Apel "Prin Referinta"
 *	 
 */ 
#include <iostream>
using namespace std;

void Read(int x);
void Write(int x);

int main()
{	
	int x = 123456;
	// Gresit! - argumentul e protejat
	Read(x);  // Apel prin valoare  
	Write(x); // Apel Prin Valoare
	
	return 0;
}

void Read(int x)
{
	cin >> x;
}

void Write(int x)
{
	cout << x;
}

