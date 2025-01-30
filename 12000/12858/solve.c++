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

struct SegTree_Sum{
    int n;
    vector<ll> arr, segtree, lazy;
public:
    SegTree_Sum(int ni, vector<ll> arri){
        n = ni;
        arr = vector<ll>(n, 0);
        segtree = vector<ll>(4*n+5, 0);
        lazy = vector<ll>(4*n+5, 0);
        for(int i=0; i<n; i++){
            arr[i] = arri[i];
        }
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        int mid = (start + end)/2;
        init(node*2, start, mid);
        init(node*2+1, mid+1, end);
        segtree[node] = segtree[node*2] + segtree[node*2+1];
    }

    void update_range(int node, int start, int end, int i1, int i2, ll target){
        update_lazy(node, start, end);
        if(i2 < start or end < i1){
            return;
        }
        if(i1 <= start and end <= i2){
            lazy[node] += target;
            update_lazy(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update_range(node*2, start, mid, i1, i2, target);
        update_range(node*2+1, mid+1, end, i1, i2, target);
        segtree[node] = segtree[node*2] + segtree[node*2+1];
    }

    ll query(int node, int start, int end, int i1, int i2){
        update_lazy(node, start, end);
        if(i2 < start or end < i1){
            return 0;
        }
        if(i1 <= start and end <= i2){
            return segtree[node];
        }
        int mid = (start + end) / 2;
        ll q1 = query(node*2, start, mid, i1, i2);
        ll q2 = query(node*2+1, mid+1, end, i1, i2);
        return q1 + q2;
    }

    void update_lazy(int node, int start, int end){
        segtree[node] += (end - start + 1) * lazy[node];

        lazy[node*2] += lazy[node];
        lazy[node*2+1] += lazy[node];
        lazy[node] = 0;
    }
};


struct SegTree_GCD{
    int n;
    vector<ll> arr, segtree;
public:
    SegTree_GCD(int ni, vector<ll> arri){
        n = ni - 1;
        arr = vector<ll>(n, 0);
        segtree = vector<ll>(4*n+5, 0);
        for(int i=0; i<n; i++){
            arr[i] = arri[i+1] - arri[i];
        }
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        int mid = (start + end)/2;
        init(node*2, start, mid);
        init(node*2+1, mid+1, end);
        segtree[node] = __gcd(segtree[node*2], segtree[node*2+1]);
    }

    void update_range(int a, int b, ll target){
        if(a > 0) update(1, 0, n-1, a-1, target);
        if(b < n) update(1, 0, n-1, b, -target);
    }

    // i1, i2 : (arr[i1] - arr[i1-1]) += target || arr[i2+1] - arr[i2]
    void update(int node, int start, int end, int i1, ll target){
        if(i1 < start or end < i1){
            return;
        }
        if(i1 <= start and end <= i1){
            segtree[node] += target;
            return;
        }
        int mid = (start + end) / 2;
        update(node*2, start, mid, i1, target);
        update(node*2+1, mid+1, end, i1, target);
        segtree[node] = __gcd(segtree[node*2], segtree[node*2+1]);
    }

    ll query(int node, int start, int end, int i1, int i2){
        if(i2 < start or end < i1){
            return 0;
        }
        if(i1 <= start and end <= i2){
            return segtree[node];
        }
        int mid = (start + end) / 2;
        ll q1 = query(node*2, start, mid, i1, i2);
        ll q2 = query(node*2+1, mid+1, end, i1, i2);
        return __gcd(q1, q2);
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<ll> arr(n);
    for(int i=0; i<n; i++) cin >> arr[i];
    SegTree_Sum sg_sum(n, arr);
    SegTree_GCD sg_gcd(n, arr);
    int qq; cin >> qq;
    while(qq--){
        ll q; cin >> q;
        if(q == 0){
            int a, b; cin >> a >> b;
            a--; b--;
            if(a == b){
                cout << sg_sum.query(1, 0, n-1, a, b) << "\n";
            }
            else{
                ll u1 = sg_sum.query(1, 0, n-1, a, a);
                ll u2 = abs(sg_gcd.query(1, 0, n-2, a, b-1));
                //cout << u1 << ' ' << u2 << "\n";
                cout << __gcd(u1, u2) << "\n";
            }
        }
        else{
            int a, b; cin >> a >> b; a--; b--;
            sg_sum.update_range(1, 0, n-1, a, b, q);
            sg_gcd.update_range(a, b, q);
        }
    }
    return 0;
}