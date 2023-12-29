/*Se citeste n, apoi numele a n copii.
 * Sa se afiseze copiii in ordine alfabetica
 */  
#include <fstream>
#include <string>
using namespace std;

ifstream fin("copii.in");
ofstream fout("copii.out");

char c[35][25];
int n;


int main()
{	
	// c[i] e pointer. El retine adrea liniei i
	
	
	// Adresa de inceput a matricei:
	fout << (void*) c << '\n'  
	     << (void*)c[1];
	return 0;
}
