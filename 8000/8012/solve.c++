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


vector<int> G[30001];
int depth[30001];
int root[30001];
int sparse[30001][16];
void dfs(int i, int t){
    for(int j:G[i]){
        if(t == j) continue;
        depth[j] = depth[i] + 1;
        root[j] = i;
        dfs(j, i);
    }
}

int lca(int i, int j){
    if(depth[i] < depth[j]) swap(i, j);
    for(int d=16-1; d>=0; d--){
        if(depth[sparse[i][d]] >= depth[j]) i = sparse[i][d];
    }
    if(i == j) return i;
    for(int d=16-1; d>=0; d--){
        if(sparse[i][d] != sparse[j][d]){
            i = sparse[i][d], j = sparse[j][d];
        }
    }
    return root[i];
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    for(int i=0; i<n-1; i++){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    depth[1] = 1;
    root[1] = 0;
    dfs(1, 0);
    
    for(int i=1; i<=n; i++) sparse[i][0] = root[i];
    for(int d=1; d<16; d++){
        for(int i=1; i<=n; i++){
            sparse[i][d] = sparse[sparse[i][d-1]][d-1];
        }
    }

    int qq; cin >> qq;
    vector<int> v(qq);
    for(int i=0; i<qq; i++) cin >> v[i];
    ll ans = 0;
    for(int i=0; i<qq-1; i++){
        int t = lca(v[i], v[i+1]);
        ans += depth[v[i]] + depth[v[i+1]] - 2*depth[t];
    }
    cout << ans << "\n";

    return 0;
}