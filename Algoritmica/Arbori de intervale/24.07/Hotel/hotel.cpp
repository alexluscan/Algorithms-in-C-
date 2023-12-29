#include <cstdio>
#include <fstream>
#include <algorithm>

using namespace std;

struct nod
{
	int left, right, tot;
};

int n, p;
nod ai[4 * 100000 + 1];

void set(int x, int st, int dr)
{
	if (st == dr)
	{
		ai[x].tot = ai[x].left = ai[x].right = 1;
		return;
	}
	
	int md = (st + dr) / 2;
	set(x * 2, st, md);
	set(x * 2 + 1, md + 1, dr);
	
	ai[x].tot = ai[x * 2].tot + ai[x * 2 + 1].tot;
	ai[x].left = ai[x * 2].left + ai[x * 2 + 1].left;
	ai[x].right = ai[x * 2].right + ai[x * 2 + 1].right;
}
void update(int x, int st, int dr, int l1, int l2, bool ch)
{
	if (l1 <= st && dr <= l2)
	{
		ai[x].tot = ai[x].left = ai[x].right = ch * (dr - st + 1);
		return;
	}
	
	int md = (st + dr) / 2;
	
	if (ai[x].tot == (dr - st + 1))
	{
		ai[x * 2].tot = ai[x * 2].left = ai[x * 2].right = (md - st + 1);
		ai[x * 2 + 1].tot = ai[x * 2 + 1].left = ai[x * 2 + 1].right = (dr - md);
	}
	else if (ai[x].tot == 0)
	{
		ai[x * 2].tot = ai[x * 2].left = ai[x * 2].right = 0;
		ai[x * 2 + 1].tot = ai[x * 2 + 1].left = ai[x * 2 + 1].right = 0;
	}
	
	if (l1 <= md) update(x * 2, st, md, l1, l2, ch);
	if (l2 > md) update(x * 2 + 1, md + 1, dr, l1, l2, ch);
	
	ai[x].tot = max(ai[x * 2].right + ai[x * 2 + 1].left, max(ai[x * 2].tot, ai[x * 2 + 1].tot));
	ai[x].left = ((ai[x * 2].left == (md - st + 1)) ? ai[x * 2].left + ai[x * 2 + 1].left : ai[x * 2].left);
	ai[x].right = ((ai[x * 2 + 1].right == (dr - md)) ? ai[x * 2 + 1].right + ai[x * 2].right : ai[x * 2 + 1].right);
}

int main()
{
	ifstream fin("hotel.in");
	ofstream fout("hotel.out");
	
	fin >> n >> p;
	set(1, 1, n);
	
	int c, l1, l2;
	while (p--)
	{
		fin >> c;
		switch (c)
		{
			case 1:
				fin >> l1 >> l2;
				l2 += l1 - 1;
				update(1, 1, n, l1, l2, 0); 
				break;
			case 2:
				fin >> l1 >> l2;
				l2 += l1 - 1;
				update(1, 1, n, l1, l2, 1);
				break;
			case 3:
				fout << ai[1].tot << '\n';
				break;
		}
	}
	
	fin.close();
	fout.close();
}
