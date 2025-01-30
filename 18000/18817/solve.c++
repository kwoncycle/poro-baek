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
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector<vector<int>> v(n);
    for(int i=0; i<n; i++){
        int o; cin >> o;
        while(o--){
            int a; cin >> a;
            a--;
            v[i].push_back(a);
        }
        sort(v[i].begin(), v[i].end());
    }

    int st = 0, ed = n; // st ok ed sad
    while(st + 1 < ed){
        int md = (st + ed) / 2;
        vector<vector<int>> graph(2*n);
        for(int i=0; i<=md; i++){
            for(int j:v[i]){
                if(v[j].empty()){
                    if(i < j and j <= md){
                        graph[i].push_back(n+j);
                    }
                }
            }
        }

        int start = 2*n, end = 2*n+1;
        vector<Edge> E;

        for(int i=0; i<=md; i++){
            for(int j:graph[i])
                E.push_back({i, j, 0x3f3f3f, 0});
        }
        for(int i=0; i<=ed; i++) {
            if(!v[i].empty())
                E.push_back({start, i, 1, 0});
        }
        for(int i=0; i<=ed; i++) {
            if(v[i].empty())
                E.push_back({i+n, end, 1, 0});
        }

        Dinic dinic(2*n+2, start, end, E);

        int cnt = 0;
        for(int i:dinic.graph[end]){
            i ^= 1;
            if(dinic.edges[i].cap == dinic.edges[i].cur) {
                cnt++;
                //cout << dinic.edges[i].u << " " << dinic.edges[i].v << "\n";
            }
        }

        int needed = 0;
        for(int i=0; i<=md; i++) 
            if(v[i].empty()) 
                needed++;

        //cout << md << " " << needed << " " << cnt << "\n";

        if(cnt >= needed){
            st = md;
        }
        else ed = md;
    }

    cout << st + 1<< "\n";
    return 0;
}