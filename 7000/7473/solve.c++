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



template<class flow_t> struct Edge{
    int u, v;
    flow_t cap, cur;
    Edge(int _u, int _v, flow_t _cap, flow_t _cur): u(_u), v(_v), cap(_cap), cur(_cur){}
};


template<class flow_t> struct Dinic{
    vector<vector<int>> graph;
    vector<Edge<flow_t>> edges;
    int n, start, end; // |node|, flow start, flow end
    vector<ll> DFS_order, level;

public:
    Dinic(int _n, int _start, int _end, vector<Edge<flow_t>> &_Edge) : n(_n), start(_start), end(_end){
        graph = vector<vector<int>>(n+1);
        edges = vector<Edge<flow_t>>((int)_Edge.size()*2, {0,0,0,0});
        int idx = 0;
        DFS_order.resize(n+1);
        level.resize(n+1);
        for(auto [u, v, cap, cur]:_Edge){
            edges[idx] = {u, v, cap, cur};
            edges[idx + 1] = {v, u, 0, 0};
            graph[u].push_back(idx);
            graph[v].push_back(idx + 1);
            idx += 2;
        }

        while(true){
            reset();
            BFS();
            if(level[end] > 0x3f3f3f3f3fll) break;
            while(true){
                ll x = DFS(start, 0x3f3f3f3f3f3fll);
                if(!x) break;
            }
        }
    }

    void reset(){
        fill(level.begin(), level.end(), 0x3f3f3f3f3f3fll);
        fill(DFS_order.begin(), DFS_order.end(), 0);
    }

    void BFS(){ // set level[]
        queue<ll> q;
        q.push(start);
        level[start] = 0;
        while(!q.empty()){
            int o = q.front(); q.pop();
            for(int i:graph[o]){
                if(edges[i].cap <= edges[i].cur) continue;
                if(level[edges[i].v] > level[o] + 1){
                    level[edges[i].v] = level[o] + 1;
                    q.push(edges[i].v);
                }
            }
        }
    }

    flow_t DFS(int u, flow_t mx){
        if(u == end) return mx;
        for(ll &i = DFS_order[u]; i < (ll)graph[u].size(); i++){
            int v = edges[graph[u][i]].v;
            if(level[u] + 1 == level[v] and edges[graph[u][i]].cap > edges[graph[u][i]].cur){
                mx = min(mx, edges[graph[u][i]].cap - edges[graph[u][i]].cur);
                flow_t o = DFS(v, mx);
                if(o > 0){
                    edges[graph[u][i]].cur += o;
                    edges[graph[u][i]^1].cur -= o;
                    return o;
                }
            }
        }
        return 0;
    }

    vector<int> mincut(){
        reset();
        BFS();
        vector<int> ans;
        for(int i=1; i<=n; i++){
            if(level[i] < 0x3f3f3f3f3fll) ans.push_back(i); 
        }
        return ans;
    }
};

// requires vector<Edge>

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> wplus(n+1, 0), wminus(n+1, 0);
    for(int i=1; i<=n; i++) cin >> wplus[i];
    for(int i=1; i<=n; i++) cin >> wminus[i];

    vector<Edge<ll>> v;

    int start = 2*n+1, end = 2*n+2;
    for(int i=1; i<=n; i++){
        v.push_back({start,i*2-1,wminus[i],0});
        v.push_back({i*2,end,wplus[i],0});
    }
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        v.push_back({a*2-1,b*2,0x3f3f3f3f3f3fll,0});
    }

    Dinic<ll> dinic(2*n+2, start, end, v);
    vector<int> S = dinic.mincut();
    vector<int> check(2*n+3, 0);
    for(int i:S) check[i] = 1;
    vector<int> ans;
    ll ttl = 0;
    for(int i=1; i<=n; i++){
        if(check[i*2-1] == 0) {
            ans.push_back(i*2 - 1);
            ttl += wminus[i];
        }
        if(check[i*2] == 1) {
            ans.push_back(i*2);
            ttl += wplus[i];
        }
    }

    cout << ttl << "\n";
    cout << (int)ans.size() << "\n";
    for(int i:ans){
        if(i%2 == 1) cout << (i+1)/2 << " -\n";
        else cout << i/2 << " +\n";
    }


    return 0;
}