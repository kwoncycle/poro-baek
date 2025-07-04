#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

const int MX = 4000100;

struct SegTree{
    int n;
    ll tree[MX], lazy[MX];
    SegTree(int _n) : n(_n) {}

    void update(int l, int r, ll val){
        U(1, 0, n-1, l, r, val);
    }
    void U(int node, int st, int ed, int l, int r, ll val){
        flu(node, st, ed);
        if(r < st or ed < l) return;
        if(l <= st and ed <= r){
            lazy[node] = val;
            flu(node, st, ed);
            return;
        }
        U(node*2, st, (st+ed)/2, l, r, val);
        U(node*2 + 1, (st+ed)/2 + 1, ed, l, r, val);
        tree[node] = max(tree[node*2], tree[node*2 + 1]);
    }

    ll query(){
        flu(1, 0, n-1); 
        return tree[1];
    }

    void flu(int node, int st, int ed){
        assert(1 <= node and node < MX);
        tree[node] += lazy[node];
        if(st != ed){
            lazy[node*2] += lazy[node];
            lazy[node*2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
} T(1000000);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, l, r;
    cin >> n >> l >> r;
    l--;
    vector<array<ll, 4>> task;
    for(int i=0; i<n; i++){
        ll x, y, s; cin >> x >> y >> s;
        task.push_back({x-r, s, y-r, y+r});
        task.push_back({x+r+1, -s, y-r, y+r});
        task.push_back({x-l, -s, y-l, y+l});
        task.push_back({x+l+1, s, y-l, y+l});
    }
    sort(all(task));
    vector<ll> v;
    for(auto &[_, _0, y1, y2] : task) {
        v.push_back(y1); v.push_back(y2);
        v.push_back(y1-1); v.push_back(y2+1);
    }

    sort(all(v));
    v.erase(unique(all(v)), v.end());

    for(auto &[_, _0, y1, y2] : task) {
        y1 = CNT_LOWER(v, y1) + 2;
        y2 = CNT_LOWER(v, y2) + 2;
    }

    n = task.size();

    ll ans = 0;

    for(int i=0; i<n; i++){
        int i1 = i;
        while(i1 < n and task[i1][0] == task[i][0]){
            T.update(task[i1][2], task[i1][3], task[i1][1]);
            i1++;
        }
        ans = max(ans, T.query());
        i = i1 - 1;
    }
    cout << ans << "\n";

    return 0;
}