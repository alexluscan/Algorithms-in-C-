// Citirea intregului fisier CARACTER cu CARACTER 
// TOATE caracterele
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{	
	char ch;
	
	while (true)
	{
		ch = fin.get();
		if (ch == EOF)
			break;
		fout << (char)toupper(ch);
	}
	
	return 0;
}
