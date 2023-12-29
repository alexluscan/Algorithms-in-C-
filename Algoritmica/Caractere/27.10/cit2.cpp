// Citirea intregului fisier LINIE cu LINIE
#include <fstream>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{	
	char L[500];
	
	while (fin.getline(L, 500))
	{
		fout << L << "\n\n";
	}
	
	return 0;
}
