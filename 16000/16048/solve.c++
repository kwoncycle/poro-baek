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

#define MOD 1000000007

struct solve{
    int n, m;
    vector<vector<int>> graph;
    vector<int> rb;
    vector<vector<ll>> DP;
    vector<int> par;
    vector<int> under;
    vector<array<ll, 3>> c;
    vector<ll> c0;
    vector<int> is_r;
    solve(){
        cin >> n >> m;
        graph.resize(n+1);
        rb.resize(n+1);
        DP.resize(n+1);
        under.resize(n+1);
        c.resize(n+1);
        is_r.resize(n+1);
        for(int i=2; i<=n; i++){
            int t; cin >> t;
            graph[t].push_back(i);
        }
        for(int i=0; i<m; i++){
            int x; cin >> x; rb[x] = 1;
        }
        DFS_red(1);
        DFS(1);
        auto [id, cn, ct] = c[1];
        if(m == 0){
            cout << cn%MOD << "\n";
        }
        else{
            for(ll i=0; i<(int)DP[id].size(); i++) cout << ((DP[id][i]) * cn + (i==0?ct:0)) % MOD << "\n";
        }
        //for(int i=0; i<=m; i++) cout << DP[1][i] << "\n";
    }

    void DFS_red(int x){
        if(rb[x]) under[x] = 1;
        int cnt = 0;
        for(int id:graph[x]){
            DFS_red(id);
            under[x] += under[id];
            if(under[id]) cnt++;
        }
        if(cnt >= 2 or rb[x]) is_r[x] = 1;
    }

    void DFS(int x){
        if(graph[x].empty()){
            if(rb[x]) {
                DP[x].resize(2);
                DP[x][0] = 1; DP[x][1] = 1;
                c[x] = {x, 1, 0};
            }
            else{
                c[x] = {-1, 2, 0};
            }
            return;
        }
        ll cx = 1;
        ll xid = -1;
        ll ct = 0;
        for(int id:graph[x]){
            DFS(id);
        }
        if(is_r[x]) {DP[x].resize(under[x] + 1); DP[x][0] = 1; xid = x;}
        for(int id:graph[x]){
            if(c[id][0] == -1) {
                cx = cx * c[id][1] % MOD;
                ct = ct * c[id][1] % MOD;
            }
            else{
                if(xid == -1 and !rb[x]) {
                    xid = c[id][0];
                    ct = c[id][2] * cx % MOD;
                    cx = cx * c[id][1] % MOD;
                }
                else{
                    vector<ll> tmp(under[x]+1, 0);
                    for(int i=0; i<(int)DP[c[id][0]].size(); i++){
                        for(int j=0; j<=under[x]-i; j++){
                            tmp[i+j] = (tmp[i+j] + (c[id][1]*DP[c[id][0]][i]%MOD + (i==0 ? c[id][2] : 0)) * DP[x][j]) % MOD;
                        }
                    }
                    DP[x] = tmp;
                }
            }
        }
        if(xid == -1) {
            cx++;
            assert(ct == 0);
        }
        else if(xid == x){
            for(int i=0; i<(int)DP[x].size(); i++){
                DP[x][i] = DP[x][i] * cx % MOD;
            }
            DP[x][0] += ct;
            ct = 0;
            cx = 1;
            if(rb[x]) DP[x][1]++;
            else DP[x][0]++;
        }
        else{
            ct++;
        }
        
        c[x] = {xid, cx, ct};
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve ss;
    return 0;
}