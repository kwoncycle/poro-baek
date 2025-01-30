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


class SegTree_min
{
    int n;
    vector<ll> segtree, arr;
 
public:
    SegTree_min(int n_input, vector<ll>& arr_input){
        n = n_input;
        segtree = vector<ll>(4*n+10, 0);
        arr = vector<ll>(n);
        for(int i=0; i<n; i++) arr[i] = arr_input[i];
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        init(node*2, start, (start + end)/2);
        init(node*2 + 1, (start + end)/2 + 1, end);

        // CHANGE THIS AS WELL
        segtree[node] = min(segtree[node*2], segtree[node*2 + 1]);
    }
    void update(int target, ll val){
        arr[target] = val;
        update_segtree(1, 0, n-1, target, val);
    }
    void update_segtree(int node, int start, int end, int target, ll val) {
        if(target < start or end < target) return;
        if(start == end){
            segtree[node] = val;
            return;
        }

        update_segtree(2*node, start, (start + end)/2, target, val);
        update_segtree(2*node + 1, (start + end)/2 + 1, end, target, val);
        
        // CHANGE AS NEEDED
        segtree[node] = min(segtree[node*2], segtree[node*2 + 1]);
        return;
    }
 
    ll query(int node, int start, int end, int left, int right) {
        if(right < start or end < left) return 0x3f3f3f3f3f3fll;
        if(left <= start and end <= right) return segtree[node];

        ll q1 = query(node*2, start, (start + end)/2, left, right);
        ll q2 = query(node*2 + 1, (start + end)/2 + 1, end, left, right);

        // CHANGE AS NEEDED
        return min(q1, q2);
    }
};
// USAGE: SegTree segtree(n, arr);


class SegTree_sum
{
    int n;
    vector<ll> segtree, arr;
 
public:
    SegTree_sum(int n_input, vector<ll>& arr_input){
        n = n_input;
        segtree = vector<ll>(4*n+10, 0);
        arr = vector<ll>(n);
        for(int i=0; i<n; i++) arr[i] = arr_input[i];
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        init(node*2, start, (start + end)/2);
        init(node*2 + 1, (start + end)/2 + 1, end);

        // CHANGE THIS AS WELL
        segtree[node] = segtree[node*2] + segtree[node*2 + 1];
    }
    void update(int target, ll val){
        arr[target] = val;
        update_segtree(1, 0, n-1, target, val);
    }
    void update_segtree(int node, int start, int end, int target, ll val) {
        if(target < start or end < target) return;
        if(start == end){
            segtree[node] = val;
            return;
        }

        update_segtree(2*node, start, (start + end)/2, target, val);
        update_segtree(2*node + 1, (start + end)/2 + 1, end, target, val);
        
        // CHANGE AS NEEDED
        segtree[node] = segtree[node*2] + segtree[node*2 + 1];
        return;
    }
 
    ll query(int node, int start, int end, int left, int right) {
        if(right < start or end < left) return 0;
        if(left <= start and end <= right) return segtree[node];

        ll q1 = query(node*2, start, (start + end)/2, left, right);
        ll q2 = query(node*2 + 1, (start + end)/2 + 1, end, left, right);

        // CHANGE AS NEEDED
        return q1 + q2;
    }
};
// USAGE: SegTree segtree(n, arr);



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<ll> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    SegTree_sum sg_sum(n, v);
    SegTree_min sg_min(n, v);

    int qq; cin >> qq;
    while(qq--){
        int q; cin >> q;
        if(q == 1){
            ll a, b; cin >> a >> b;
            sg_sum.update(a-1, b);
            sg_min.update(a-1, b);
        }
        else{
            ll a, b; cin >> a >> b;
            a--;
            ll ans = 0;
            int st1 = 0, ed1 = a;
            if(sg_min.query(1, 0, n-1, st1, ed1) >= b) ans += sg_sum.query(1, 0, n-1, st1, ed1);
            else{
                while(st1 + 1 < ed1){
                    int md = (st1 + ed1)/2;
                    if(sg_min.query(1, 0, n-1, md, a) >= b) ed1 = md;
                    else st1 = md;
                }
                ans += sg_sum.query(1, 0, n-1, ed1, a);
            }

            st1 = a, ed1 = n-1;
            if(sg_min.query(1, 0, n-1, st1, ed1) >= b) ans += sg_sum.query(1, 0, n-1, st1, ed1);
            else{
                while(st1 + 1 < ed1){
                    int md = (st1 + ed1)/2;
                    if(sg_min.query(1, 0, n-1, a, md) >= b) st1 = md;
                    else ed1 = md;
                }
                ans += sg_sum.query(1, 0, n-1, a, st1);
            }

            ans -= sg_sum.query(1, 0, n-1, a, a);
            cout << ans << "\n";
        }
    }
    return 0;
}