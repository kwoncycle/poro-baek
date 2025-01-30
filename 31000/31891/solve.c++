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

class SegTree
{
    int n;
    vector<ll> segtree, arr;
 
public:
    SegTree(int n_input, vector<ll>& arr_input){
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
    vector<int> v(n+1);
    for(int i=1; i<=n; i++) cin >> v[i];
    vector<ll> arr(n+1, 1);
    SegTree sgtree(n+1, arr);

    double ans = 0;
    ans += (double)(1 + (double)(n-v[1])/2.0);
    sgtree.update(v[1], 0);

    for(int i=2; i<=n; i++){
        int c0 = sgtree.query(1,0,n,min(v[i],v[i-1]),max(v[i],v[i-1]))-1;
        int c1 = sgtree.query(1,0,n,max(v[i],v[i-1]),n);
        if(v[i] > v[i-1]) c1--;
        ans += (double)(c0+c1+2)/2.0;
        sgtree.update(v[i],0);
    }

    cout << fixed << setprecision(12) << ans << "\n";

    return 0;
}