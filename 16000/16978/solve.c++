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
        if(lazy[node]){
            segtree[node] = lazy[node] * (e - s + 1);
            if(e != s){
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = 0;
        }
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
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }

    ll query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    ll query_segtree(int node, int s, int e, int i1, int i2){
        if(lazy[node]){
            segtree[node] = lazy[node] * (e - s + 1);
            if(e != s){
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = 0;
        }
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
    vector<ll> ans(qq, -1);
    vector<array<ll, 4>> qry2;
    vector<array<ll, 2>> qry1;
    for(int i=0; i<qq; i++){
        int q; cin >> q;
        if(q == 1){
            int i1, v; cin >> i1 >> v;
            qry1.push_back({i1, v});
        }
        else{
            int k, i1, j1; cin >> k >> i1 >> j1;
            qry2.push_back({k, i1, j1, i});
        }
    }

    sort(qry2.begin(), qry2.end());
    int i2 = 0;
    for(int i=0; i<=(int)qry1.size(); i++){
        while(i2 < (int)qry2.size() and qry2[i2][0] == i){
            int idx = qry2[i2][3];
            ans[idx] = sgtree.query(qry2[i2][1]-1, qry2[i2][2]-1);
            i2++;
        }

        if(i < (int)qry1.size()) sgtree.update_range(qry1[i][0]-1, qry1[i][0]-1, qry1[i][1]);
    }

    for(ll i:ans){
        if(i >= 0) cout << i << "\n";
    }
    return 0;
}