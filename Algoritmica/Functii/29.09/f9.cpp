/* Mecanisme de Apelare (de Transfer) a functiilor in C++ :
 * 1. Apel "Prin Valoare" 
 * 2  Apel "Prin Referinta"
 *	 
 */ 
#include <iostream>
using namespace std;

void Swap(int& x, int& y);

int main()
{	
	int x, y;
	cin >> x >> y; // 2 7
	Swap(x, y);   // DA! Apel prin Referinta
	
	cout << x << ' ' << y; // 2 7
	
	return 0;
}

void Swap(int& x, int& y)
{
	int aux;
	aux = x;
	x = y;
	y = aux;
}
