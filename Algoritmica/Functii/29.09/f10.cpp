/* Mecanisme de Apelare (de Transfer) a functiilor in C++ :
 * 1. Apel "Prin Valoare" 
 * 2  Apel "Prin Referinta"
 *	 
 */ 
#include <iostream>
using namespace std;

int Cmmdc(int a, int b);
void Cmmdc(int a, int b, int& d);

int main()
{	
	int x, y;
	cin >> x >> y; 
//	cout << Cmmdc(x, y);   
	int cmmdc;
	Cmmdc(x, y, cmmdc);
	
	cout << cmmdc;
	
	return 0;
}

void Cmmdc(int a, int b, int& d)
{
	int rest;
	while (b)
	{
		rest = a % b;
		a = b;
		b = rest;
	}
	d = a;
}
// Alg lui Euclid
int Cmmdc(int a, int b)
{
	int rest;
	while (b)
	{
		rest = a % b;
		a = b;
		b = rest;
	}
	
	return a;
}
