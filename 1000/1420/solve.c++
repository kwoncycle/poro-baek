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


struct Edge{
    ll u, v, cap, cur;
    Edge(ll _u, ll _v, ll _cap, ll _cur): u(_u), v(_v), cap(_cap), cur(_cur){}
};


struct Dinic{
    vector<vector<ll>> graph;
    vector<Edge> edges;
    ll n, start, end; // |node|, flow start, flow end
    vector<ll> level, DFS_order;

public:
    Dinic(ll _n, ll _start, ll _end, vector<Edge> &_Edge) : n(_n), start(_start), end(_end){
        graph = vector<vector<ll>>(n+1);
        edges = vector<Edge>((ll)_Edge.size()*2, {0,0,0,0});
        ll idx = 0;
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<string> v(n+2);
    for(int i=1; i<=n; i++) {
        cin >> v[i];
        v[i] = "#" + v[i] + "#";
    }
    v[0] = string(m+2, '#'); v[n+1] = string(m+2, '#');
    int st, ed;
    vector<pii> asdf = {{0,1}, {0,-1}, {1, 0}, {-1, 0}};
    vector<Edge> edges;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(v[i][j] == 'K') st = (i*m+j)*2;
            if(v[i][j] == 'H') ed = (i*m+j)*2+1;
        }
    }

    edges.push_back({st, st+1, 100, 0});
    edges.push_back({ed-1, ed, 100, 0});

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(v[i][j] != '#'){
                edges.push_back({(i*m+j)*2, (i*m+j)*2+1, 1, 0});
                for(auto &[i1,j1]:asdf){
                    if(v[i+i1][j+j1] != '#'){
                        //if(i*m+j != ed and (i+i1)*m+j+j1 != st)
                        edges.push_back({(i*m+j)*2+1, ((i+i1)*m+j+j1)*2, 1, 0});
                    }
                }
            }
        }
    }

    Dinic dinic(2*n*m+2*m+5, st, ed, edges);
    int cnt = 0;
    for(auto &[u,v1,c1,c2]:dinic.edges){
        if(u == st) cnt += c2;
        if(u == st and v1 == ed){
            cnt = -1; break;
        }
    }
    cout << cnt << "\n";
    return 0;
}