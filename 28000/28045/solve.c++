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
int n1;
vector<vector<int>> t1;
int n2;
vector<vector<int>> t2;
vector<int> par1(104), par2(104), depth1(104), depth2(104);
vector<vector<int>> under1, under2;
vector<vector<int>> validlist;


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

void DFS1(int i, int t){
    for(int j:t1[i]){
        if(t == j) continue;
        par1[j] = i;
        under1[i].push_back(j);
        depth1[j] = depth1[i] + 1;
        DFS1(j, i);
    }
}

void DFS2(int i, int t){
    for(int j:t2[i]){
        if(t == j) continue;
        par2[j] = i;
        under2[i].push_back(j);
        depth2[j] = depth2[i] + 1;
        DFS2(j, i);
    }
}


bool valid_pair(int v1, int v2){
    if(depth1[v1] != depth2[v2]) return false;
    if(under2[v2].empty()) {
        return true;
    }
    vector<Edge> edges;
    set<int> s;
    map<int, int> mp; vector<int> id2i;
    int id = 0;
    int st = (int)under2[v2].size() + (int)under1[v1].size() + 1, ed = st + 1;
    for(int j:under2[v2]) {
        mp[j+300] = id; id++; id2i.push_back(j+300);
        s.insert(j);
        edges.push_back({mp[j+300], ed, 1, 0});
    }
    for(int i:under1[v1]){
        mp[i] = id; id++; id2i.push_back(i);
        edges.push_back({st, mp[i], 1, 0});
        for(int t:validlist[i]){
            if(s.find(t) != s.end()){
                edges.push_back({mp[i], mp[t+300], 1, 0});
            }
        }
    }
    //for(auto &[u,v,c1,c2]:edges) cout << u << " " << v << " " << c1 << " " << c2 << "\n";
    
    Dinic dinic(ed+1, st, ed, edges);
    int cnt = 0;
    for(auto &[u,v,c1,c2]:dinic.edges){
        if(u == st) {
            //cout << u << " " << v << " " << c1 << " " << c2 << "\n";
            cnt += c2;
        }
    }
    //cout << v1 << " " << v2 << "= " << cnt << "\n";
    if(cnt == (int)under2[v2].size()) return true;
    else return false;
}

bool solve(int rt){
    //cout << "-====" << rt << "===\n";
    vector<vector<int>> d1(105), d2(105);
    for(int i=1; i<=n1; i++){
        d1[depth1[i]].push_back(i);
    }
    for(int i=1; i<=n2; i++){
        d2[depth2[i]].push_back(i);
    }
    for(int d=100; d>=0; d--){
        for(int i:d1[d]) for(int j:d2[d]){
            //cout << i << " " << j << "\n";
            bool b = valid_pair(i, j);
            if(b) validlist[i].push_back(j);
        }
    }
    
    //for(int i=1; i<=n1; i++){
        //cout << i << ": "; for(int j:validlist[i]) cout << j << " "; cout << "\n";
    //}
    if(valid_pair(rt, 1)) return true;
    return false;
}


int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    cin >> n1;
    t1.resize(n1+1);
    for(int i=0; i<n1-1; i++){
        int a, b; cin >> a >> b;
        t1[a].push_back(b);
        t1[b].push_back(a);
    }
    cin >> n2;
    t2.resize(n2+1);
    for(int i=0; i<n2-1; i++){
        int a, b; cin >> a >> b;
        t2[a].push_back(b);
        t2[b].push_back(a);
    }
    if(n2 == 1){
        cout << "Y\n"; return 0;
    }
    if(n1 == 1){
        cout << "N\n"; return 0;
    }
    
    under2 = vector<vector<int>>(n2+1);
    par2[1] = -1;
    DFS2(1, -1);
    for(int i=1; i<=n1; i++){
        under1 = vector<vector<int>>(n1+1);
        depth1 = vector<int>(n1+1, 0);
        validlist = vector<vector<int>>(n1+1);
        par1[i] = -1;
        DFS1(i, -1);
        if(solve(i)) {
            cout << "Y\n";
            return 0;
        }

    }
    cout << "N\n";

    return 0;
}