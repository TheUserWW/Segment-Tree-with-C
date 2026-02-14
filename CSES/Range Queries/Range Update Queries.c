#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long data;
    long long lazy;
} node;

void build(node* tree, long long* data, long long rt, long long l, long long r) {
    if (l == r) {
        tree[rt].data = data[l];
        tree[rt].lazy = 0;
        return;
    }
    const long long mid = l + (r - l) / 2;
    build(tree, data, rt * 2, l, mid);
    build(tree, data, rt * 2 + 1, mid + 1, r);
    
    tree[rt].data = tree[rt * 2].data ^ tree[rt * 2 + 1].data;
    tree[rt].lazy = 0;
}

void push_down(node* tree, long long rt) {
    if (tree[rt].lazy != 0) {
        tree[rt * 2].data += tree[rt].lazy;
        tree[rt * 2].lazy += tree[rt].lazy;
        
        tree[rt * 2 + 1].data += tree[rt].lazy;
        tree[rt * 2 + 1].lazy += tree[rt].lazy;
        
        tree[rt].lazy = 0;
    }
}

void update_range(node* tree, long long rt, long long left, long long right, 
                  long long ul, long long ur, long long value) {
    if (ul > right || ur < left) {
        return;
    }
    if (ul <= left && ur >= right) {
        tree[rt].data += value;
        tree[rt].lazy += value;
        return;
    }
    push_down(tree, rt);
    long long mid = left + (right - left) / 2;
    update_range(tree, 2 * rt, left, mid, ul, ur, value);
    update_range(tree, 2 * rt + 1, mid + 1, right, ul, ur, value);
    tree[rt].data = (tree[2 * rt].data > tree[2 * rt + 1].data) ? 
                     tree[2 * rt].data : tree[2 * rt + 1].data;
}

long long query(node* tree, long long rt, long long l, long long r, long long k) {
    if (l == r) {
        return tree[rt].data;
    }
    const long long mid = l + (r - l) / 2;
    push_down(tree, rt);
    if (k <= mid) {
        return query(tree, rt * 2, l, mid, k);
    } else {
        return query(tree, rt * 2 + 1, mid + 1, r, k);
    }
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    
    long long* arr = (long long*)malloc(sizeof(long long) * (n + 1));
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    
    node* tree = (node*)calloc(4 * n + 10, sizeof(node));
    build(tree, arr, 1, 1, n);
    
    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            long long a, b, u;
            scanf("%lld %lld %lld", &a, &b, &u);
            update_range(tree, 1, 1, n, a, b, u);
        } else {
            long long k;
            scanf("%lld", &k);
            printf("%lld\n", query(tree, 1, 1, n, k));
        }
    }
    
    free(arr);
    free(tree);
    return 0;
}
