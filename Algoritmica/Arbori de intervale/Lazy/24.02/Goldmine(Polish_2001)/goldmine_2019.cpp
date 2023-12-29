#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("KOP.IN");
ofstream fout("KOP.OUT");

#define mid ((x + y) / 2 - ( (x + y) % 2 && (x + y) < 0 ))
const int Inf = 0x3f3f3f3f;

struct Point{
	int x, y;
	
	bool operator < (const Point& p) const
	{
		return x < p.x || (x == p.x && y < p.y);
	}
};

class ST{
public:
	ST(int x, int y): x{x}, y{y},
		  vmax{0}, lazy{0},
		  left{nullptr}, right{nullptr}
	{
		if (x != y)
		{
			left = new ST(x, mid);
			right = new ST(mid + 1, y);
		}
	}
	
	void Update(int i, int j, int val)
	{
		UpdateLazy();
		
		if (x > j || y < i)
			return;
		
		if (i <= x && y <= j)
		{
			vmax += val;
			
			if (x != y)
			{
				left->lazy += val;
				right->lazy += val;
			}
			
			return;
		}
		
		left->Update(i, j, val);
		right->Update(i, j, val);
		
		vmax = max(left->vmax, right->vmax);
	}
	
	int GetMax()
	{
		UpdateLazy();
		
		return vmax;
	}
	
private:
	void UpdateLazy()
	{
		if (!lazy)
			return;
		
		vmax += lazy;
		if (x != y)
		{
			left->lazy += lazy;
			right->lazy += lazy;
		}
		
		lazy = 0;
	}

	int x, y;		// intervalul de care se ocupa nodul
	int vmax;		// valoarea maxima pe acest interval
	int lazy;
	ST *left, *right;
};

using VI = vector<int>;
using VP = vector<Point>;

int W, H;
int n;
VP a;

int ymin{Inf}, ymax{-Inf};			// arborele de intervale va lucra in intervalul [ymin; ymax]

void ReadData();
void Solve();

int main()
{
	ReadData();
	Solve();
	
	fin.close();
	fout.close();
	return 0;
}

void ReadData()
{
	fin >> W >> H;
	fin >> n;
	
	a = VP(n);
	for (int i = 0; i < n; ++i)
	{
		fin >> a[i].x >> a[i].y;
		
		ymin = min(ymin, a[i].y);
		ymax = max(ymax, a[i].y);
	}
	
	sort(a.begin(), a.end());
	
	ymin -= H;
}

void Solve()
{
	ST st(ymin, ymax);
	int ans{0};
	
	for (int i = 0, j = 0; i < n;)
	{
		for (; i < n && a[i].x - a[j].x <= W; ++i)
			st.Update(a[i].y - H, a[i].y, +1);
		
		ans = max(ans, st.GetMax());
		
		for (; j < i && a[i].x - a[j].x > W; ++j)
			st.Update(a[j].y - H, a[j].y, -1);
	}
	
	fout << ans << '\n';
}
