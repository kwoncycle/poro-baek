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

int n, m, k, chk[1004], par[1004]; 
ll v[1004], DP[1004];
vector<array<ll, 3>> edges;
vector<int> who[1004];
vector<ll> turn[1004];
vector<pll> graph[1004];


struct DSU{
    int par[1004];
    DSU(int _n){
        for(int i=1; i<=_n; i++) par[i] = i;
    }
    int Find(int x){
        if(par[x] == x) return x;
        return par[x] = Find(par[x]);
    }
    bool Union(int l, int r){
        l = Find(l); r = Find(r);
        if(l == r) return false;
        par[l] = r; return true;
    }
} D(1000);

struct solve{
    solve(){
        cin >> n >> m >> k;
        for(int i=1; i<=n; i++) cin >> v[i];
        for(int i=0; i<m; i++){
            ll x,y,z; cin >> x >> y >> z;
            edges.push_back({z, x, y});
            D.Union(x, y);
        }
        vector<int> partition;
        for(int i=1; i<=n; i++){
            if(D.Find(i) == i){
                partition.push_back(i);
            }
        }
        for(int i=0; i<(int)partition.size()-1; i++){
            edges.push_back({0x3f3f3f3f3f3fll, partition[i], partition[i+1]});
        }

        for(int i=0; i<=n; i++) D.par[i] = i;
        sort(all(edges));
        ll cost = 0;

        for(auto &[z,x,y]:edges){
            if(D.Union(x, y)){
                graph[x].push_back({y, z});
                graph[y].push_back({x, z});
                cost += z;
            }
        }
        
        int id = 1;
        for(int i=1; i<=n; i++){
            if(v[i] <= v[id]) id = i;
        }
        cost += v[id];
        chk[id] = 1;
        DFS(id, 0);
        k--;
        while(k--){
            ll dl = 0, id = 0;
            for(int i=1; i<=n; i++){
                if(chk[i]) continue;
                ll delta = v[i] - DP[i];
                if(dl > delta){
                    dl = delta;
                    id = i;
                }
            }
            if(!id) break;
            chk[id] = 1;
            cost += dl;
            while(DP[par[id]] == DP[id]) id = par[id];
            for(int i=0; i<(int)graph[id].size(); i++){
                if(graph[id][i].X == par[id]){
                    swap(graph[id][i], graph[id].back());
                    graph[id].pop_back(); break;
                }
            }
            for(int i=0; i<(int)graph[par[id]].size(); i++){
                if(graph[par[id]][i].X == id){
                    swap(graph[par[id]][i], graph[par[id]].back());
                    graph[par[id]].pop_back(); break;
                }
            }

            for(int i=1; i<=n; i++){
                DP[i] = 0; par[i] = 0;
            }
            for(int i=1; i<=n; i++){
                if(chk[i]) DFS(i, 0);
            }
        }
        if(cost >= 0x3f3f3f3f3f3fll - 12312) cout << "-1\n";
        else cout << cost << "\n";
    }
    void DFS(int node, int rt){
        for(auto &[i, d]:graph[node]){
            if(i == rt) continue;
            DP[i] = max(DP[node], d);
            par[i] = node;
            DFS(i, node);
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve S;

    return 0;
}