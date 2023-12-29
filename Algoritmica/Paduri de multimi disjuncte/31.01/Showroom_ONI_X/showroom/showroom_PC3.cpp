//Code by Patcas Csaba
//Time complexity: O(nrCars * log(nrCars) + nrCompanies * maxCarsInACompany ^ 2)
//Space complexity: O(nrCars + maxCarsInACompany)
//Method: Disjoint sets + Pascal triangle with two lines
//Implementation time: 1 h 30 min

#include <vector>
#include <string> 
#include <set> 
#include <map> 
#include <queue> 
#include <bitset> 
#include <stack>
#include <list>

#include <numeric> 
#include <algorithm> 

#include <cstdio>
#include <fstream>
#include <iostream> 
#include <sstream> 
#include <iomanip>

#include <cctype>
#include <cmath> 
#include <ctime>
#include <cassert>

using namespace std;

#define LL long long
#define PII pair <int, int>
#define VB vector <bool>
#define VI vector <int>
#define VD vector <double>
#define VS vector <string>
#define VPII vector <pair <int, int> >
#define VVI vector < VI >
#define VVB vector < VB >

#define FORN(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)
#define FORI(it, X) for(__typeof((X).begin()) it = (X).begin(); it !=(X).end(); ++it) 
#define REPEAT do{ 
#define UNTIL(x) }while(!(x)); 

#define SZ size()
#define BG begin() 
#define EN end() 
#define CL clear()
#define X first
#define Y second
#define RS resize
#define PB push_back
#define MP make_pair
#define ALL(x) x.begin(), x.end()

#define IN_FILE "showroom.in"
#define OUT_FILE "showroom.out" 

#define BASE 9001

ifstream fin(IN_FILE);
ofstream fout(OUT_FILE);

VVI lines, c;
int n, a, r, k, nrIDs;
map <string, int> id;
VI father, treeSize, companySizes;

void read()
{
	nrIDs = 0;
	fin >> n >> a >> r >> k;
	lines.RS(n + 1);
	FOR(i, 0, n)
	{
		string s;
		getline(fin, s);

		stringstream ss(s);
		string model;
		while (ss >> model)
		{
			if (!id.count(model))
			{
				++nrIDs;
				id[model] = nrIDs;
			}
			lines[i].PB(id[model]);
		}
	}
	fin.close();

}

int getRoot(int node)
{
	if (father[node] == 0) return node;
	return father[node] = getRoot(father[node]);
}

void unite(int node1, int node2)
{
	node1 = getRoot(node1);
	node2 = getRoot(node2);
	if (node1 == node2) return;
	if (treeSize[node1] > treeSize[node2])
	{
		father[node1] = node2;
		treeSize[node2] += treeSize[node1];
	}
	else
	{
		father[node2] = node1;
		treeSize[node1] += treeSize[node2];
	}
}

void getCompanies()
{
	father.RS(nrIDs + n + 1);
	treeSize.RS(nrIDs + n + 1);
	FOR(i, 1, n)
	{
		int thisRoot = nrIDs + i;
		FORN(j, lines[i].SZ)
		{
			if (father[lines[i][j]] == 0) 
			{
				father[lines[i][j]] = thisRoot;
				++treeSize[thisRoot];
			}
			else
			{
				unite(thisRoot, lines[i][j]);
				thisRoot = getRoot(thisRoot);
			}
		}
	}

	set <int> usedRoots;
	FOR(i, 1, n)
	{
		int root = getRoot(lines[i][0]);
		if (!usedRoots.count(root))
		{
			companySizes.PB(treeSize[root]);
			usedRoots.insert(root);
		}
	}
}

int getPascalTriangle(int line, int column)
{
	c.RS(2);
	int actualLine = 0;
	FOR(i, 1, line)
	{
		actualLine = 1 - actualLine;
		c[actualLine].RS(i + 1);
		c[actualLine][0] = 1;
		c[actualLine][i] = 1;
		FOR(j, 1, i - 1) c[actualLine][j] = (c[1 - actualLine][j - 1] + c[1 - actualLine][j]) % BASE;
	}
	return c[actualLine][column];
}

int solve()
{
	int solution = 1, f = a;
	FORN(i, companySizes.SZ)
	{
		if (f <= companySizes[i]) solution = (solution * getPascalTriangle(companySizes[i],f)) % BASE;
		f = (f + r) % k;
	}
	return solution;
}

int main()
{
	read();
	
	//Solve
	getCompanies();

	//Write data
	fout << companySizes.SZ << endl;
	fout << solve();
	fout.close();

	return 0;
}