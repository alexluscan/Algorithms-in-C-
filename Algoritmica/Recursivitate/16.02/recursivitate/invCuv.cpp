#include <iostream>
using namespace std;

void Inv()
{
	char ch = cin.get();
	if (ch == '\n')
		return;
	Inv();
	cout << ch;
}


int main()
{
	Inv();
    return 0;
}
