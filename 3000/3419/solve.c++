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

    vector<int> BFS1(){
        vector<int> chk(n, 0);
        queue<int> q;
        for(int id:graph[start]){
            auto [u, v, cap, cur] = edges[id];
            if(cap != cur){
                chk[v] = 1;
                q.push(v);
            }
        }
        while(!q.empty()){
            ll o = q.front(); q.pop();
            for(ll i:graph[o]){
                if(edges[i].cap <= edges[i].cur) continue;
                if(!chk[edges[i].v]){
                    chk[edges[i].v] = 1;
                    q.push(edges[i].v);
                }
            }
        }
        return chk;
    }

    vector<int> BFS2(){
        vector<int> chk(n, 0);
        queue<int> q;
        for(int id:graph[end]){
            auto [u, v, cap, cur] = edges[id];
            if(cap == cur){
                chk[v] = 1;
                q.push(v);
            }
        }
        while(!q.empty()){
            ll o = q.front(); q.pop();
            for(ll i:graph[o]){
                if(edges[i].cap > edges[i].cur) continue;
                if(!chk[edges[i].v]){
                    chk[edges[i].v] = 1;
                    q.push(edges[i].v);
                }
            }
        }
        return chk;
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
int id[105][105];
struct solve{
    string s[105], ans[105];
    
    solve(){
        int n, m; cin >> n >> m;
        if(!(n+m)) exit(0);
        for(int i=0; i<n; i++) {
            cin >> s[i]; ans[i].resize(m);
        }
        int i0 = 1, i1 = n*m/2 + 3;

        vector<Edge> edges;
        int st = 0, ed = n*m + 10;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if((i+j)%2 == 0){
                    id[i][j] = i0; i0++;
                    edges.push_back(Edge(st, id[i][j], 1, 0));
                }
                else{
                    id[i][j] = i1; i1++;
                    edges.push_back(Edge(id[i][j], ed, 1, 0));
                }
            }
        }


        for(int i=0; i<n; i++){
            for(int j=0; j<m-1; j++){
                if(s[i][j] == '.' and s[i][j+1] == '.'){
                    if((i+j)%2 == 0) edges.push_back(Edge(id[i][j], id[i][j+1], 1, 0));
                    else edges.push_back(Edge(id[i][j+1], id[i][j], 1, 0));
                }
            }
        }

        for(int i=0; i<n-1; i++){
            for(int j=0; j<m; j++){
                if(s[i][j] == '.' and s[i+1][j] == '.'){
                    if((i+j)%2 == 0) edges.push_back(Edge(id[i][j], id[i+1][j], 1, 0));
                    else edges.push_back(Edge(id[i+1][j], id[i][j], 1, 0));
                }
            }
        }

        Dinic D(ed+1, st, ed, edges);
        int flowcur = D.flow;
        vector<int> V = D.BFS1();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if((i+j)%2 == 0){
                    if(s[i][j] == '.'){
                        if(V[id[i][j]] == 1) ans[i][j] = 'B';
                        else ans[i][j] = 'A';
                    }
                    else ans[i][j] = 'X';
                }
                //else ans[i][j] = 'C';
            }
        }
        V = D.BFS2();
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if((i+j)%2 == 1){
                    if(s[i][j] == '.'){
                        if(V[id[i][j]] == 1) ans[i][j] = 'B';
                        else ans[i][j] = 'A';
                    }
                    else ans[i][j] = 'X';
                }
            }
        }
        for(int i=0; i<n; i++) cout << ans[i] << "\n";
        cout << "\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        solve S;
    }
}