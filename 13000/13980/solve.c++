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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

struct Edge{
    ll u, v, cap, cur;
    Edge(ll _u, ll _v, ll _cap, ll _cur): u(_u), v(_v), cap(_cap), cur(_cur){}
};


struct Dinic{
    vector<vector<ll>> graph;
    vector<Edge> edges;
    ll n, start, end; // |node|, flow start, flow end
    vector<ll> level, DFS_order;
    ll ttl = 0;

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
                ttl += x;
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



class djs
{
    int n, m;
    vector<vector<pii>> par;
 
public:
    djs(int n, int m) : n(n), m(m) {
        par.resize(n);
        for(int i=0; i<n; i++) par[i].resize(m);
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                par[i][j] = {i, j};
            }
        }
    }
 
    pii find(pii v) {
        if(par[v.X][v.Y] == v) return v;
        else return par[v.X][v.Y] = find(par[v.X][v.Y]);
    }
 
    bool Union(pii x, pii y) {
        pii px = find(x);
        pii py = find(y);
 
        if(px == py) return false;
 
        par[px.X][px.Y] = py;
        return true;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<string> v(n);
    djs DJS(n, m);
    for(int i=0; i<n; i++) cin >> v[i];

    vector<pii> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'C')
            for(auto p:dir){
                pii t = p + pii(i, j);
                if(0<=t.X and t.X<n and 0<=t.Y and t.Y<m){
                    if(v[t.X][t.Y] == 'L') v[i][j] = 'W';
                }
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'L')
            for(auto p:dir){
                pii t = p + pii(i, j);
                if(0<=t.X and t.X<n and 0<=t.Y and t.Y<m){
                    if(v[t.X][t.Y] == 'L') DJS.Union({i,j}, t);
                }
            }
        }
    }

    int cnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(DJS.find({i, j}) == pii(i, j) and v[i][j] == 'L') cnt++;
        }
    }

    vector<Edge> edges;
    int st = n*m, ed = n*m+1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'C'){
                cnt++;
                int id = (i*m+j);
                if((i+j)%2 == 0) edges.push_back({st, id, 1, 0});
                else edges.push_back({id, ed, 1, 0});
                if((i+j) % 2 == 0){
                    for(auto p:dir){
                        pii t = p + pii(i, j);
                        if(0<=t.X and t.X<n and 0<=t.Y and t.Y<m){
                            if(v[t.X][t.Y] == 'C'){
                                int idt = (t.X*m + t.Y);
                                edges.push_back({id, idt, 1, 0});
                            }
                        }
                    }
                }
            }
        }
    }
    //cout << cnt << "\n";
    Dinic dnc(ed+1, st, ed, edges);
    cnt -= dnc.ttl;
    cout << cnt << "\n";


    return 0;
}