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

const int MX = 200005;
vector<int> v[MX];
int par[MX], DP[MX], sparse[MX][20];

struct solve{
    int n;
    solve(){
        cin >> n;
        for(int i=1; i<=n; i++){
            v[i].resize(3);
            for(auto &x:v[i]) {
                cin >> x;
                if(x == i) x = n+1;
            }
            sort(all(v[i]));
        }
        for(int i=0; i<20; i++){
            sparse[n+1][i] = n+1;
        }
        for(int i=n; i>=1; i--){
            int nxt = n+1;
            for(int j=0; j<3; j++){
                int o = lca(v[i][j], v[i][(j+1)%3]);
                if(DP[nxt] < DP[o]) nxt = o;
            }
            par[i] = nxt;
            DP[i] = DP[par[i]] + 1;
            sparse[i][0] = nxt;
            for(int d=1; d<20; d++){
                sparse[i][d] = sparse[sparse[i][d-1]][d-1];
            }
            
        }
        int st = 1;
        vector<int> ans(n+1);
        while(st < n+1){
            ans[st] = 1; st = par[st];
        }
        for(int i=1; i<=n; i++){
            if(ans[i]) cout << "Yes\n";
            else cout << "No\n";
        }
    }
    int lca(int l, int r){
        if(DP[l] < DP[r]) swap(l, r);
        int o = DP[l]-DP[r];
        for(int d=19; d>=0; d--){
            if((o>>d)&1) l = sparse[l][d];
        }
        if(l == r) return l;
        for(int d=19; d>=0; d--){
            if(sparse[l][d] != sparse[r][d]){
                l = sparse[l][d];
                r = sparse[r][d];            
            }
        }
        return par[l];
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve S;
    return 0;
}