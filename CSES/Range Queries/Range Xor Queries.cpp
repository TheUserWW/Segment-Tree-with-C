#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define i128 __int128
#define vl vector<i64>
#define vb vector<bool>
#define umap unordered_map
#define uset unordered_set
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(),v.rend()
#define write(v) for(int i = 0; i < v.size(); i++) cin >> v[i];
#define init(n) ll n; cin >> n;
#define printV(v) for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
#define printlnV(v) for(int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << "\n";
 
void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    if (!name.empty()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
 
struct node {
    ll data;
};
 
void build(node* tree, ll* data, ll rt, ll l, ll r) {
    if (l == r) {
        tree[rt].data = data[l];
        return;
    }
    const ll mid = l + ( r - l )/2;
    build(tree,data,rt*2,l,mid);
    build(tree,data,rt*2+1,mid+1,r);
 
    tree[rt].data = tree[rt*2].data ^ tree[rt*2+1].data;
}
 
void update(node* tree, ll rt, ll l, ll r, ll idx, ll val) {
    if (l == r) {
        tree[rt].data = val;
        return;
    }
 
    ll mid = l + (r - l)/2;
    if (idx <= mid) {
        update(tree,rt*2,l,mid,idx,val);
    }
    else {
        update(tree,rt*2+1,mid+1,r,idx,val);
    }
 
    tree[rt].data = min(tree[rt*2].data,tree[rt*2+1].data);
}
 
ll query(node* tree, ll rt, ll l, ll r, ll ql, ll qr) {
    if (ql > r || qr < l) {
        return 0;
    }
    if (l >= ql && r <= qr) {
        return tree[rt].data;
    }
    const ll mid = l + (r - l)/2;
    return query(tree,rt*2,l,mid,ql,qr) ^ query(tree,rt*2+1,mid+1,r,ql,qr);
}
 
 
int main() {
    setIO();
    ll n,m;
    cin >> n >> m;
    ll* arr = (ll*)malloc(sizeof(ll)*n+1);
    for (int i = 1; i <=n; i++) {
        cin >> arr[i];
    }
    node* tree = (node*)calloc(4*n+10,sizeof(node));
    build(tree,arr,1,1,n);
 
    for (int i = 0; i < m; i ++) {
            ll a,b;
            cin >> a >> b;
            cout<<query(tree,1,1,n,a,b)<<"\n";
 
    }
    free(arr);
    free(tree);
    return 0;
}
