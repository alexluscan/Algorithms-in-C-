// OK
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

const int  MaxN = 10002,
		   MaxSeg = 4 * MaxN;

struct Segm {
    int x, y1, y2, sgn;
    bool operator < (const Segm& s) const
    {
		return x < s.x || (x == s.x && sgn < s.sgn); 
	}
};

Segm s[MaxSeg]; // cate 4 segmente la fiecare dreptunghi
int n, c;
long long sum[4 * MaxSeg], aria;
int nrs[4 * MaxSeg];

void Read();
void Sweep();
void Update(int, int, int, int, int, int);
void Write();

int main()
{
    Read();
    n = 2 * n;
    sort(s + 1, s + n + 1);
    Sweep();
	Write();
    return 0;
}    

void Read()
{
    ifstream fin("mar9.in");
    cin >> n;
    int xsj, ysj, xds, yds, k = 1;
    for (int i = 1; i <= n; ++i)
    {
        cin >> xsj >> ysj >> xds >> yds;
        s[k].x = xsj; s[k].y1 = ysj;  s[k].y2 = yds;  s[k++].sgn = -1;
        
        s[k].x = xds; s[k].y1 = ysj;  s[k].y2 = yds;  s[k++].sgn = 1;
    }
    fin.close();
}        

void Sweep()
{
    for (int i = 1; i <= n; ++i)
    {
        aria += sum[1] * (s[i].x - s[i - 1].x);
        Update(1, 0, 30001, s[i].y1, s[i].y2 - 1, s[i].sgn);    
    }
}

void Update(int i, int l, int r, int a, int b, int semn)
{
    if ( a <= l && b >= r)
    {
        nrs[i] += semn;
        if (nrs[i] > 0)
            sum[i] = r - l + 1;
        else sum[i] = sum[2*i] + sum[2*i + 1];
        return;
    }    
    int m = (l + r) / 2;
    if (a <= m)    
        Update(i*2, l, m, a, b, semn);
    if (b > m)
        Update(i*2 + 1, m + 1, r, a, b, semn);    
    
    sum[i] = 0;
    if (nrs[i] )
		sum[i] = r - l + 1;
	else
        if ( l < r )
			sum[i] = sum[i*2] + sum[2*i + 1];
}                        

void Write()
{
    ofstream fout("mars.out");
    cout << aria;
    fout.close();
}    
