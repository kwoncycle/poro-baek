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

vector<int> graph[305];
int cost[305];
const int D = 90500;
ll DP[305][181000]; // DP[i][j] : i~n, win with +k + D more
#define MOD 998244353

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    string s; cin >> s;
    s = 'W' + s;
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
    }
    for(int i=n; i>=1; i--){
        if(s[i] == 'W'){
            for(int j:graph[i]){
                cost[i] = max(cost[i], cost[j] + 1);
            }
        }
        else{
            for(int j:graph[i]){
                cost[i] = min(cost[i], cost[j] - 1);
            }
        }
    }
    DP[n][D-1] = 2;
    for(ll i=n-1; i>=1; i--){
        for(int j=0; j<=180000; j++){
            DP[i][j] = (DP[i+1][j] + ((j-cost[i] >= 0 and j-cost[i] <= 180000) ? DP[i+1][j-cost[i]] : 0)) % MOD;
        }
    }
    ll sm = 0;
    for(int i=D; i<=180000; i++) sm += DP[1][i], sm %= MOD;
    cout << sm << "\n";
    return 0;
}