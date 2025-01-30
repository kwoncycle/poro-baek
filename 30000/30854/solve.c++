#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

struct SegTree{
    int n;
    vector<int> tree, v;
    int (*f)(int, int);
    int iv;
    SegTree(){}
    SegTree(int _n, vector<int> &_v, int (*_f)(int, int), int _iv): n(_n), v(_v), f(_f), iv(_iv){
        tree.resize(4*n+4);
        init(1, 0, n-1);
    }
    
    void init(int node, int s, int e){
        if(s == e){
            tree[node] = v[s];
            return;
        }
        init(node*2, s, (s+e)/2);
        init(node*2 + 1, (s+e)/2 + 1, e);
        tree[node] = f(tree[node*2], tree[node*2 + 1]);
    }

    int query(int l, int r){
        return query(1, 0, n-1, l, r);
    }
    int query(int node, int s, int e, int l, int r){
        if(e<l or r<s) return iv;
        if(l<=s and e<=r) return tree[node];
        int q1 = query(node*2, s, (s+e)/2, l, r);
        int q2 = query(node*2 + 1, (s+e)/2 + 1, e, l, r);
        return f(q1, q2);
    }

    void update(int i, int val){
        update(1, 0, n-1, i, val);
    }
    void update(int node, int s, int e, int i, int val){
        if(e<i or i<s) return;
        if(i<=s and e<=i){
            tree[node] = val;
            return;
        }
        update(node*2, s, (s+e)/2, i, val);
        update(node*2 + 1, (s+e)/2 + 1, e, i, val);
        tree[node] = f(tree[node*2], tree[node*2 + 1]);
    }
};


class SegTreeLazy{
public:   
    int n;
    vector<ll> arr, segtree, lazy;


    SegTreeLazy(int n_input, vector<ll> &input_arr){
        n = n_input;
        arr.resize(n);
        for(int i=0; i<n; i++) arr[i] = input_arr[i];
        lazy = vector<ll>(4*n+5, 0);
        segtree = vector<ll>(4*n+5, 0);
        init(1, 0, n-1);
    }
    void init(int node, int s, int e){
        if(s == e){
            segtree[node] = arr[s];
            return;
        }
        init(node * 2, s, (s + e)/2);
        init(node * 2 + 1, (s + e)/2 + 1, e);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
        return;
    }
    // add s~e += target
    void update(int i1, int i2, ll target){
        update(1, 0, n-1, i1, i2, target);
    }

    void update(int node, int s, int e, int i1, int i2, ll target){
        segtree[node] = lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] = target;
            segtree[node] = lazy[node] * (e - s + 1);
            if(e != s){
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = 0;
            return;
        }
        update(node*2, s, (s + e)/2, i1, i2, target);
        update(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }

    ll query(int i1, int i2){
        return query(1, 0, n-1, i1, i2);
    }

    ll query(int node, int s, int e, int i1, int i2){
        segtree[node] = lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return 0;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        ll q1 = query(node*2, s, (s+e)/2, i1, i2);
        ll q2 = query(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return q1 + q2;
    }
};



vector<int> vy;
vector<pii> vx;
SegTree Sgmin;

pii find_range(pii p){
    pii p1 = {p.X, 0x3f3f3f3f};
    int n1 = CNT_LOWER(vx, p1) - 1;
    int mn
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<int> inp(m);
    for(int i=0; i<m; i++) cin >> inp[i];
    vy.resize(m/2-1);
    vx.resize(m/2-1);
    for(int i=0; i<m/2-1; i++){
        vx[i] = {inp[i*2], inp[i*2+2]};
        vy[i] = inp[i*2+1];
    }
    
    Sgmin = SegTree(m/2-1, vy, [](int l, int r){return min(l, r);}, 0x3f3f3f3f);

    return 0;
}