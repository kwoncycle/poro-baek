#include <bits/stdc++.h>
using namespace std;
 
#define ll int
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

struct HLD{
    ll n; // size of graph, |V|
    vector<vector<ll>> graph, child;
    vector<ll> par, top, segtree, sz, depth, in, out, arr, in_inv;
    ll tm = 0;
    HLD(){
        cin >> n;
        graph.resize(n+1);
        par.resize(n+1, 0);
        top.resize(n+1, 0);
        segtree.resize(4*n+8, 0);
        sz.resize(n+1, 0);
        depth.resize(n+1, 0);
        in.resize(n+1, 0);
        out.resize(n+1, 0);
        arr.resize(n+1, 0);
        child.resize(n+1);
        in_inv.resize(n+1, 0);
        for(int i=1; i<=n-1; i++){
            ll u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        par[1] = 0;
        depth[1] = 1;
        dfs1(1);

        top[1] = 1;
        dfs2(1);

        find_arr();

        init_seg(1, 0, n-1);
    }

    // determine par, sz, order of children (with sz).
    void dfs1(int x){ 
        sz[x] = 1;
        for(auto &u:graph[x]){
            if(u == par[x]) continue;
            depth[u] = depth[x] + 1;
            par[u] = x;
            dfs1(u);
            sz[x] += sz[u];
            child[x].push_back(u);
            if(sz[u] > sz[child[x][0]]) swap(child[x][0], child[x].back());
        }
    }

    // make DFS ordering with child-, determine HLD
    void dfs2(int x){
        in[x] = tm; 
        in_inv[tm] = x;
        tm++;
        for(auto &u:child[x]){
            if(u == child[x][0]) top[u] = top[x];
            else top[u] = u;
            dfs2(u);
        }

        out[x] = tm;
    }

    void find_arr(){
        for(int i=1; i<=n; i++){
            arr[in[i]] = 99999999;
        }
    }

    void init_seg(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        int mid = (start + end)/2;
        init_seg(node*2, start, mid);
        init_seg(node*2+1, mid + 1, end);
        segtree[node] = min(segtree[node*2], segtree[node*2+1]);
    }

    void update(int node, int start, int end, ll i1, ll val){
        if(i1 < start or end < i1) return;
        if(start == end){
            segtree[node] = val;
            return;
        }
        int mid = (start + end)/2;
        update(node*2, start, mid, i1, val);
        update(node*2+1, mid+1, end, i1, val);
        segtree[node] = min(segtree[node*2], segtree[node*2+1]);
    }

    ll query(int node, int start, int end, ll i1, ll i2){
        if(i2 < start or end < i1) return 99999999;
        if(i1 <= start and end <= i2){
            return segtree[node];
        }
        int mid = (start + end)/2;
        ll q1 = query(node*2, start, mid, i1, i2);
        ll q2 = query(node*2+1, mid+1, end, i1, i2);
        return min(q1, q2);
    }

    void update_hld(ll i){
        if(arr[in[i]] == 99999999) arr[in[i]] = in[i];
        else arr[in[i]] = 99999999;
        update(1,0,n-1,in[i],arr[in[i]]);
    }

    ll query_hld(ll u, ll v){
        if(u == v) {
            return arr[in[u]];
        }
        ll tu = top[u], tv = top[v];
        if(tu == tv){
            if(depth[u] > depth[v]) swap(u, v);
            ll q = query(1, 0, n-1, in[u], in[v]);
            return q;
        }
        else{
            if(depth[tu] < depth[tv]) {
                swap(tu, tv);
                swap(u, v);
            }
            ll q = query(1, 0, n-1, in[tu], in[u]);
            ll q1 = query_hld(par[tu], v);
            if(q1 != 99999999) q = q1;
            return q;
        }
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    HLD hld;
    int qq; cin >> qq;
    while(qq--){
        int q; cin >> q;
        if(q == 1){
            ll i; cin >> i;
            hld.update_hld(i);
        }
        else{
            ll v; cin >> v;
            ll ans = hld.query_hld(1, v);
            if(ans == 99999999) ans = -1;
            else {
                ans = hld.in_inv[ans];
            }
            cout << ans << "\n";
        }
    }
    return 0;
}