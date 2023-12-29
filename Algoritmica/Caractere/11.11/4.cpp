#include <iostream>
using namespace std;

int main()
{	
	char b[100];
	
	cin.getline(b, 100, '?'); // Extrage pana la caracterul delimitator '?' 
	cout << b;                // Carcaterul delimitator nu va fi plasat in buffer, 
	                          // dar va fi extras din stream 
	return 0;
}
