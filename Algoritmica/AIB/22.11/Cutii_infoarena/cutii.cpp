#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
 
ifstream fin("cutii.in");
ofstream fout("cutii.out");
 
struct Cutie {
    int x, y, z;
    Cutie(int _x = 0, int _y = 0, int _z = 0) 
        : x(_x), y(_y), z(_z)
    { }
    bool operator < (const Cutie &c) const 
    {
        return z < c.z;
    }
};
 
const int MAX_N = 3500;
int aib[MAX_N + 10][MAX_N + 10];  // aib[x][y] - nr max de cutii cu _x < x si _y < y 
 
void Update(int cx, int cy, int val) 
{
    for (int x = cx; x <= MAX_N; x += x & -x) 
		for (int y = cy; y <= MAX_N; y += y & -y) 
            aib[x][y] = max(aib[x][y], val);
}
 
int Query(int cx, int cy) 
{
    int ans = 0;
    for (int x = cx; x > 0; x -= x & -x) 
        for (int y = cy; y > 0; y -= y & -y) 
            ans = max(ans, aib[x][y]);
    return ans;
}
 
void Reset(int cx, int cy) 
{
    for (int x = cx; x <= MAX_N; x += x & -x) 
        for (int y = cy; y <= MAX_N; y += y & -y) 
            aib[x][y] = 0;
}
 
int Solve(int n) 
{
    vector<Cutie> C;
    int x, y, z;
 
    for (int i = 1; i <= n; i++) 
    {
        fin >> x >> y >> z;
        C.push_back(Cutie(x, y, z));
    }
    sort(C.begin(), C.end());
     
    int ans = 0;
    for (const auto& c : C) 
    {
        int d = Query(c.x - 1, c.y - 1) + 1;
        Update(c.x, c.y, d);
        ans = max(ans, d);
    }
     
    for (const auto& c : C) 
        Reset(c.x, c.y);
 
    return ans;
}
 
int main() 
{
    int n, t;
    fin >> n >> t; 
     
    for(int i = 1; i <= t; i++) 
        fout << Solve(n) << '\n';

    return 0;
}
