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

struct solve{
    int n;
    vector<int> color, DP0, DP1, ci0, ci1, partner, isin, deg; // DP0 : x, DP1 : o, subtree root
    vector<vector<int>> G;
    vector<pii> edges;
    solve(){
        cin >> n;
        color.resize(2*n+1); G.resize(2*n+1); DP0.resize(2*n+1), DP1.resize(2*n+1); ci0.resize(n+1), ci1.resize(n+1); partner.resize(2*n+1); isin.resize(2*n+1); deg.resize(n+1);
        for(int i=1; i<=2*n; i++) {
            cin >> color[i];
            if(ci0[color[i]] == 0) ci0[color[i]] = i;
            else ci1[color[i]] = i;
        }
        for(int i=0; i<2*n-1; i++){
            int a, b; cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        DFS(1, 0);
        if(DP0[1] <= DP1[1]) DFS1(1, 0, 1);
        else DFS1(1, 0, 0);
        G.clear();
        G.resize(2*n+1);
        for(auto &[i,j]:edges){
            isin[i] = 1; isin[j] = 1;
            G[i].push_back(j); G[j].push_back(i);
            deg[color[i]]++; deg[color[j]]++;
        }
        vector<pii> ans;
        for(int i=1; i<=2*n; i++){
            if(isin[i] and deg[color[i]] == 1){
                int cur = i;
                vector<int> seq;
                seq.push_back(opposite(cur));
                while(true){
                    seq.push_back(cur);
                    deg[color[cur]]--;
                    cur = G[cur][0];
                    deg[color[cur]]--;
                    seq.push_back(cur);
                    if(deg[color[cur]]) cur = opposite(cur);
                    else break;
                }
                int sz = seq.size();
                for(int j=0; j<sz/2; j++){
                    ans.push_back({seq[j], seq[sz-1-j]});
                }
            }
        }
        for(int i=1; i<=2*n; i++){
            if(isin[i] and deg[color[i]] == 2){
                int cur = i;
                vector<int> seq;
                int o = opposite(cur);
                while(true){
                    seq.push_back(cur);
                    deg[color[cur]]--;
                    cur = G[cur][0];
                    deg[color[cur]]--;
                    seq.push_back(cur);
                    if(deg[color[cur]]) cur = opposite(cur);
                    else break;
                }
                seq.pop_back();
                int sz = seq.size();
                for(int j=0; j<sz/2; j++){
                    ans.push_back({seq[j], seq[sz-1-j]});
                }
            }
        }
        cout << ans.size() << "\n";
        for(auto &[i,j]:ans) cout << i << " " << j << "\n";
    }
    int opposite(int node){
        int c = color[node];
        return ci0[c] + ci1[c] - node;
    }
    void DFS(int node, int rt){
        int diff = -0x3f3f3f3f, p = -1;
        for(int i:G[node]){
            if(i == rt) continue;
            DFS(i, node);
            DP0[node] += max(DP0[i], DP1[i]);
            if(diff < max(diff, DP0[i] - max(DP0[i], DP1[i]))){
                diff = max(diff, DP0[i] - max(DP0[i], DP1[i]));
                p = i;
            }
        }
        DP1[node] = max(0, DP0[node] + diff + 1);
        partner[node] = p;
    }
    void DFS1(int node, int rt, int state){ // 1: free, 0: ban
        if(state == 1){
            for(int i:G[node]){
                if(i == rt) continue;
                if(i == partner[node] and DP1[node] >= DP0[node]){
                    edges.push_back({node, i});
                    DFS1(i, node, 0);
                }
                else DFS1(i, node, 1);
            }
        }
        else{
            for(int i:G[node]){
                if(i == rt) continue;
                DFS1(i, node, 1);
            }
        }
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