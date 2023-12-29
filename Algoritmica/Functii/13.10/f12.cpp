#include <fstream>
#include <iostream>
using namespace std;

void ReadArray(int a[1000], int& n);
void WriteArray(int a[1000], int n);

int main()
{
	int a[1000], n;
	cout << a;
	ReadArray(, n);
	WriteArray(a, n);
	
	return 0;
}

void ReadArray(int a[1000], int& n)
{
	ifstream fin("sir.in");
	fin >> n;
	for (int i = 0; i < n; ++i)
		fin >> a[i];
}

void WriteArray(int a[1000], int n)
{
	ofstream fout("sir.out");
	for (int i = 0; i < n; ++i)
		fout << a[i] << ' ';
}
