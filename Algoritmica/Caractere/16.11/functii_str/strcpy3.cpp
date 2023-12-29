#include <iostream>
#include <cstring>
using namespace std;


int main()
{	
	char a[100] = "Vii pe la mine?", b[100] = "Niciodata";
	
	strcpy(a + 4, "mai baiatule ?");
	
	cout << a;
	return 0;
}
