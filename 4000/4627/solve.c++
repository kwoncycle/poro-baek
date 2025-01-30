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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    for(int ti=1; ti<=tt; ti++){
        int n, d, m; cin >> n >> d;
        vector<string> v(n), frog(n);
        for(int i=0; i<n; i++) cin >> v[i];
        m = v[0].size();
        for(int i=0; i<n; i++) cin >> frog[i];
        int cnt = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(frog[i][j] == 'L') cnt++;
            }
        }

        int fstart = 2*n*m, fend = 2*n*m+1;
        vector<Edge> edges;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(v[i][j]-'0'){
                    if(i-d < 0 or i+d>=n or j-d<0 or j+d>=m){
                        edges.push_back({2*(i*m+j)+1, fend, v[i][j]-'0', 0});
                    }

                    if(frog[i][j] == 'L'){
                        edges.push_back({fstart, 2*(i*m+j), 1, 0});
                    }

                    edges.push_back({2*(i*m+j), 2*(i*m+j)+1, v[i][j]-'0', 0});

                    for(int i1=-d; i1<=d; i1++){
                        for(int j1=-(d-abs(i1)); j1<=d-abs(i1); j1++){
                            if(i1 == 0 and j1 == 0) continue;
                            if(0<=i1+i and i1+i<n and 0<=j1+j and j1+j<m){
                                if(v[i1+i][j1+j]-'0'){
                                    edges.push_back({2*(i*m+j)+1, 2*((i1+i)*m+j1+j), v[i][j]-'0', 0});
                                }
                            }
                        }
                    }
                }
            }
        }

        Dinic flow(fend+1, fstart, fend, edges);
        int ans = 0;
        for(auto &[u,v,c1,c2]:flow.edges){
            //if(c2 > 0)
            //cout << u/m << u%m << " " << v/m << v%m << " " << c1 << " " << c2 << "\n";
            if(v == fend){
                
                ans += c2;
            }
        }

        cnt -= ans;

        cout << "Case #" << ti << ": ";
        if(cnt == 0){
            cout << "no lizard was left behind.\n";
        }
        else if(cnt == 1){
            cout << "1 lizard was left behind.\n";
        }
        else cout << cnt << " lizards were left behind.\n";
    }
    return 0;
}