#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<int,int>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
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

    ll SPFA(){
        fill(dst.begin(), dst.end(), 0x3f3f3f3f3f3f3f);
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

        ll flow = 0x3f3f3f3f3f3f3f;
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, w, t; cin >> n >> w >> t;
    int st = 0, O = n+1, L = n+2, S = n+3, ed = n+4;
    vector<Edge> edges;

    for(int i=1; i<=n; i++){
        ll s, l; cin >> s >> l;
        if(s < l) l = s;

        edges.push_back(Edge(st, i, 1, 0, 0));
        edges.push_back(Edge(i, O, 1, 0, 0));
        edges.push_back(Edge(i, L, 1, 0, l));
        edges.push_back(Edge(i, S, 1, 0, s));
    }

    edges.push_back(Edge(O, ed, t, 0, 0));
    edges.push_back(Edge(L, ed, w, 0, 0));
    edges.push_back(Edge(S, ed, n-t-w, 0, 0));
    MCMF ans(ed+1, st, ed, edges);
    cout << ans.mincost << "\n";
}