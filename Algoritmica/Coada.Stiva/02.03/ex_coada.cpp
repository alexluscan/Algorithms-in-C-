#include <iostream>
#include <queue>
using namespace std;

int main()
{
	queue<int> Q;      // declar o coada vida
	
	Q.push(10);
	Q.push(20);
	Q.push(30);
	
	while (!Q.empty()) // cat timp coada nu e vida
	{
		cout << Q.front() << ' ';
		Q.pop();
		
	}
	
}
