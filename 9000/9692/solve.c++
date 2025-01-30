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

struct segtree01{
    int n;
    vector<int> segtree;
    vector<int> len;
    segtree01(int _n):n(_n){
        segtree = vector<int>(4*n+5);
        len = vector<int>(4*n + 5);
        //init(1, 0, n-1);
    }
    /*
    void init(int node, int start, int end){
        if(start == end) segtree[node] = arr[start];
        else{
            int mid = (start + end)/2;
            init(node*2, start, mid);
            init(node*2 + 1, mid + 1, end);
            segtree[node] = segtree[node*2] + segtree[node*2+1];
        }
    }*/

    int query(){
        return len[1];
    }

    void update(int node, int start, int end, int l, int r, int v){
        if(end < l or r < start) return;
        if(l <= start and end <= r){
            segtree[node] += v;
        }
        else{
            int mid = (start + end)/2;
            update(node*2, start, mid, l, r, v);
            update(node*2 + 1, mid + 1, end, l, r, v);
        }

        if(segtree[node] > 0) len[node] = end - start + 1;
        else if(start == end) len[node] = 0;
        else len[node] = len[node*2] + len[node*2 + 1];
    }
};



// THIS IS LAZY
class SegTree{
public:   
    ll n;
    vector<ll> segtree, lazy;


    SegTree(ll n_input){
        n = n_input;
        lazy = vector<ll>(3*n+5, 0);
        segtree = vector<ll>(3*n+5, 0);
        //init(1, 0, n-1);
    }
    /*
    void init(ll node, ll s, ll e){
        if(s == e){
            segtree[node] = arr[s];
            return;
        }
        init(node * 2, s, (s + e)/2);
        init(node * 2 + 1, (s + e)/2 + 1, e);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
        return;
    }*/
    // add s~e += target
    void update_range(ll i1, ll i2, ll target){
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(ll node, ll s, ll e, ll i1, ll i2, ll target){
        assert(node < 3*n + 6);
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

    ll query(ll i1, ll i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    ll query_segtree(ll node, ll s, ll e, ll i1, ll i2){
        assert(node < 3*n + 6);
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
    int n, a, b; cin >> n >> a >> b;
    vector<pii> v(n);
    for(ll i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    SegTree sgtree(2000003);
    vector<array<int, 3>> qry;
    for(int i=0; i<n; i++){
        qry.push_back({v[i].X, v[i].Y, 0}); // 0: in
        qry.push_back({v[i].X, v[i].Y + b, 1});
    }

    sort(qry.begin(), qry.end(), [&](array<int,3> &a, array<int,3> &b){
        return a[1] < b[1];
    });
    int id = 0;
    __int128 ttl = 0;
    __int128 ans = 0;
    for(int i=0; i<=2000001; i++){
        while(id < 2*n and qry[id][1] == i){
            if(qry[id][2] == 1){
                ttl -= sgtree.query(qry[id][0], qry[id][0] + a - 1) - a;
                sgtree.update_range(qry[id][0], qry[id][0] + a - 1, -1); //(1, 0, 2000002, qry[id][0], qry[id][0] + a - 1, -1);
                //ttl -= a;
            }
            else{
                ttl += sgtree.query(qry[id][0], qry[id][0] + a - 1);
                sgtree.update_range(qry[id][0], qry[id][0] + a - 1, 1);
            }
            id++;
        }
        ans += ttl;
        if(id == 2*n) break;
    }
    //cout << ans << "\n";
    
    long double a1 = (long double)ans;
    long double d1 = (long double)((ll)n * (ll)(n-1)/2);
    cout << fixed << setprecision(10) << a1/d1 << "\n";
    return 0;
}