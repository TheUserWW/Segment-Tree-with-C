#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef long long ll;
 
typedef struct {
    ll data;
} node;
 
void build(node* tree, ll* data, ll rt, ll l, ll r) {
    if (l == r) {
        tree[rt].data = data[l];
        return;
    }
    const ll mid = l + (r - l) / 2;
    build(tree, data, rt * 2, l, mid);
    build(tree, data, rt * 2 + 1, mid + 1, r);
    
    tree[rt].data = tree[rt * 2].data ^ tree[rt * 2 + 1].data;
}
 
void update(node* tree, ll rt, ll l, ll r, ll idx, ll val) {
    if (l == r) {
        tree[rt].data = val;
        return;
    }
    
    ll mid = l + (r - l) / 2;
    if (idx <= mid) {
        update(tree, rt * 2, l, mid, idx, val);
    } else {
        update(tree, rt * 2 + 1, mid + 1, r, idx, val);
    }
    
    tree[rt].data = tree[rt * 2].data ^ tree[rt * 2 + 1].data;
}
 
ll query(node* tree, ll rt, ll l, ll r, ll ql, ll qr) {
    if (ql > r || qr < l) {
        return 0;
    }
    if (l >= ql && r <= qr) {
        return tree[rt].data;
    }
    const ll mid = l + (r - l) / 2;
    return query(tree, rt * 2, l, mid, ql, qr) ^ 
           query(tree, rt * 2 + 1, mid + 1, r, ql, qr);
}
 
int main() {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    
    ll* arr = (ll*)malloc(sizeof(ll) * (n + 1));
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    
    node* tree = (node*)calloc(4 * n + 10, sizeof(node));
    build(tree, arr, 1, 1, n);
    
    for (int i = 0; i < m; i++) {
        ll a, b;
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", query(tree, 1, 1, n, a, b));
    }
    
    free(arr);
    free(tree);
    return 0;
}
