/* Mecanisme de Apelare (de Transfer) a functiilor in C++ :
 * 1. Apel "Prin Valoare" 
 *	 Exemplu
 */ 
#include <iostream>
using namespace std;

int SumaCifrelor(int a);

int main()
{	
	int x, y;
	cin >> x >> y;
	
	cout << SumaCifrelor(x) << '\n';
	cout << SumaCifrelor(x * y) << '\n';
	cout << SumaCifrelor(2 * x + y) << '\n';
	cout << SumaCifrelor(10000) << '\n';
		 
	// Argumentul functiei (la Apelul prin Valoare) poate fi:
	//- o variabila
	// o constanta
	// o expresie
	return 0;
}

int SumaCifrelor(int x)
{
	int sc = 0;
	while (x)
	{
		sc += x % 10;
		x /= 10;
	}
	
	return sc;
}
