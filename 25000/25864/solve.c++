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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

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

int n, m; 
int p1(int i, int j){
    return 2*(i*m+j);
}

int p2(int i, int j){
    return 2*(i*m+j) + 1;
}

bool isin(int i, int j){
    return (0<=i) and (i<n) and (0<=j) and (j<m);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    vector<string> v(n);
    for(int i=0; i<n; i++) cin >> v[i];

    int st = p1(n, 0), ed = p2(n, 0);
    vector<Edge> edges;
    vector<pii> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            
            if(v[i][j] == 'B'){
                edges.push_back({st, p1(i, j), 1, 0, 0});
            }
            if(v[i][j] == 'C'){
                edges.push_back({st, p1(i, j), 1, 0, 0});
            }
            if(v[i][j] == 'F'){
                edges.push_back({p1(i,j), p2(i,j), 2, 0, 0});
                edges.push_back({p2(i, j), ed, 2, 0, 0});
            }
            else edges.push_back({p1(i,j), p2(i,j), 1, 0, 0});
            for(auto &[pi, pj]:dir){
                if(isin(i+pi, j+pj)){
                    
                    if(v[i+pi][j+pj] == '.' or v[i+pi][j+pj] == 'F'){//cout << i << " " << j << " " << p2(i, j) << "|HI\n";
                        edges.push_back({(ll)p2(i, j), (ll)p1(i+pi, j+pj), 1, 0, 1});
                    }
                }
            }
        }
    }

    //for(auto [i,j,k,l,t]:edges) cout << i << " " << j << " " << k << " " << l << " " << t << "\n";

    MCMF mcmf(ed+1, st, ed, edges);
    int cnt = 0;
    for(auto [i,j,k,l,t]:mcmf.edges){
        if(i == st and k == l) cnt++;// cout << i << " " << j << " " << k << " " << l << "\n";
    }
    if(cnt == 2) cout << mcmf.mincost << "\n";
    else cout << "-1\n";
    return 0;
}