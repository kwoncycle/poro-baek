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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<Edge> v;
    int st = 0, ed = 2*n + 1;
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        b += n;
        v.push_back(Edge(a, b, 1, 0));
    }
    for(int i=1; i<=n; i++){
        v.push_back(Edge(st, i, 1, 0));
        v.push_back(Edge(i+n, ed, 1, 0));
    }

    Dinic D(ed + 1, st, ed, v);
    if(D.flow == n){
        cout << "-1\n"; return 0;
    }

    int non;
    for(int i:D.graph[st]){
        if(D.edges[i].cap != D.edges[i].cur){
            non = D.edges[i].v; break;
        }
    }

    vector<int> check(2*n+3, 0);
    queue<int> q;
    q.push(non);
    check[non] = 1;
    while(!q.empty()){
        int node = q.front(); q.pop();
        for(int i:D.graph[node]){
            if(D.edges[i].cap != D.edges[i].cur){
                if(!check[D.edges[i].v]){
                    q.push(D.edges[i].v); check[D.edges[i].v] = 1;
                }
            }
        }
    }

    int cnt = 0;
    for(int i=1; i<=n; i++){
        if(check[i]) cnt++;
    }
    cout << cnt << "\n";
    for(int i=1; i<=n; i++){
        if(check[i]) cout << i << " ";
    }
    cout << "\n";

    return 0;
}