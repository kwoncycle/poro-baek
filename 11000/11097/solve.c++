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
    int n;
    vector<string> v;
    stack<int> stk;
    vector<int> visited;
    vector<int> scc;
    vector<vector<int>> sccvi;
    vector<pii> ans;
    vector<int> deg;
    solve(){
        cin >> n;
        v.resize(n); visited.resize(n, 0); scc.resize(n, 0); sccvi.resize(n); deg.resize(n);
        for(int i=0; i<n; i++) cin >> v[i];

        for(int i=0; i<n; i++){
            if(!visited[i]){
                visited[i] = 1;
                dfs(i);
            }
        }

        fill(visited.begin(), visited.end(), 0);
        while(!stk.empty()){
            int i = stk.top(); stk.pop();
            if(!visited[i]){
                visited[i] = 1;
                dfs_inv(i, i);
            }
        }

        for(int i=0; i<n; i++){
            if(sccvi[i].size() >= 2){
                int ns = sccvi[i].size();
                for(int j=0; j<ns; j++){
                    ans.push_back({sccvi[i][j], sccvi[i][(j+1)%ns]});
                }
            }
        }
        
        for(int i=0; i<n; i++){
            if(scc[i] != i){
                for(int j=0; j<n; j++){
                    v[i][j] = '0'; v[j][i] = '0';
                }
            }
        }

        for(int i=0; i<n; i++){
            if(scc[i] == i){
                vector<int> tmp(n, 1);
                for(int j=0; j<n; j++){
                    if(v[i][j]-'0' and i!=j){
                        for(int k=0; k<n; k++){
                            if(v[j][k]-'0' and j!=k){
                                tmp[k] = 0;
                            }
                        }
                    }
                }
                for(int j=0; j<n; j++){
                    if(v[i][j]-'0' and tmp[j] == 1 and scc[j] == j and i!=j){
                        ans.push_back({i, j});
                    }
                }
            }
        }

        cout << ans.size() << "\n";
        for(auto [i,j]:ans) cout << i+1 << " " << j+1 << "\n";
    }

    void dfs(int node){
        for(int i=0; i<n; i++){
            if(v[node][i] - '0' and !visited[i]){
                visited[i] = 1;
                dfs(i);
            } 
        }
        stk.push(node);
    }

    void dfs_inv(int node, int tp){
        for(int i=0; i<n; i++){
            if(v[i][node] - '0' and !visited[i]){
                visited[i] = 1;
                dfs_inv(i, tp);
            } 
        }
        scc[node] = tp;
        sccvi[tp].push_back(node);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        solve s;
    }
    return 0;
}