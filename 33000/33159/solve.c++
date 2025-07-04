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

const int MX = 300055;

int n, q, clk;
int sparse[20][MX], depth[MX], order[MX], out[MX], DP1[MX];
ll DP[MX];
vector<int> graph[MX];

int ttl;

struct solve{
    solve(){
        cin >> n >> q;
        for(int i=0; i<n-1; i++){
            int a, b; cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        DFS(1, 0);
        for(int d=1; d<20; d++){
            for(int i=1; i<=n; i++){
                sparse[d][i] = sparse[d-1][sparse[d-1][i]];
            }
        }

        while(q--){
            query();
        }
    }

    void query(){
        int k; cin >> k;
        vector<int> v(k);
        vector<int> nodes;
        for(auto &i:v) cin >> i;
        if(k == 1){
            cout << "0\n"; return;
        }
        for(auto &i:v) nodes.push_back(i);

        sort(all(v), [&](int l, int r){
            return order[l] < order[r];
        });

        for(int i=0; i<k-1; i++){
            nodes.push_back(LCA(v[i], v[i+1]));
        }

        sort(all(nodes), [&](int l, int r){
            return order[l] < order[r];
        });

        nodes.erase(unique(all(nodes)), nodes.end());
        for(int i:nodes){
            graph[i].clear();
            DP[i] = 0;
            DP1[i] = 0;
        }
        for(int i:v) DP1[i] = 1;
        stack<int> stk;
        stk.push(nodes[0]);
        for(int i=1; i<(int)nodes.size(); i++){
            while(true){
                int o = stk.top();
                if(ispar(o, nodes[i])){
                    graph[o].push_back(nodes[i]);
                    break;
                }
                else stk.pop();
            }
            stk.push(nodes[i]);
        }

        for(int i:v){
            DP[nodes[0]] += depth[i] - depth[nodes[0]];
        }
        
        ttl = k;
        DFS1(nodes[0]);
        DFS_DP(nodes[0]);
        ll ans = DP[nodes[0]];
        for(int i:nodes){
            ans = min(ans, DP[i]);
        }
        cout << ans << "\n";
    }

    void DFS1(int node){ // for fill DP1
        for(int i:graph[node]){
            DFS1(i);
            DP1[node] += DP1[i];
        }
    }

    void DFS_DP(int node){
        for(int i:graph[node]){
            int d = depth[i] - depth[node];
            DP[i] = DP[node] + (ll)(ttl - DP1[i])*d - (ll)(DP1[i])*d;
            DFS_DP(i);
        }
    }

    void DFS(int node, int rt){
        clk++;
        order[node] = clk;
        for(int i:graph[node]){
            if(i == rt) continue;
            depth[i] = depth[node] + 1;
            sparse[0][i] = node;
            DFS(i, node);
        }
        out[node] = clk;
    }

    int LCA(int l, int r){
        if(depth[l] < depth[r]) swap(l, r);
        int o = depth[l] - depth[r];
        if(o)
        for(int d=19; d>=0; d--){
            if(o & (1<<d)){
                o -= (1<<d);
                l = sparse[d][l];
            }
        }
        if(l == r) return l;
        for(int d=19; d>=0; d--){
            if(sparse[d][l] != sparse[d][r]){
                l = sparse[d][l];
                r = sparse[d][r];
            }
        }
        l = sparse[0][l];
        return l;
    }

    bool ispar(int l, int r){ // is l ancestor of r?
        return order[l] <= order[r] and out[r] <= out[l];
    }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve S;
    return 0;
}