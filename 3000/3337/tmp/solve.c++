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

struct solve{
    int n, k;
    vector<int> graph; vector<vector<int>> graph_inv;
    bitset<500001> visited;
    stack<int> stk;
    vector<int> scc;
    vector<int> scc_idx;
    vector<int> deg;
    vector<int> dst;
    int ans = 0;
    solve(){
        cin >> n >> k;
        graph.resize(n+1); graph_inv.resize(n+1);
        scc.resize(n+1); scc_idx.resize(n+1);
        dst.resize(n+1, 0x3f3f3f);
        deg.resize(n+1);
        for(int i=0; i<n; i++){
            int a, b; cin >> a >> b;
            graph[a] = b;
            graph_inv[b].push_back(a);
            deg[b]++;
        }
        int u = 1;
        dst[u] = 0;
        for(int i=1; i<=k; i++){
            u = graph[u];
            dst[u] = min(i, dst[u]);
        }
        //fillstack
        for(int i=1; i<=n; i++){
            if(!visited[i]) {
                visited[i] = 1;
                dfs(i);
            }
        }
        visited.reset();
        while(!stk.empty()){
            int t = stk.top(); stk.pop();
            if(!visited[t]){
                visited[t] = 1;
                dfs_inv(t, t);
            }
        }

        for(int i=1; i<=n; i++){
            if(scc[scc_idx[i]] >= 2 and (int)graph_inv[i].size() > 1) reverse(i);
        }

        //cout << ans << "A\n";
        for(int i=1; i<=n; i++){
            if(scc[i] > 1 and scc_idx[i] == i){
                int i1 = i;
                vector<int> v;
                while(graph[i1] != i){
                    v.push_back(dst[i1]);
                    i1 = graph[i1];
                }
                v.push_back(dst[i1]);
                int nv = v.size();
                for(int j=0; j<nv; j++){
                    v[(j+1)%nv] = min(v[(j+1)%nv], v[j]+1);
                }
                for(int j=0; j<nv; j++){
                    v[(j+1)%nv] = min(v[(j+1)%nv], v[j]+1);
                }
                i1 = graph[i1];
                //for(int j:v) cout << (j<=k ? j : 0) << " "; cout << "\n";
                int id = 0;
                while(id < (int)v.size() and v[id] < k+1) id++;
                if(id == (int)v.size()) continue;
                rotate(v.begin(), v.begin()+id, v.end());
                int mn1 = 0, mn2 = 0x3f3f3f;
                for(int j=0; j<(int)v.size(); j++){
                    if(v[j] < k+1) continue;
                    mn1++;
                    j += k-1;
                }
                for(int jj=0; jj<(int)v.size()+1; jj++){
                    rotate(v.begin(), v.begin()+1, v.end());
                    if(v[0] >= k+1){
                        mn2 = 0;
                        for(int j=0; j<(int)v.size(); j++){
                            if(v[j] < k+1) continue;
                            mn2++;
                            j += k-1;
                        }
                        mn1 = min(mn1, mn2);
                    }
                }
                /*
                id = v.size();
                for(int j=v.size()-1; j>=max(0, (int)v.size()-(k-1)); j--){
                    if(v[j] >= k+1) id = j;
                }
                if(id != v.size()){
                    mn2 = 0;
                    rotate(v.begin(), v.begin()+id, v.end());
                    for(int j=0; j<(int)v.size(); j++){
                        if(v[j] < k+1) continue;
                        mn2++;
                        j += k-1;
                    }
                }*/
                //cout << min(mn1, mn2) << "\n";
                cout << mn1 << "\n";
                ans += min(mn1, mn2);
            }
        }
        cout << ans << "\n";
    }

    void dfs(int x){
        {
            int i = graph[x];
            if(!visited[i]){
                visited[i] = 1;
                dfs(i);
            }
        }
        stk.push(x);
    }

    void dfs_inv(int x, int loc){
        scc[loc]++;
        scc_idx[x] = loc;
        for(int i:graph_inv[x]){
            if(!visited[i]){
                visited[i] = 1;
                dfs_inv(i, loc);
            }
        }
    }

    void reverse(int x){
        int mn = k+1;
        int truth = 0;
        for(int i:graph_inv[x]){
            if(scc[scc_idx[i]] > 1) continue;
            truth = 1;
            reverse(i);
            mn = min(mn, dst[i]+1);
        }
        dst[x] = min(dst[x], mn);
        if(dst[x] > k and scc[scc_idx[x]] == 1){
            dst[x] = 1; ans++;
        }
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve s;
    return 0;
}