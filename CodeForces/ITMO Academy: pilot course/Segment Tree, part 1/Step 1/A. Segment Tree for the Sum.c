#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll data;
} node;

void build_tree(node* tree, ll* data, ll rt, ll left, ll right) {
    if (left == right) {
        tree[rt].data = data[left];
        return;
    }
    ll mid = left + (right - left) / 2;
    
    build_tree(tree, data, 2 * rt, left, mid);
    build_tree(tree, data, 2 * rt + 1, mid + 1, right);
    
    tree[rt].data = tree[rt * 2].data + tree[rt * 2 + 1].data;
}

void update(node* tree, ll rt, ll left, ll right, ll i, ll v) {
    if (left == right) {
        tree[rt].data = v;
        return;
    }
    
    ll mid = left + (right - left) / 2;
    if (i <= mid) {
        update(tree, rt * 2, left, mid, i, v);
    } else {
        update(tree, rt * 2 + 1, mid + 1, right, i, v);
    }
    tree[rt].data = tree[rt * 2].data + tree[rt * 2 + 1].data;
}

ll query(node* tree, ll rt, ll left, ll right, ll ql, ll qr) {
    if (ql > right || qr < left) {
        return 0;
    }
    
    if (left >= ql && right <= qr) {
        return tree[rt].data;
    }
    
    ll mid = left + (right - left) / 2;
    
    ll l_c = query(tree, rt * 2, left, mid, ql, qr);
    ll r_c = query(tree, rt * 2 + 1, mid + 1, right, ql, qr);
    
    return l_c + r_c;
}


void setIO(const char* name) {
    if (name != NULL && name[0] != '\0') {
        char in_filename[256];
        char out_filename[256];
        sprintf(in_filename, "%s.in", name);
        sprintf(out_filename, "%s.out", name);
        
        freopen(in_filename, "r", stdin);
        freopen(out_filename, "w", stdout);
    }
}

int main() {
    setIO("");
    
    ll n, m;
    scanf("%lld %lld", &n, &m);
    
    ll* arr = (ll*)malloc((n + 1) * sizeof(ll));
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    
    node* tree = (node*)calloc(n * 4 + 10, sizeof(node));
    build_tree(tree, arr, 1, 1, n);
    
    for (int j = 0; j < m; j++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            ll i, v;
            scanf("%lld %lld", &i, &v);
            update(tree, 1, 1, n, i + 1, v);
        } else {
            ll l, r;
            scanf("%lld %lld", &l, &r);
            printf("%lld\n", query(tree, 1, 1, n, l + 1, r));
        }
    }
    
    free(tree);
    free(arr);
    return 0;
}
