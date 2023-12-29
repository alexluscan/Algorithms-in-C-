#include <iostream>
#include <cstring>
using namespace std;

int SC(char s[]) 
{
	int n = strlen(s);
	if (n == 0)
		return 0;
	
	char u = s[n - 1];
	s[n - 1] = 0;
	if (u >= '0' && u <= '9')
		return u - '0' + SC(s);
	
	return SC(s);
}

int main()
{
	char s[] = "3sh3j58";
	cout << SC(s);
}
