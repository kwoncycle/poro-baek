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


struct solve{
    int n;
    vector<vector<int>> G;
    vector<int> DP, deg;
    vector<int> ans1, ans0;
    int RT = -1;
    solve(){
        cin >> n;
        G.resize(n+1); DP.resize(n+1); deg.resize(n+1);
        for(int i=1; i<n; i++){
            int a,b; cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
            deg[a]++; deg[b]++;
        }
        int st = 0x3f3f3f3f;
        for(int i=1; i<=n; i++){
            if(G[i].size() == 1) st = min(st, i);
        }
        DFS(st, 0);
        DFS1(st, 0, 1);
        vector<int> ans = ans0;
        if(RT == -1) RT = ans.back();
        if(RT != -1){
            fill(all(DP), 0);
            DFS(RT, 0);
            ans1.clear(); 
            DFS1(RT, 0, 1);
            ans = min(ans, ans1);
        }
        for(int i:ans) cout << i << " "; cout << "\n";
    }
    void DFS(int node, int rt){
        DP[node] = 0x3f3f3f3f;
        
        for(int i:G[node]){
            if(i == rt) continue;
            DFS(i, node);
            DP[node] = min(DP[node], DP[i]);
        }
        sort(all(G[node]), [&](int l, int r){
            if(l == rt) return true;
            if(r == rt) return false;
            return DP[l] < DP[r];
        });
        if(G[node].size() == 1) DP[node] = node;
    }

    void DFS1(int node, int rt, bool ed){
        if(ed){
            if(G[node].back() != rt and node > DP[G[node].back()]){
                if(RT == -1){
                    RT = node;
                }
            }
        }
        bool leaf = 1;
        for(int i:G[node]){
            if(i == rt) continue;
            leaf = 0;
            if(i == G[node].back() and ed) {
                ans0.push_back(node);
                DFS1(i, node, ed);
            }
            else DFS1(i, node, 0);
        }
        ans1.push_back(node);
        if(!ed or leaf) ans0.push_back(node);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        solve S;
    }
    return 0;
}