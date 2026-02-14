#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    long long data;
    long long count;
} node;

struct node merge(node left, node right) {
    if (left.data < right.data) {
        return left;
    }
    else if (left.data > right.data) {
        return right;
    }
    else {
        node result = {left.data, left.count + right.count};
        return result;
    }
}

void build_tree(node* tree, long long* data, long long rt, long long left, long long right) {
    if (left == right) {
        tree[rt].data = data[left];
        tree[rt].count = 1;
        return;
    }
    long long mid = left + (right - left)/2;

    build_tree(tree, data, 2*rt, left, mid);
    build_tree(tree, data, 2*rt+1, mid+1, right);

    tree[rt] = merge(tree[rt*2], tree[rt*2+1]);
}

void update(node* tree, long long rt, long long left, long long right, long long i, long long v) {
    if (left == right) {
        tree[rt].data = v;
        return;
    }

    long long mid = left + (right - left)/2;
    if (i <= mid) {
        update(tree, rt*2, left, mid, i, v);
    }
    else {
        update(tree, rt*2+1, mid+1, right, i, v);
    }
    tree[rt] = merge(tree[rt*2], tree[rt*2+1]);
}

node query(node* tree, long long rt, long long left, long long right, long long ql, long long qr) {
    if (ql > right || qr < left) {
        node result = {LLONG_MAX, 0};
        return result;
    }

    if (left >= ql && right <= qr) {
        return tree[rt];
    }

    long long mid = left + (right - left)/2;

    node l_c = query(tree, rt*2, left, mid, ql, qr);
    node r_c = query(tree, rt*2+1, mid+1, right, ql, qr);

    return merge(l_c, r_c);
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    
    long long* arr = (long long*)malloc((n + 1) * sizeof(long long));
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    
    node* tree = (node*)calloc(n * 4 + 10, sizeof(node));
    build_tree(tree, arr, 1, 1, n);

    for (int j = 0; j < m; j++) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            long long i, v;
            scanf("%lld %lld", &i, &v);
            update(tree, 1, 1, n, i+1, v);
        }
        else {
            long long l, r;
            scanf("%lld %lld", &l, &r);
            node ans = query(tree, 1, 1, n, l+1, r);
            printf("%lld %lld\n", ans.data, ans.count);
        }
    }

    free(tree);
    free(arr);
    return 0;
}
