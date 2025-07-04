#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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
    ll u, v, cap, cur;
    Edge(ll _u, ll _v, ll _cap, ll _cur): u(_u), v(_v), cap(_cap), cur(_cur){}
};

bool operator < (const Edge l, const Edge r){return true;}

unordered_map<ll, int> R, L;
ll vals[10000], Ri[10000];

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

    void addEdge(Edge e){
        auto &[u, v, cap, cur] = e;
        int idx = edges.size();
        edges.push_back({u, v, cap, cur});
        edges.push_back({v, u, 0, 0});
        graph[u].push_back(idx);
        graph[v].push_back(idx + 1);
        reset(); BFS();
        ll x = DFS(start, 0x3f3f3f3f3f3fll);
        flow += x;
        return;
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
    while(tt--){
        memset(vals, 0, sizeof(vals)); memset(Ri, 0, sizeof(Ri));
        L.clear(); R.clear();

        int n; cin >> n;
        vector<ll> v(n), vt;
        for(auto &i:v) {
            cin >> i;
            vt.push_back(i);
        }
        sort(all(v)); sort(all(vt));
        vt.erase(unique(all(vt)), vt.end());
        int st = 0, ed = n*3+5;
        vector<Edge> edges;
        for(int i=n+1; i<=3*n+3; i++){
            edges.push_back(Edge(i, ed, 1, 0));
        }
        int id = n+1;
        
        for(ll i:vt){
            R[i] = id; L[i] = id-n;
            Ri[id] = i;
            edges.push_back(Edge(L[i], R[i], 1, 0));
            vals[L[i]] = i;
            id++;
        }
        Dinic D(ed+1, st, ed, edges);
        priority_queue<pair<ll, Edge>, vector<pair<ll, Edge>>, greater<pair<ll, Edge>>> pq;
        unordered_set<ll> used;
        for(ll i:v){
            int flw = D.flow;
            //cout << "st " << i << " added\n";
            D.addEdge(Edge(st, L[i], 1, 0));
            while(flw == D.flow and !pq.empty()){
                auto &[_, e] = pq.top();
                //cout << vt[e.u-1] << " " << Ri[e.v] << " added\n";
                D.addEdge(e);
                pq.pop();
            }
            assert(flw != D.flow);
            for(int i1:D.graph[D.end]){
                if(D.edges[i1-1].cap == D.edges[i1-1].cur){
                    used.insert(Ri[D.edges[i1-1].u]);
                }
            }
            for(ll j:vt){
                if(used.find(vals[L[j]]) != used.end()){
                    while(used.find(vals[L[j]]) != used.end()){
                        vals[L[j]] += j;
                        if(R.find(vals[L[j]]) == R.end()){
                            R[vals[L[j]]] = id;
                            Ri[id] = vals[L[j]];
                            id++;
                            assert(id < ed);
                        }
                        pq.push({vals[L[j]], Edge(L[j], R[vals[L[j]]], 1, 0)});
                    }
                }
            }
        }
        ll mx = 0;
        for(int i:D.graph[D.end]){
            if(D.edges[i-1].cap == D.edges[i-1].cur){
                mx = max(mx, Ri[D.edges[i-1].u]);
            }
        }
        cout << mx << "\n";
    }
    return 0;
}