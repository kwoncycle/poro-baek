#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define p2 array<ll,2>

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

vector<vector<ll>> dst(1001, vector<ll>(1001, 999999999999999999ll));
vector<vector<array<ll, 2>>> graph(1001);
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m; cin >> n >> m;

    for(ll i=0; i<m; i++){
        ll u, v, d; cin >> u >> v >> d;
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
    }

    for(ll i=1; i<=n; i++){
        priority_queue<p2, vector<p2>, greater<p2>> pq;
        dst[i][i] = 0;
        pq.push({dst[i][i], i});
        while(!pq.empty()){
            p2 elm = pq.top(); pq.pop();
            ll node = elm[1], d = elm[0];
            if(dst[i][node] < d) continue;
            dst[i][node] = d;
            for(auto [next_node, next_d]:graph[node]){
                if(dst[i][next_node] > d + next_d){
                    dst[i][next_node] = d + next_d;
                    pq.push({dst[i][next_node], next_node});
                }
            }
        }
    }

    ll k; cin >> k;
    vector<array<ll, 3>> order(k);
    for(ll i=0; i<k; i++) cin >> order[i][0] >> order[i][1] >> order[i][2];

    ll st = -1, ed = 999999999999999999ll;
    while(st + 1 < ed){
        ll md = (st + ed)/2;
        vector<vector<ll>> DP(k+1, vector<ll>(k+1, 999999999999999999ll));
        for(ll i=0; i<k; i++){
            for(ll j=i; j<k; j++){
                if(i == 0){
                    ll tm = order[j][2] + dst[1][order[i][1]];
                    if(tm - order[i][0] <= md) DP[i][j] = tm;
                }
                else{
                    ll tm1 = DP[i-1][j] + dst[order[i-1][1]][order[i][1]];
                    ll tm2 = DP[i-1][i-1] + dst[order[i-1][1]][1];
                    tm2 = max(tm2, order[j][2]);
                    tm2 += dst[1][order[i][1]];
                    ll tm = min(tm1, tm2);
                    if(tm - order[i][0] <= md) DP[i][j] = tm;
                }
            }
        }
        if(DP[k-1][k-1] == 999999999999999999ll) st = md;
        else ed = md;
    }
    cout << ed << "\n";
    return 0;
}