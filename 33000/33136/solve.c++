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

int n, m; 
vector<int> G[200005];
int chk[200005], par[200005], depth[200005];
void DFS(int node){
    for(int i:G[node]){
        if(chk[i]) continue;
        chk[i] = 1;
        par[i] = node;
        depth[i] = depth[node] + 1;
        DFS(i);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    unordered_map<ll, int> mp;
    for(int i=0; i<m; i++){
        ll a, b; cin >> a >> b;
        mp[(a<<30) ^ b] = i+1; mp[(b<<30) ^ a] = i+1;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    chk[1] = 1; depth[1] = 1;
    DFS(1);
    ll mx = 0, i1, i2;
    for(int i=1; i<=n; i++){
        for(int j:G[i]){
            if(depth[j] < depth[i] and j != par[i]){
                if(mx < depth[j]){
                    mx = depth[j];
                    i1 = i; i2 = j;
                }
            }
        }
    }
    vector<int> ans;
    ans.push_back(mp[(i1 << 30) ^ i2]);
    while(i1 != i2){
        assert(i1 != 0);
        ans.push_back(mp[(i1 << 30) ^ par[i1]]);
        i1 = par[i1];
    }
    cout << ans.size() << "\n";
    for(int i:ans) cout << i << " "; cout << "\n";

    return 0;
}