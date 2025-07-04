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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int g, l; cin >> g >> l;

    vector<int> G(l, -1);
    vector<vector<int>> ban(l);
    vector<int> cnt(26, 0), det(26, -1);
    for(int i=0; i<g-1; i++){
        string s, ans; 
        cin >> s >> ans;
        vector<int> C(26);
        for(int j=0; j<l; j++){
            if(ans[j] == 'G' or ans[j] == 'Y') C[s[j]-'a']++;
        }
        for(int j=0; j<26; j++){
            cnt[j] = max(cnt[j], C[j]);
        }
        for(int j=0; j<l; j++){
            if(ans[j] == 'G'){
                G[j] = s[j]-'a';
            }
            else if(ans[j] == 'Y'){
                ban[j].push_back(s[j] - 'a');
            }
            else{
                det[s[j] - 'a'] = C[s[j] - 'a'];
                ban[j].push_back(s[j] - 'a');
            }
        }
    }

    vector<Edge> edges;
    int st = 26+l, ed = 26+l+1, ST = ed+1, ED = ed+2;
    // 0..25,  26+0 .. 26+l-1,
    vector<int> demand(ED+1);
    demand[st] = -l, demand[ed] = l;
    for(int i=0; i<26; i++){
        demand[st] += cnt[i]; demand[i] -= cnt[i];
        if(det[i] == -1){
            edges.push_back(Edge(st, i, l - cnt[i], 0));
        }
    }
    for(int i=0; i<l; i++){
        sort(all(ban[i]));
        ban[i].erase(unique(all(ban[i])), ban[i].end());
        if(G[i] != -1){
            edges.push_back(Edge(G[i], i+26, 1, 0));
        }
        else{
            int id = 0;
            for(int j=0; j<26; j++){
                if(id < (int)ban[i].size() and ban[i][id] == j){
                    id++; continue;
                }
                edges.push_back(Edge(j, i+26, 1, 0));
            }
        }
        edges.push_back(Edge(i+26, ed, 1, 0));
    }

    for(int i=0; i<=ed; i++){
        if(demand[i] < 0){
            edges.push_back(Edge(ST, i, -demand[i], 0));
        }
        else if(demand[i] > 0){
            edges.push_back(Edge(i, ED, demand[i], 0));
        }
    }

    string ans(l, '8');
    Dinic D(ED+1, ST, ED, edges);
    for(auto &[i,j,cap,cur]:D.edges){
        if(0<=i and i<26 and 26<=j and j<st and cap == 1 and cur == 1){
            ans[j-26] = 'a' + i;
        }
    }
    for(char c:ans) assert(c != '8');
    cout << ans << "\n";
    return 0;
}