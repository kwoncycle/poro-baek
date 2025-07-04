#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
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

struct CHT{
    vector<pii> stk; // (a, b)
    void insert(pii p){
        while(stk.size() >= 1 and stk.back().X == p.X and stk.back().Y > p.Y) stk.pop_back();
        if(stk.size() >= 1 and stk.back().X == p.X and stk.back().Y < p.Y) return;
        while(stk.size() >= 2 and cx(stk[stk.size()-2], p) > cx(stk[stk.size()-1], p)) stk.pop_back();
        stk.push_back(p);
    }
    double cx(pii p1, pii p2){
        return (double)(p2.Y - p1.Y) / (double)(p1.X - p2.X);
    }
    ll query(ll x){
        if(stk.size() == 1) return stk[0].X * x + stk[0].Y;
        int st = 0, ed = stk.size() - 1;
        if(x < cx(stk[st], stk[st + 1])){
            return stk[0].X * x + stk[0].Y;
        }
        while(st + 1 < ed){
            int md = (st + ed) / 2;
            if(cx(stk[md], stk[md + 1]) < x) st = md;
            else ed = md;
        }
        return stk[st + 1].X * x + stk[st + 1].Y;
    }
};

struct DSU{
    int n;
    vector<int> par;
    DSU(int _n) : n(_n){
        par.resize(n+1);
        for(int i=0; i<=n; i++) par[i] = i;
    }
    int find(int u){
        if(par[u] == u) return u;
        return par[u] = find(par[u]);
    }
    bool Union(int u, int v){
        u = find(u); v = find(v);
        if(u == v) return false;
        par[u] = v;
        return true;
    }
};

const int MX = 1000005;
vector<int> graph[MX];
vector<int> par(MX, -1);
int order[MX], up[MX], cnt[MX];
int clk = 0;

ll A[MX], B[MX], C[MX];

set<ll> st;
set<ll> cutedge;
DSU D(MX);

ll C2(ll l){
    return l*(l-1)/2;
}

void DFS(int node){
    clk++; order[node] = clk;
    up[node] = order[node];
    for(int i:graph[node]){
        if(par[node] == i) continue;
        if(order[i] == 0){
            par[i] = node;
            DFS(i);
            if(up[i] > order[node]) {
                if(st.find(((ll)i << 32) ^ (ll)node) == st.end()){
                    cutedge.insert(((ll)i << 32) ^ (ll)node);
                }
            }
            up[node] = min(up[node], up[i]);
        }
        else up[node] = min(up[node], order[i]);
    }
}

ll N1;

ll ans = 0x3f3f3f3f3f3f3f3fll;
void DFS1(int node){
    C[node] = cnt[node];
    vector<int> child;
    for(int i:graph[node]){
        if(i == par[node]) continue;
        par[i] = node;
        DFS1(i);
        C[node] += C[i];
    }
    
    A[node] = C2(C[node]);
    for(int i:graph[node]){
        if(i == par[node]) continue;
        child.push_back(i);
        A[node] = min(A[node], C2(C[node] - C[i]) + A[i]);
    }

    sort(all(child), [&](int l, int r){
        return C[l] > C[r];
    });

    if(child.size() <= 1) {
        if(node == D.find(0)) ans = min(ans, A[node]);
    }
    else{
        CHT CH;
        ll T = 2*N1 - 1;
        for(int i:child){
            if(i != child[0]){
                ll U = CH.query(C[i]) + C[i]*C[i] - T*C[i] + 2*A[i] + N1*(N1 - 1);
                assert(U%2 == 0);
                U /= 2;
                ans = min(ans, U);
            }
            CH.insert(pii(2*C[i], C[i]*C[i] - T*C[i] + 2*A[i]));
        }
    }
    
}



extern long long max_diversity(int n, int m, vector<int> U, vector<int> V){
    N1 = n;
    for(int i=0; i<m; i++){
        graph[U[i]].push_back(V[i]);
        graph[V[i]].push_back(U[i]);
    }
    for(int i=0; i<n; i++) {
        sort(all(graph[i]));
        for(int j=0; j<(int)graph[i].size()-1; j++){
            if(graph[i][j] == graph[i][j+1]) st.insert(((ll)i<<32)^(ll)graph[i][j]);
        }
        graph[i].erase(unique(all(graph[i])), graph[i].end());
    }
    DFS(0);
    for(int i=0; i<m; i++){
        if(cutedge.find(((ll)U[i] << 32) ^ (ll)V[i]) == cutedge.end() and cutedge.find(((ll)V[i] << 32) ^ (ll)U[i]) == cutedge.end()){
            D.Union(U[i], V[i]);
        }
    }

    for(int i=0; i<n; i++){
        cnt[D.find(i)]++;
        graph[i].clear();
    }

    for(ll i1:cutedge){
        ll u = i1 >> 32, v = i1 % (1ll<<32);
        u = D.find(u); v = D.find(v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    par = vector<int>(MX, -1);
    
    DFS1(D.find(0));

    return C2(n) - ans;
}
    
    
// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cout.tie(0);
//     int N, M;
//     cin >> N >> M;
    
//     std::vector<int> U(M), V(M);
//     for (int i=0;i<M;i++){
//         cin >> U[i] >> V[i];
//     }
    
//     long long S = max_diversity(N, M, U, V);
//     cout << S << "\n";
// }
    