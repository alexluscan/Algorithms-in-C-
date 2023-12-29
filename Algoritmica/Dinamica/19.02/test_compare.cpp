#include <bits/stdc++.h>

using namespace std;

template <class T>
struct Greater {
	
	bool operator () (T a, T b)
	{
		return a > b;
	}
};

template <class T>
struct Less {
	
	bool operator () (T a, T b)
	{
		return a < b;
	}
};


template <class T, class Compare = greater<T>>
struct A {
	T a;
	Compare comp;
	
	T get(const T& x, const T& y)
	{
		if (comp(x, y)) // compara x > y
			return x;
		return y;
	}
};

int main() 
{
	
//	Greater<int> comp; // comp = functor sau "Function Object"
	
//	if (comp(20, 10)) // if (20 > 10)
//		cout << 20 << " > " << 10;
		
	
	A<int> a {10};
	
	cout << a.get(10, 20) << '\n';
	
	A<int, less<int>> b {10};
	
	cout << b.get(10, 20);
	
	
}
