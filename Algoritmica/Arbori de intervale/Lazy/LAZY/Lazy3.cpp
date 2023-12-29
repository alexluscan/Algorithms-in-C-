// Program to show segment tree to demonstrate lazy 
// propagation 
#include <stdio.h> 
#include <math.h> 
#define MAX 1000 
  
// Ideally, we should not use global variables and large 
// constant-sized arrays, we have done it here for simplicity. 
int tree[MAX] = {0};  // To store segment tree 
int lazy[MAX] = {0};  // To store pending updates 
  
/*  x -> index of current node in segment tree 
    l and r -> Starting and ending indexes of elements for 
                 which current nodes stores sum. 
    L and R -> starting and ending indexes of update query 
    diff -> which we need to add in the range L to ue */
void updateRangeUtil(int x, int l, int r, int L, 
                     int R, int diff) 
{ 
    // If lazy value is non-zero for current node of segment 
    // tree, then there are some pending updates. So we need 
    // to make sure that the pending updates are done before 
    // making new updates. Because this value may be used by 
    // parent after recursive calls (See last line of this 
    // function) 
    if (lazy[x] != 0) 
    { 
        // Make pending updates using value stored in lazy 
        // nodes 
        tree[x] += (r-l+1)*lazy[x]; 
  
        // checking if it is not leaf node because if 
        // it is leaf node then we cannot go further 
        if (l != r) 
        { 
            // We can postpone updating children we don't 
            // need their new values now. 
            // Since we are not yet updating children of x, 
            // we need to set lazy flags for the children 
            lazy[x*2 + 1]   += lazy[x]; 
            lazy[x*2 + 2]   += lazy[x]; 
        } 
  
        // Set the lazy value for current node as 0 as it 
        // has been updated 
        lazy[x] = 0; 
    } 
  
    // out of range 
    if (l > r || l > R || r < L) 
        return ; 
  
    // Current segment is fully in range 
    if (l >= L && r <= R) 
    { 
        // Add the difference to current node 
        tree[x] += (r - l + 1) * diff; 
  
        // same logic for checking leaf node or not 
        if (l != r) 
        { 
            // This is where we store values in lazy nodes, 
            // rather than updating the segment tree itelf 
            // Since we don't need these updated values now 
            // we postpone updates by storing values in lazy[] 
            lazy[x*2 + 1]   += diff; 
            lazy[x*2 + 2]   += diff; 
        } 
        return; 
    } 
  
    // If not completely in range, but overlaps, recur for children, 
    int mid = (l+r)/2; 
    updateRangeUtil(x*2 + 1, l, mid, L, R, diff); 
    updateRangeUtil(x*2 + 2, mid+1, r, L, R, diff); 
  
    // And Le the result of children calls to update this 
    // node 
    tree[x] = tree[x*2 + 1] + tree[x*2 + 2]; 
} 
  
// Function to update a range of values in segment 
// tree 
/*  L and eu -> starting and ending indexes of update query 
    ue  -> ending index of update query 
    diff -> which we need to add in the range L to R */
void updateRange(int n, int L, int R, int diff) 
{ 
   updateRangeUtil(0, 0, n - 1, L, R, diff); 
} 
  
  
/*  A recursive function to get the sum of values in given 
    range of the array. The following are parameters for 
    this function. 
    x --> Index of current node in the segment tree. 
           Initially 0 is paled as root is always at' 
           index 0 
    l & r  --> Starting and ending indexes of the 
                 segment represented by current node, 
                 i.e., tree[x] 
    qs & qe  --> Starting and ending indexes of query 
                 range */
int getSumUtil(int l, int r, int qs, int qe, int x) 
{ 
    // If lazy flag is set for current node of segment tree, 
    // then there are some pending updates. So we need to 
    // make sure that the pending updates are done before 
    // processing the sub sum query 
    if (lazy[x] != 0) 
    { 
        // Make pending updates to this node. Note that this 
        // node represents sum of elements in arr[l..r] and 
        // all these elements must be increased by lazy[x] 
        tree[x] += (r-l+1)*lazy[x]; 
  
        // checking if it is not leaf node because if 
        // it is leaf node then we cannot go further 
        if (l != r) 
        { 
            // Since we are not yet updating children os x, 
            // we need to set lazy values for the children 
            lazy[x*2+1] += lazy[x]; 
            lazy[x*2+2] += lazy[x]; 
        } 
  
        // unset the lazy value for current node as it has 
        // been updated 
        lazy[x] = 0; 
    } 
  
    // Out of range 
    if (l>r || l>qe || r<qs) 
        return 0; 
  
    // At this point we are sure that pending lazy updates 
    // are done for current node. So we can return value  
    // (same as it was for query in our previous post) 
  
    // If this segment lies in range 
    if ( l >= qs && r <= qe) 
        return tree[x]; 
  
    // If a part of this segment overlaps with the given 
    // range 
    int mid = (l + r)/2; 
    return getSumUtil(l, mid, qs, qe, 2*x+1) + 
           getSumUtil(mid+1, r, qs, qe, 2*x+2); 
} 
  
// Return sum of elements in range from index qs (query 
// start) to qe (query end).  It mainly uses getSumUtil() 
int getSum(int n, int qs, int qe) 
{ 
    // Check for erroneous input values 
    if (qs < 0 || qe > n-1 || qs > qe) 
    { 
        printf("Invalid Input"); 
        return -1; 
    } 
  
    return getSumUtil(0, n-1, qs, qe, 0); 
} 
  
// A recursive function that constructs Segment Tree for 
//  array[l..r]. x is index of current node in segment 
// tree st. 
void constructSTUtil(int arr[], int l, int r, int x) 
{ 
    // out of range as l can never be greater than r 
    if (l > r) 
        return ; 
  
    // If there is one element in array, store it in 
    // current node of segment tree and return 
    if (l == r) 
    { 
        tree[x] = arr[l]; 
        return; 
    } 
  
    // If there are more than one elements, then recur 
    // for left and right subtrees and store the sum 
    // of values in this node 
    int mid = (l + r)/2; 
    constructSTUtil(arr, l, mid, x*2+1); 
    constructSTUtil(arr, mid+1, r, x*2+2); 
  
    tree[x] = tree[x*2 + 1] + tree[x*2 + 2]; 
} 
  
/* Function to construct segment tree from given array. 
   This function allocates memory for segment tree and 
   calls constructSTUtil() to fill the allocated memory */
void constructST(int arr[], int n) 
{ 
    // Fill the allocated memory st 
    constructSTUtil(arr, 0, n-1, 0); 
} 
  
  
// Driver program to test above functions 
int main() 
{ 
    int arr[] = {1, 3, 5, 7, 9, 11}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
  
    // Build segment tree from given array 
    constructST(arr, n); 
  
    // Print sum of values in array from index 1 to 3 
    printf("Sum of values in given range = %d\n", 
           getSum(n, 1, 3)); 
  
    // Add 10 to all nodes at indexes from 1 to 5. 
    updateRange(n, 1, 5, 10); 
  
    // Find sum after the value is updated 
    printf("Updated sum of values in given range = %d\n", 
            getSum( n, 1, 3)); 
  
    return 0; 
} 
