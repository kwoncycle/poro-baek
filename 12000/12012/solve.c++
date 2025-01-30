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


struct djs
{
    int n;
    vector<int> par, cnt;
 
public:
    djs(int n) : n(n) {
        par.resize(n);
        cnt.resize(n, 1);
        for(int i=0; i<n; i++) par[i] = i;
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
 
    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);
 
        if(px == py) return false;

        cnt[py] += cnt[px];
        par[px] = py;
        
        return true;
    }
};
// Usage: djs DJS(n)

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> graph(n+1);
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    djs DJS(n+1);
    vector<int> perm(n);
    for(int i=0; i<n; i++) cin >> perm[i];
    vector<int> isin(n+1, 0);
    vector<string> ans(n);
    for(int i=n-1; i>=0; i--){
        int i1 = perm[i];
        for(int j1:graph[i1]){
            if(isin[j1]) DJS.Union(i1, j1);
        }
        isin[i1] = 1;
        if(DJS.cnt[DJS.find(i1)] == n - i) ans[i] = "YES";
        else ans[i] = "NO";
    }
    for(auto i:ans) cout << i << "\n";
    return 0;
}