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

struct SegTree{
    int n;
    vector<pll> arr, segtree, lazy;
public:
    SegTree(int n_inp, vector<ll> &arr_input){
        n = n_inp;
        arr.resize(n);
        segtree = vector<pll>(4*n+5, {0, 0});
        lazy = vector<pll>(4*n+5, {0, 0});
        for(int i=0; i<n; i++){
            arr[i] = {0, arr_input[i]};
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
        segtree[node] = {segtree[node*2].X + segtree[node*2+1].X, segtree[node*2].Y + segtree[node*2+1].Y};
    }

    void update_range(int node, int start, int end, int i1, int i2){
        update_lazy(node, start, end);
        if(i2 < start or end < i1){
            return;
        }
        if(i1 <= start and end <= i2){
            lazy[node].X += 1;
            lazy[node].Y += -i1 + 1;
            update_lazy(node, start, end);
            return;
        }
        int mid = (start + end)/2;
        update_range(node*2, start, mid, i1, i2);
        update_range(node*2+1, mid + 1, end, i1, i2);
        segtree[node] = {segtree[node*2].X + segtree[node*2+1].X, segtree[node*2].Y + segtree[node*2+1].Y};
    }

    ll query(int node, int start, int end, int i1, int i2){ //actually i1 == i2
        update_lazy(node, start, end);
        if(i2 < start or end < i1){
            return 0;
        }
        if(i1 <= start and end <= i2){
            return segtree[node].X * i1 + segtree[node].Y;
        }
        int mid = (start + end)/2;
        ll q1 = query(node*2, start, mid, i1, i2);
        ll q2 = query(node*2 + 1, mid + 1, end, i1, i2);
        return q1 + q2;
    }

    void update_lazy(int node, int start, int end){
        segtree[node].X += lazy[node].X * (end - start + 1);
        segtree[node].Y += lazy[node].Y * (end - start + 1);
        if(start != end){
            lazy[node*2].X += lazy[node].X;
            lazy[node*2 + 1].X += lazy[node].X;
            lazy[node*2].Y += lazy[node].Y;
            lazy[node*2 + 1].Y += lazy[node].Y;
        }
        lazy[node] = {0, 0};
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<ll> arr(n);
    for(int i=0; i<n; i++) cin >> arr[i];
    SegTree segtree(n, arr);
    int qq; cin >> qq;
    while(qq--){
        int q; cin >> q;
        if(q == 1){
            int l, r; cin >> l >> r; l--; r--;
            segtree.update_range(1, 0, n-1, l, r);
        }
        else{
            int x; cin >> x; x--;
            cout << segtree.query(1, 0, n-1, x, x) << '\n';
        }
    }
    return 0;
}