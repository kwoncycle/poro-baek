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


// THIS IS LAZY
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
        segtree[node] += lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] += target;
            segtree[node] += lazy[node] * (e - s + 1);
            if(e != s){
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
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
        segtree[node] += lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return 0;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        ll q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        ll q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return q1 + q2;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<ll> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    SegTree sgtree(n, a);

    int qq; cin >> qq;
    while(qq--){
        int q; cin >> q;
        if(q == 1){
            int i, j, k; cin >> i >> j >> k;
            sgtree.update_range(i-1, j-1, k);
        }
        else{
            int x; cin >> x;
            cout << sgtree.query(x-1, x-1) << "\n";
        }
    }
    return 0;
}