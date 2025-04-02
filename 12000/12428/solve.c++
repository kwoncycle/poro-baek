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

#define A3 array<int,3>
class djs
{
    int k, n, m;
    vector<vector<vector<A3>>> par;
 
public:
    djs(int _k, int _n, int _m) : n(_n), m(_m), k(_k) {
        par = vector<vector<vector<A3>>>(k, vector<vector<A3>>(n, vector<A3>(m)));
        for(int i=0; i<k; i++){
            for(int j=0; j<n; j++){
                for(int ki=0; ki<m; ki++){
                    par[i][j][ki] = {i,j,ki};
                }
            }
        }
    }
 
    A3 find(A3 v) {
        if(par[v[0]][v[1]][v[2]] == v) return v;
        else return par[v[0]][v[1]][v[2]] = find(par[v[0]][v[1]][v[2]]);
    }
 
    bool Union(A3 x, A3 y) {
        A3 px = find(x);
        A3 py = find(y);
 
        if(px == py) return false;
 
        par[px[0]][px[1]][px[2]] = py;
        return true;
    }
};
// Usage: djs DJS(n)

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    for(int tc=1; tc<=tt; tc++){
        int n, m, k; cin >> n >> m >> k;
        vector<vector<string>> v(k, vector<string>(n));
        for(int i=0; i<k; i++){
            for(int j=0; j<n; j++) cin >> v[i][j];
        }

        djs DJS(k, n, m);
        int roomid = 1;
        map<A3, int> mp;
        vector<int> room_odd, room_even;
        for(int fl=0; fl<k; fl++){
            for(int i=0; i<n-1; i++){
                for(int j=0; j<m; j++){
                    if(v[fl][i][j] == '.' and v[fl][i+1][j] == '.') DJS.Union({fl,i,j}, {fl,i+1,j});
                }
            }
            for(int i=0; i<n; i++){
                for(int j=0; j<m-1; j++){
                    if(v[fl][i][j] == '.' and v[fl][i][j+1] == '.') DJS.Union({fl,i,j}, {fl,i,j+1});
                }
            }
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++){
                    if(v[fl][i][j] == '.' and DJS.find({fl,i,j}) == A3{fl,i,j}){
                        mp[{fl,i,j}] = roomid; 
                        if(fl%2 == 0) room_even.push_back(roomid);
                        else room_odd.push_back(roomid);
                        roomid++;
                    }
                }
            }
        }

        int st = 0, ed = roomid;
        vector<Edge> edges;
        set<pii> set_edge;

        for(int fl=0; fl<k-1; fl++){
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++){
                    if(v[fl][i][j] == '.' and v[fl+1][i][j] == '.'){
                        if(fl%2 == 0) set_edge.insert(pii{mp[DJS.find({fl,i,j})], mp[DJS.find({fl+1,i,j})]});
                        else set_edge.insert(pii{mp[DJS.find({fl+1,i,j})], mp[DJS.find({fl,i,j})]});
                    }
                }
            }
        }
        for(auto [i,j]: set_edge){
            edges.push_back(Edge(i, j, 1, 0));
        }
        for(int i:room_even) edges.push_back(Edge(st, i, 1, 0));
        for(int i:room_odd) edges.push_back(Edge(i, ed, 1, 0));
        int room_ttl = room_even.size() + room_odd.size();
        Dinic D(ed+1, st, ed, edges);
        room_ttl -= D.flow;
        cout << "Case #" << tc << ": " << room_ttl << "\n";
    }
    return 0;
}