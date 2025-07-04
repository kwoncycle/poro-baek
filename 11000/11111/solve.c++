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
    ll u, v, cap, cur, cost;
    Edge(ll _u, ll _v, ll _cap, ll _cur, ll _cost): u(_u), v(_v), cap(_cap), cur(_cur), cost(_cost){}
};


struct MCMF{ // min cost max flow
    vector<vector<ll>> graph;
    vector<Edge> edges;
    ll n, start, end, mincost = 0; // |node|, flow start, flow end
    vector<ll> dst, queue_cnt, prev;
    bool signal;

public:
    MCMF(ll _n, ll _start, ll _end, vector<Edge> &_Edge) : n(_n), start(_start), end(_end){
        graph = vector<vector<ll>>(n+1);
        edges = vector<Edge>((ll)_Edge.size()*2, {0,0,0,0,0});
        ll idx = 0;
        dst.resize(n+1);
        prev.resize(n+1);
        queue_cnt.resize(n+1);
        for(auto &[u, v, cap, cur, cost]:_Edge){
            edges[idx] = {u, v, cap, cur, cost};
            edges[idx + 1] = {v, u, 0, 0, -cost};
            graph[u].push_back(idx);
            graph[v].push_back(idx + 1);
            idx += 2;
        }
        signal = true;
        while(signal){
            ll a = SPFA(); mincost += a;
        }
    }

    void addEdge(Edge &e){
        auto [u, v, cap, cur, cost] = e;
        int idx = edges.size();
        edges.push_back({u, v, cap, cur, cost});
        edges.push_back({v, u, 0, 0, -cost});
        graph[u].push_back(idx);
        graph[v].push_back(idx + 1);
        idx += 2;
        signal = true;
        while(signal){
            ll a = SPFA(); mincost += a;
        }
    }

    ll SPFA(){
        fill(dst.begin(), dst.end(), 0x3f3f3f3f);
        fill(prev.begin(), prev.end(), -1);
        
        queue<ll> q;
        dst[start] = 0;
        q.push(start);
        queue_cnt[start]++;

        while(!q.empty()){
            ll u = q.front(); q.pop();
            queue_cnt[u]--;
            for(ll i:graph[u]){
                if(edges[i].cap <= edges[i].cur) continue;
                ll v = edges[i].v;
                if(dst[u] + edges[i].cost < dst[v]){
                    dst[v] = dst[u] + edges[i].cost;
                    prev[v] = i;
                    if(!queue_cnt[v]){
                        q.push(v);
                        queue_cnt[v]++;
                    }
                }
            }
        }
        if(prev[end] == -1) {
            signal = false;
            return 0;
        }

        ll flow = 0x3f3f3f3f;
        for(ll i=end; i!=start; i=edges[prev[i]].u){
            flow = min(flow, edges[prev[i]].cap - edges[prev[i]].cur);
        }

        ll cost_total = 0;
        for(ll i=end; i!=start; i=edges[prev[i]].u){
            cost_total += flow*edges[prev[i]].cost;
            edges[prev[i]].cur += flow;
            edges[prev[i]^1].cur -= flow;
        }

        return cost_total;
    }
};

string v[100];

int convert(int x, int y){
    return x*52 + y + 1;
}

int val[5][5] = {
    {10, 8, 7, 5, 1},
    { 8, 6, 4, 3, 1},
    { 7, 4, 3, 2, 1},
    { 5, 3, 2, 2, 1},
    { 1, 1, 1, 1, 0}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for(int i=0; i<n; i++) cin >> v[i];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j] == 'F') v[i][j] = 'E';
        }
    }
    vector<Edge> edges;
    int st = 0, ed = convert(50, 0), ed1 = ed + 1;
    for(int i=0; i<n; i++){
        for(int j=0; j<m-1; j++){
            if((i+j)%2){
                edges.push_back(Edge(convert(i, j), convert(i, j+1), 1, 0, 10 - val[v[i][j]-'A'][v[i][j+1]-'A']));
            }
            else{
                edges.push_back(Edge(convert(i, j+1), convert(i, j), 1, 0, 10 - val[v[i][j]-'A'][v[i][j+1]-'A']));
            }
        }
    }
    for(int i=0; i<n-1; i++){
        for(int j=0; j<m; j++){
            if((i+j)%2){
                edges.push_back(Edge(convert(i, j), convert(i+1, j), 1, 0, 10 - val[v[i][j]-'A'][v[i+1][j]-'A']));
            }
            else{
                edges.push_back(Edge(convert(i+1, j), convert(i, j), 1, 0, 10 - val[v[i][j]-'A'][v[i+1][j]-'A']));
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if((i+j)%2){
                edges.push_back(Edge(st, convert(i, j), 1, 0, 0));
            }
            else{
                edges.push_back(Edge(convert(i, j), ed, 1, 0, 0));
            }
        }
    }
    MCMF M(ed1 + 1, st, ed1, edges);
    ll ans = 0;
    for(int fl = 0; fl < n*m; fl++){
        Edge E = Edge(ed, ed1, 1, 0, 0);
        M.addEdge(E);
        // edges.push_back(Edge(ed, ed1, 1, 0, 0));
        // MCMF M(ed1 + 1, st, ed1, edges);
        ll ttl = 0;
        for(auto &[u, v, cap, cur, cost]:M.edges){
            if(v == ed1) ttl += cur;
        }
        ans = max(ans, ttl*10 - M.mincost);
    }
    cout << ans << "\n";
    return 0;
}