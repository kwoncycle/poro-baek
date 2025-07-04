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

const int MX = 50050;

struct solve{
    int n, k;
    vector<pii> graph[MX];
    double score[MX];
    double cur;
    bool able;
    vector<double> DP[MX];
    solve(){
        cin >> n >> k;
        for(int i=0; i<n-1; i++){
            int a, b, c; cin >> a >> b >> c;
            graph[a].push_back({b, c});
            graph[b].push_back({a, c});
        }

        double st = 0, ed = 1100000;
        while(st + 0.000000001 < ed){
            double md = (st + ed) / 2;
            cur = md;
            able = 0;
            for(int i=1; i<=n; i++) {
                DP[i].clear();
                score[i] = 0;
            }
            DFS(1, 0);
            if(able) st = md;
            else ed = md;
        }
        cout << fixed << setprecision(15) << st << "\n";
    }

    void DFS(int node, int par){
        if(able) return;
        DP[node].push_back(score[node]);
        for(auto &[nxt, c]:graph[node]){
            if(nxt == par) continue;
            if(able) return;
            score[nxt] = score[node] + (double)c - cur;
            DFS(nxt, node);
            DP[nxt].push_back(max(score[nxt], DP[nxt].back()));
        }
        for(auto &[nxt, c]:graph[node]){
            if(nxt == par) continue;
            if(able) return;
            score[nxt] = score[node] + (double)c - cur;
            if(DP[node].size() < DP[nxt].size()) DP[nxt].swap(DP[node]);
            int sz1 = DP[node].size(), sz2 = DP[nxt].size();
            for(int i=0; i<sz2; i++){
                int T = sz2-1-i + sz1-1 - k;
                if(0 <= T and T < sz1){
                    if(DP[nxt][i] + DP[node][T] >= score[node] + score[node]){
                        able = 1; return;
                    }
                }
            }
            for(int i=0; i<sz2; i++){
                DP[node][i-sz2+sz1] = max(DP[node][i-sz2+sz1], DP[nxt][i]);
                if(i-sz2+sz1 > 0) DP[node][i-sz2+sz1] = max(DP[node][i-sz2+sz1], DP[node][i-sz2+sz1 - 1]);
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve S;
    return 0;
}