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
    Dinic(ll _n, ll _start, ll _end, vector<Edge> &_Edge, int k) : n(_n), start(_start), end(_end){
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
                if(flow >= k) break;
            }
            if(flow >= k) break;
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

vector<Edge> edges;
void addE(int l, int r){
    // 2l: l in, 2l+1 : l out
    if(r != 1 and l != 2) edges.push_back(Edge(2*l+1, 2*r, 1, 0));
    if(r != 2 and l != 1) edges.push_back(Edge(2*r+1, 2*l, 1, 0));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    for(int tc=1; ; tc++){
        int k, n; cin >> k >> n;
        if(k + n == 0) break;
        edges.clear();
        for(int i=3; i<=n; i++){
            edges.push_back(Edge(2*i, 2*i + 1, 1, 0));
        }
        for(int i=0; i<=n; i++){
            string s; getline(cin, s);
            if(!i) continue;
            int j = 0;
            for(char c:s){
                if(c == ' '){
                    if(i < j) addE(i, j);
                    j = 0;
                }
                else{
                    j *= 10; j += c - '0';
                }
            }
            if(i < j) addE(i, j);
        }
        int st = 1*2 + 1, ed = 2*2;
        Dinic D(2*n + 2, st, ed, edges, k);
        vector<int> outt;
        for(auto &[u, v, cur, cap]:D.edges){
            if(u == st and cur == cap) outt.push_back(v);
        }

        cout << "Case " << tc << ":\n";
        if(outt.size() < k) cout << "Impossible\n";
        else{
            for(int id=0; id<k; id++){
                cout << "1 ";
                int cur = outt[id];
                while(cur != ed){
                    cout << cur/2 << " ";
                    cur++;
                    for(int i:D.graph[cur]){
                        if(D.edges[i].cap == 1 and D.edges[i].cur == 1){
                            cur = D.edges[i].v; break;
                        }
                    }
                }
                cout << "2\n";
            }
        }
        cout << "\n";
    }
    return 0;
}