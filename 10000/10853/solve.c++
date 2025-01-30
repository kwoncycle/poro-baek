#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

ll n, m, k; 
vector<vector<array<ll,2>>> graph;
vector<vector<array<ll, 2>>> graph1;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m >> k;
    graph.resize(n+1);
    graph1.resize(n+1);
    vector<ll> path(k);
    for(ll i=0; i<k; i++) cin >> path[i];

    for(ll i=0; i<m; i++){
        ll a, b, c; cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    vector<ll> dist(n+1, 0x3f3f3f3f3f3f3f3fll);
    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;
    // (dist[i], i)
    dist[1] = 0;
    pq.push({dist[1], 1});
    while(!pq.empty()){
        auto [x, y] = pq.top(); pq.pop();
        if(dist[y] < x){
            continue;
        }
        dist[y] = x;
        for(auto [nx, ny]: graph[y]){
            ll nd = ny + dist[y];
            if(dist[nx] > nd){
                dist[nx] = nd;
                pq.push({dist[nx], nx});
            }
        }
    }

    ll truth = 1;
    for(ll i=k-1; i>0; i--){
        int c = 0;
        for(auto [x, y]:graph[path[i]]){
            if(dist[x] + y <= dist[path[i]]) c++;
        }
        if(c > 1) truth = 0;
    }

    if(truth) cout << "no\n";
    else cout << "yes\n";
    return 0;
}