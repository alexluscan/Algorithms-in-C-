#include <cstdio>
using namespace std;
int const MAXN = 100000 + 5;
 
struct node {
    int st;
    int en;
    int mid;
    long long value;
};
 
node tree[4 * MAXN];
long long lazy[4 * MAXN];
 
void init_tree(int index, int left, int right) {
 
    tree[index].st = left, tree[index].en = right;
    tree[index].mid = (tree[index].st + tree[index].en) >> 1;
 
    if (tree[index].st != tree[index].en) {
        init_tree(2 * index, left, tree[index].mid);
        init_tree(2 * index + 1, tree[index].mid + 1, right);
    }
 
    tree[index].value = lazy[index] = 0;
}
 
long long getValue(int index) {
    return tree[index].value + (lazy[index] * (long long) (tree[index].en - tree[index].st + 1));
}
 
void refresh(int index) {
    lazy[2 * index] += lazy[index];
    lazy[2 * index + 1] += lazy[index];
    lazy[index] = 0;
}
 
void update(int index, int left, int right, int value) {
 
    if (tree[index].st >= left && tree[index].en <= right) {
        lazy[index] += value;
        return;
    }
    if (tree[index].st > right || tree[index].en < left)
        return;
    if (tree[index].st < left || tree[index].en > right) {
        refresh(index);
        update(2 * index, left, right, value);
        update(2 * index + 1, left, right, value);
        tree[index].value = getValue(2 * index) + getValue(2 * index + 1);
    }
}
 
long long query(int index, int left, int right) {
    if (tree[index].st >= left && tree[index].en <= right)
        return getValue(index);
    if (tree[index].st > right || tree[index].en < left)
        return 0;
    long long result = 0;
    if (tree[index].st < left || tree[index].en > right) {
        refresh(index);
        result = query(2 * index, left, right) + query(2 * index + 1, left, right);
        tree[index].value = getValue(2 * index) + getValue(2 * index + 1);
    }
    return result;
}
 
 
int main(int argc, char **args) {
    int T, p, q, v;
    scanf("%d", &T);
    while (T-- > 0) {
        int n,c;
        scanf("%d", &n);
        scanf("%d", &c);
        init_tree(1, 0, n - 1);
        for (int i = 0; i < c; i++) {
            scanf("%d", &n);
            if (n == 0) {
                scanf("%d%d%d", &p, &q, &v);
                update(1, p - 1, q - 1, v);
            } else {
                scanf("%d%d", &p, &q);
                printf("%lld\n", query(1, p - 1, q - 1));
            }
        }
    }
    return 0;
}
