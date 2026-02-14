#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long data;
} node;

void build_tree(long long* data, node* tree, long long rt, long long left, long long right) {
    if (left == right) {
        tree[rt].data = data[left];
        return;
    }
    const long long mid = left + (right - left) / 2;
    build_tree(data, tree, 2 * rt, left, mid);
    build_tree(data, tree, 2 * rt + 1, mid + 1, right);
    tree[rt].data = tree[2 * rt].data + tree[2 * rt + 1].data;
}

void update(node* tree, long long rt, long long left, long long right, long long idx, long long value) {
    if (left == right) {
        tree[rt].data = value;
        return;
    }
    const long long mid = left + (right - left) / 2;
    if (idx <= mid) {
        update(tree, 2 * rt, left, mid, idx, value);
    } else {
        update(tree, 2 * rt + 1, mid + 1, right, idx, value);
    }
    tree[rt].data = tree[2 * rt].data + tree[2 * rt + 1].data;
}

long long segment_sum(node* tree, long long rt, long long left, long long right, long long a, long long b) {
    if (a > right || b < left) {
        return 0;
    }
    if (left >= a && right <= b) {
        return tree[rt].data;
    }
    long long mid = left + (right - left) / 2;
    return segment_sum(tree, 2 * rt, left, mid, a, b) + 
           segment_sum(tree, 2 * rt + 1, mid + 1, right, a, b);
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    
    long long* arr = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }
    
    node* tree = (node*)malloc((4 * n + 10) * sizeof(node));
    build_tree(arr, tree, 1, 0, n - 1);
    
    for (int i = 0; i < q; i++) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            long long k, u;
            scanf("%lld %lld", &k, &u);
            update(tree, 1, 0, n - 1, k - 1, u);
        } else {
            long long a, b;
            scanf("%lld %lld", &a, &b);
            printf("%lld\n", segment_sum(tree, 1, 0, n - 1, a - 1, b - 1));
        }
    }
    
    free(arr);
    free(tree);
    
    return 0;
}
