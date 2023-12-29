// C++ program to showLazy propagation in Segment Tree - Sum of range
#include<bits/stdc++.h>
using namespace std;

#define MAX 100010
int tree[MAX], lazy[MAX];
vector<int> ar;

/* Function to display elements of the Segment Tree and
   the Lazy tree level by level. */
void showSegTree(int n)
{
	int h = ceil(log2(n));
	cout << "Segment Tree:" << endl;
	for(int i = 0; i <= h; ++i)
	{
		for (int j = 0; j < pow(2, i); ++j)
			cout << tree[int(pow(2, i)-1 + j)] << ' ';
		cout << endl;
	}
	
	cout << "Lazy Tree:" << endl;
	for (int i = 0; i <= h; ++i)
	{
		for (int j = 0; j < pow(2, i); ++j)
			cout << lazy[int(pow(2, i) - 1 + j)] << ' ';
		cout << endl;
	}
}

/* Function to construct the Segment Tree recursively.
   At each node, if it is not the leaf, two children are
   processed further. Otherwise, the leaf is assigned an
   array alement. strt and end are range in the array,
   idx is the index used in the segment tree */
int BuildST(int strt, int end, int idx)
{
	// Initialize all lazy tree nodes with 0
	lazy[idx] = 0;
	// Saves tree[idx] = ar[strt] and then returns tree[idx]
	if (strt == end)
		return tree[idx] = ar[strt];
		
	int mid = (strt + end) / 2;
	return tree[idx] = BuildST(strt, mid, 2*idx+1) +
			BuildST(mid+1, end, 2*idx+2);
}
void BuildST(int n)
{
	BuildST(0, n - 1, 0);
}

/* Function to get the sum of elements of array in the
   range [strt..end]. l & r are the range of current node.
   indx is the index of node in segment tree */
int QuerySum(int strt, int end, int l, int r, int idx)
{
	// If there's pending update, update the node first
	if(lazy[idx] != 0)
	{
		// Add the pending update to the current node
		// [l..r] contains l-r+1 nodes
		tree[idx] += (r-l+1) * lazy[idx];

		// If the node has children, postpone the updates
		// to the children by adding to the their lazy nodes
		if (l != r)
		{
		  lazy[2*idx+1] += lazy[idx];
		  lazy[2*idx+2] += lazy[idx];
		}
		// Reset the lazy node of current node
		lazy[idx] = 0;
	}
	// If completly outside the range, don't care
	if(end < l || r < strt || l > r)
	return 0;

	// If node is entirely within the range, return the node value
	if(strt <= l && r <= end)
	return tree[idx];

	// Enter its children and process further
	int mid = (l + r) / 2;
	return QuerySum(strt, end, l, mid, 2*idx+1) +
	  QuerySum(strt, end, mid+1, r, 2*idx+2);
}

int QuerySum(int n, int strt, int end)
{
  return QuerySum(strt, end, 0, n-1, 0);
}

/* Function to update a particular node of the array in
   Segment Tree. pos is the desired index in the array.
   val is the value to be added */
void Update(int strt, int end, int val, int l, int r, int idx)
{
	// If there's pending update, update the node first
	if(lazy[idx] != 0)
	{
		// Add the pending update to the current node
		// [l..r] contains l-r+1 nodes
		tree[idx] += (r-l+1)*lazy[idx];
		// If the node has children, postpone the updates
		// to the children by adding to the their lazy nodes
		if(l != r)
		{
			  lazy[2*idx+1] += lazy[idx];
			  lazy[2*idx+2] += lazy[idx];
		}
		// Reset the lazy node of current node
		lazy[idx] = 0;
	}
	// If completly outside the range, don't care
	if (end < l || r < strt || l > r)
		return;
	// If node is entirely within the range
	if (strt <= l && r <= end)
	{
		// Update the current node in Segment tree
		tree[idx] += (r - l + 1) * val;
		// If the node has children, postpone the updates
		// of the children by adding to the their lazy nodes
		if (l != r)
		{
		  lazy[2*idx+1] += val;
		  lazy[2*idx+2] += val;
		}
	}
	else
	{
		// Enter its children and process further
		int mid = (l + r) / 2;
		Update(strt, end, val, l, mid, 2*idx+1);
		Update(strt, end, val, mid+1, r, 2*idx+2);
		// Recalculate the itermediate nodes after updation
		tree[idx] = tree[2*idx + 1] + tree[2*idx + 2];  
	}
}

void Update(int n, int strt, int end, int val)
{
	Update(strt, end, val, 0, n-1, 0);
}


int main()
{
	int n = 7;
	ar = {18, 17, 1, 19, 15, 11, 20};
	BuildST(n);
	cout << "n = 7, ar = {18, 17, 1, 19, 15, 11, 20}"<<endl;
	showSegTree(n);

	Update(n, 0, 4, 2);

	cout << "\nUpdate(n, 0, 4, 2):"<<endl;
	showSegTree(n);
	cout << "\nSum of ar[1..4] = " << QuerySum(n, 1, 4)<<endl;
	showSegTree(n);

	return 0;
}
