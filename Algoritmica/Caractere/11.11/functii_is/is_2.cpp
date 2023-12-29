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
		if (a[i] >= 'A' && a[i] <= 'Z')
			a[i] += 32;  // a[i] += 'a' - 'A'
		else
		if (a[i] >= 'a' && a[i] <= 'z')
			a[i] -= 32; // a[i] -= 'a' - 'A'
		
	
		fout << a[i];
	}
	
	return 0;
}
