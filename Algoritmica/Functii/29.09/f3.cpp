/* Mecanisme de Apelare (de Transfer) a functiilor in C++ :
 * 1. Apel "Prin Valoare" 
 *	 Exemplu
 */ 
#include <iostream>
using namespace std;

int SumaCifrelor(int a);

int main()
{	
	int x;
	cin >> x;
	
	cout << SumaCifrelor(x) << '\n'
		 << x;
		 
	// Apelul Prin Valoare are meritul ca PROTEJEAZA ARGUMENTUL
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
