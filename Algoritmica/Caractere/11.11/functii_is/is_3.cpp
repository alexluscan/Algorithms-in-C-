// Sa se tranf literele mari in mici si invers
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{	
	char a[10000];
	
	fin.getline(a, 10000, EOF);

	
	for (int i = 0; a[i]; i++)
	{
		if (isupper(a[i]))
			a[i] = tolower(a[i]);
		else
		if (islower(a[i]))
			a[i] = toupper(a[i]);
		
	
		fout << a[i];
	}
	
	return 0;
}
