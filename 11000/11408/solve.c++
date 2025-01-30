#include <bits/stdc++.h>
using namespace std;
 
#define pii pair<int,int>
#define pll pair<int,int>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

struct Edge{
    int u, v, cap, cur, cost;
    Edge(int _u, int _v, int _cap, int _cur, int _cost): u(_u), v(_v), cap(_cap), cur(_cur), cost(_cost){}
};


struct MCMF{ // min cost max flow
    vector<vector<int>> graph;
    vector<Edge> edges;
    int n, start, end, mincost = 0; // |node|, flow start, flow end
    vector<int> dst, queue_cnt, prev;
    bool signal;

public:
    MCMF(int _n, int _start, int _end, vector<Edge> &_Edge) : n(_n), start(_start), end(_end){
        graph = vector<vector<int>>(n+1);
        edges = vector<Edge>((int)_Edge.size()*2, {0,0,0,0,0});
        int idx = 0;
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
            int a = SPFA(); mincost += a;
        }
    }

    int SPFA(){
        fill(dst.begin(), dst.end(), 0x3f3f3f3f);
        fill(prev.begin(), prev.end(), -1);
        
        queue<int> q;
        dst[start] = 0;
        q.push(start);
        queue_cnt[start]++;

        while(!q.empty()){
            int u = q.front(); q.pop();
            queue_cnt[u]--;
            for(int i:graph[u]){
                if(edges[i].cap <= edges[i].cur) continue;
                int v = edges[i].v;
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

        int flow = 0x3f3f3f3f;
        for(int i=end; i!=start; i=edges[prev[i]].u){
            flow = min(flow, edges[prev[i]].cap - edges[prev[i]].cur);
        }

        int cost_total = 0;
        for(int i=end; i!=start; i=edges[prev[i]].u){
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
    int n, m; cin >> n >> m;
    vector<Edge> edges;
    int st = 0, ed = n+m+1;
    for(int i=1; i<=n; i++){
        int o; cin >> o;
        while(o--){
            int w, c; cin >> w >> c;
            edges.push_back({i, w+n, 1, 0, c});
        }
    }

    for(int i=1; i<=n; i++){
        edges.push_back({st, i, 1, 0, 0});
    }
    for(int i=n+1; i<=n+m; i++){
        edges.push_back({i, ed, 1, 0, 0});
    }

    MCMF mcmf(ed+1, st, ed, edges);
    int cnt = 0;
    for(auto &[u,v,c1,c2,c3]:mcmf.edges){
        if(u == st) {
            cnt += c2;
        }
    }
    cout << cnt << "\n";
    cout << mcmf.mincost << "\n";
    return 0;
}