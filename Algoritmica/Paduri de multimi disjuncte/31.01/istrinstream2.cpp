#include <fstream>
#include <string>
#include <sstream>
using namespace std;

ifstream fin("text.in");
ofstream fout("text.out");

int main()
{
	int n;
	string nume;
	double media;
	char sex;
	string line;
	fin >> n;
	fin.get();
	istringstream is;ine(fin, line))
	{
		is.str(line);
		is >> nume >> media >> sex;
		
		fout << nume << ' ' << media << ' ' << sex << '\n';
		
		is.clear();
	}
}
