/* Sa se inverseze cuvintele unei fraze
 * 
 */ 
#include <iostream>
using namespace std;

void Inv(int n) // n = cate cuvinte mai sunt de citit
{
	if (n == 0)
		return;
		
	char cuv[20];
	cin >> cuv;
	Inv(n - 1);
	
	cout << cuv << ' ';
}

int main()
{
	int n;
	cin >> n;
	
	Inv(n);
}
