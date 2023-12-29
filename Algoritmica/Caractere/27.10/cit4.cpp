// Citirea intregului fisier CARACTER cu CARACTER 
// NUMAI carcaterel grafice (vizibile)
#include <fstream>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{	
	char ch;
	
	while (fin >> ch)
	{
		fout << ch;
	}
	
	return 0;
}
