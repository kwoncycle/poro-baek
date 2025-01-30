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


// THIS IS LAZY
class SegTree{
public:   
    int n;
    vector<ll> arr, segtree, lazy;


    SegTree(int n_input, vector<int> &arr_i){
        n = n_input;
        arr.resize(n);
        for(int i=0; i<n; i++) arr[i] = arr_i[i];
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
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
        return;
    }
    // add s~e += target
    void update_range(int i1, int i2, ll target){
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(int node, int s, int e, int i1, int i2, ll target){
        segtree[node] += lazy[node];
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] += target;
            segtree[node] += lazy[node];
            if(e != s){
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
    }

    ll query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    ll query_segtree(int node, int s, int e, int i1, int i2){
        segtree[node] += lazy[node];
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return 0x3f3f3f3f;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        ll q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        ll q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return min(q1, q2);
    }
};

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(2*n);
    for(int i=0; i<2*n; i++) cin >> v[i];
    vector<vector<int>> p(n+1);
    for(int i=0; i<2*n; i++) p[v[i]].push_back(i);
    if(n%2 == 1){
        cout << "(\n"; return 0;
    }
    int sm = 0;
    vector<int> arr(2*n+1);
    for(int i=0; i<=2*n; i++) arr[i] = 2*n-i;
    SegTree tree(2*n+1, arr);
    vector<int> ans(2*n, 0);
    for(int i=0; i<2*n; i++){
        if(ans[i]) {
            sm += ans[i];
            if(sm < 0){
                cout << "(\n"; return 0; 
            }
            continue;
        }
        int i1 = p[v[i]][0], i2 = p[v[i]][1];
        
        tree.update_range(0, i2, -2);
        tree.update_range(0, i1, -2);
        int mn = tree.query(0, 2*n);
        tree.update_range(0, i2, 2);
        tree.update_range(0, i1, 2);

        int b1 = 0, b2 = 0;
        if(mn < 0){ // ')'
            b2 = 1;
        }
        if(sm == 0) b1 = 1;
        if(b1 == 1 and b2 == 1){
            cout << "(\n"; return 0; 
        }
        if(b2){
            ans[i1] = -1; ans[i2] = -1;
        }
        else{
            ans[i1] = 1; ans[i2] = 1;
        }
        if(ans[i1] == 1){
            tree.update_range(0, i2, -2*ans[i2]);
            tree.update_range(0, i1, -2*ans[i1]);
        }
        sm += ans[i];
        if(sm < 0){
            cout << "(\n"; return 0; 
        }
    }
    if(sm != 0){
        cout << "(\n"; return 0;
    }
    //assert(tree.query(0,0) == 0 and tree.query(2*n,2*n) == 0);
    for(int i=0; i<2*n; i++){
        if(ans[i] == 1) cout << "(";
        else cout << ")";
    }
    cout << "\n";
    return 0;
}