#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[] = "365260";
	
	int x = atoi(a);
	
	cout << x << ' ' << x / 2 << '\n';
	
	
	int y = 0;
	
	for (int i = 0; a[i]; ++i)
		y = y * 10 + a[i] - '0';
		
	cout << y;
	return 0;
}
