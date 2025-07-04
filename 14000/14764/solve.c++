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

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

struct Edge{
    ll u, v, cap, cur;
    Edge(ll _u, ll _v, ll _cap, ll _cur): u(_u), v(_v), cap(_cap), cur(_cur){}
};


struct Dinic{
    vector<vector<ll>> graph;
    vector<Edge> edges;
    ll n, start, end; // |node|, flow start, flow end
    vector<ll> level, DFS_order;
    ll flow = 0;
public:
    Dinic(ll _n, ll _start, ll _end, vector<Edge> &_Edge) : n(_n), start(_start), end(_end){
        graph = vector<vector<ll>>(n+1);
        edges = vector<Edge>((ll)_Edge.size()*2, {0,0,0,0});
        ll idx = 0;
        DFS_order.resize(n+1);
        level.resize(n+1);
        for(auto &[u, v, cap, cur]:_Edge){
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
                flow += x;
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
            ll o = q.front(); q.pop();
            for(ll i:graph[o]){
                if(edges[i].cap <= edges[i].cur) continue;
                if(level[edges[i].v] > level[o] + 1){
                    level[edges[i].v] = level[o] + 1;
                    q.push(edges[i].v);
                }
            }
        }
    }

    ll DFS(ll u, ll mx){
        if(u == end) return mx;
        for(ll &i = DFS_order[u]; i < (ll)graph[u].size(); i++){
            ll v = edges[graph[u][i]].v;
            if(level[u] + 1 == level[v] and edges[graph[u][i]].cap > edges[graph[u][i]].cur){
                mx = min(mx, edges[graph[u][i]].cap - edges[graph[u][i]].cur);
                ll o = DFS(v, mx);
                if(o > 0){
                    edges[graph[u][i]].cur += o;
                    edges[graph[u][i]^1].cur -= o;
                    return o;
                }
            }
        }
        return 0;
    }

    vector<ll> mincut(){
        reset();
        BFS();
        vector<ll> ans;
        for(int i=1; i<=n; i++){
            if(level[i] < 0x3f3f3f3f3fll) ans.push_back(i); 
        }
        return ans;
    }
};

// requires vector<Edge>

vector<ll> dst(1005, 0x3f3f3f3f3f3f3fll);
vector<array<ll, 2>> graph[1005];
vector<ll> G[1005];
ll v[1005];
int chk[1005];

void DFS(int node){
    for(int i:G[node]){
        if(chk[i] == 0){
            chk[i] = 1;
            DFS(i);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, c;
    cin >> n >> m >> c;
    for(int i=1; i<=c; i++) cin >> v[i];
    for(int i=0; i<m; i++){
        int a, b, val;
        cin >> a >> b >> val;
        graph[a].push_back({b, val});
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq; // (dst[node], node)
    dst[0] = 0;
    pq.push({dst[0], 0});
    while(!pq.empty()){
        auto [d, node] = pq.top(); pq.pop();
        if(dst[node] < d) continue;
        for(auto &[nd1, d1]:graph[node]){
            if(dst[nd1] > d + d1){
                dst[nd1] = d + d1;
                pq.push({dst[nd1], nd1});
            }
        }
    }

    for(int i=0; i<n; i++){
        for(auto &[j, d]: graph[i]){
            if(dst[i] + d == dst[j]){
                G[i].push_back(j);
            }
        }
    }

    vector<Edge> edges;
    
    int st = 0, ed = 2*c + 1;
    for(int i=1; i<=c; i++) {
        edges.push_back(Edge(st, i, 1, 0));
        edges.push_back(Edge(i+c, ed, 1, 0));
    }

    for(int i=1; i<=c; i++){
        memset(chk, 0, sizeof(chk));
        chk[v[i]] = 1;
        DFS(v[i]);
        for(int j=1; j<=c; j++){
            if(j == i) continue;
            if(chk[v[j]]){
                edges.push_back(Edge(i, j+c, 1, 0));
            }
        }
    }

    Dinic DN(ed+1, st, ed, edges);
    cout << c - DN.flow << "\n";

    return 0;
}