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
    vector<vector<array<ll, 2>>> graph, child;
    vector<ll> par, top, segtree, sz, depth, in, out, arr;
    vector<array<ll, 2>> edges;
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
        edges.resize(n+1);
        for(int i=1; i<=n-1; i++){
            ll u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
            edges[i] = {u, v};
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
        for(auto &[u, w]:graph[x]){
            if(u == par[x]) continue;
            depth[u] = depth[x] + 1;
            par[u] = x;
            dfs1(u);
            sz[x] += sz[u];
            child[x].push_back({u, w});
            if(sz[u] > sz[child[x][0][0]]) swap(child[x][0], child[x].back());
        }
    }

    // make DFS ordering with child-, determine HLD
    void dfs2(int x){
        in[x] = tm; tm++;
        for(auto &[u, w]:child[x]){
            if(u == child[x][0][0]) top[u] = top[x];
            else top[u] = u;
            dfs2(u);
        }

        out[x] = tm;
    }

    void find_arr(){
        for(int i=1; i<=n; i++){
            for(auto &[u, w]:child[i]){
                arr[in[u]] = w;
            }
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
        segtree[node] = max(segtree[node*2], segtree[node*2+1]);
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
        segtree[node] = max(segtree[node*2], segtree[node*2+1]);
    }

    ll query(int node, int start, int end, ll i1, ll i2){
        if(i2 < start or end < i1) return -999;
        if(i1 <= start and end <= i2){
            return segtree[node];
        }
        int mid = (start + end)/2;
        ll q1 = query(node*2, start, mid, i1, i2);
        ll q2 = query(node*2+1, mid+1, end, i1, i2);
        return max(q1, q2);
    }

    void update_hld(ll i, ll c){
        auto [u, v] = edges[i];
        if(depth[u] < depth[v]) i = v;
        else i = u;
        arr[in[i]] = c;
        update(1,0,n-1,in[i],c);
    }

    ll query_hld(ll u, ll v){
        if(u == v) return 0;
        ll tu = top[u], tv = top[v];
        if(tu == tv){
            if(depth[u] > depth[v]) swap(u, v);
            ll q = query(1, 0, n-1, in[u] + 1, in[v]);
            return q;
        }
        else{
            if(depth[tu] < depth[tv]) {
                swap(tu, tv);
                swap(u, v);
            }
            ll q = 0;
            if(tu != u) q = query(1, 0, n-1, in[tu] + 1, in[u]);
            q = max(q, arr[in[tu]]);
            q = max(q, query_hld(par[tu], v));
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
            ll i, c; cin >> i >> c;
            hld.update_hld(i, c);
        }
        else{
            ll u, v; cin >> u >> v;
            cout << hld.query_hld(u, v) << "\n";
        }
    }
    return 0;
}