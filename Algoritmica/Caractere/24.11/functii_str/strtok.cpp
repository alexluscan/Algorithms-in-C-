#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{	
	char a[1000];
	fin.getline(a, 1000, EOF);
	
	char sep[] = "?.,><';: \n!-";
	char* p = strtok(a, sep);
	
	while (p)
	{
		fout << p << '\n';
		p = strtok(0, sep);
	}
	
	fout << "\n\n";
	
	return 0;
}
