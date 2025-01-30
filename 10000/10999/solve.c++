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

#define segtreetype long long
class SegTree{
public:   
    int n;
    vector<ll> arr, segtree, lazy;
    SegTree(int n_input, vector<ll> &input_arr){
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
    void update_range(int i1, int i2, ll target){
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(int node, int s, int e, int i1, int i2, ll target){
        update_lazy(node, s, e);
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] += target;
            update_lazy(node, s, e);
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }

    ll query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    ll query_segtree(int node, int s, int e, int i1, int i2){
        update_lazy(node, s, e);
        if(e < i1 or i2 < s) return 0;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        ll q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        ll q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return q1 + q2;
    }

    void update_lazy(int node, int s, int e){
        segtree[node] += lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k; m += k;
    vector<ll> v(n);
    for(int i=0; i<n; i++){
        cin >> v[i];
    }
    SegTree sgtree(n, v);
    while(m--){
        int a; cin >> a;
        if(a == 1){
            ll b, c, d; cin >> b >> c >> d;
            b--; c--;
            sgtree.update_range(b, c, d);
        }
        if(a == 2){
            ll b, c; cin >> b >> c;
            b--; c--;
            cout << sgtree.query(b, c) << "\n";
        }
    }
    return 0;
}