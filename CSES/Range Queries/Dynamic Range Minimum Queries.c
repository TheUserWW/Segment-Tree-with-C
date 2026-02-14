#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long data;
} node;

void build(node* tree, long long* data, long long rt, long long l, long long r) {
    if (l == r) {
        tree[rt].data = data[l];
        return;
    }
    const long long mid = l + (r - l) / 2;
    build(tree, data, rt * 2, l, mid);
    build(tree, data, rt * 2 + 1, mid + 1, r);
    
    tree[rt].data = (tree[rt * 2].data < tree[rt * 2 + 1].data) ? 
                     tree[rt * 2].data : tree[rt * 2 + 1].data;
}

void update(node* tree, long long rt, long long l, long long r, long long idx, long long val) {
    if (l == r) {
        tree[rt].data = val;
        return;
    }
    
    long long mid = l + (r - l) / 2;
    if (idx <= mid) {
        update(tree, rt * 2, l, mid, idx, val);
    } else {
        update(tree, rt * 2 + 1, mid + 1, r, idx, val);
    }
    
    tree[rt].data = (tree[rt * 2].data < tree[rt * 2 + 1].data) ? 
                     tree[rt * 2].data : tree[rt * 2 + 1].data;
}

long long query(node* tree, long long rt, long long l, long long r, long long ql, long long qr) {
    if (ql > r || qr < l) {
        return LLONG_MAX;
    }
    if (l >= ql && r <= qr) {
        return tree[rt].data;
    }
    const long long mid = l + (r - l) / 2;
    long long left_min = query(tree, rt * 2, l, mid, ql, qr);
    long long right_min = query(tree, rt * 2 + 1, mid + 1, r, ql, qr);
    
    return (left_min < right_min) ? left_min : right_min;
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
            long long k, u;
            scanf("%lld %lld", &k, &u);
            update(tree, 1, 1, n, k, u);
        } else {
            long long a, b;
            scanf("%lld %lld", &a, &b);
            printf("%lld\n", query(tree, 1, 1, n, a, b));
        }
    }
    
    free(arr);
    free(tree);
    return 0;
}
