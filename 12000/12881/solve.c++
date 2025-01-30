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

using A2 = array<ll, 2>;

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    int n, k, l; cin >> n >> k >> l;
    vector<int> loc(n);
    for(int i=0; i<n; i++) cin >> loc[i];
    set<int> sl;
    for(int i:loc) sl.insert(i);
    if((int)sl.size() != n){
        cout << "0\n"; return 0;
    }
    vector<vector<array<ll, 2>>> graph(k+1);
    for(int i=0; i<l; i++){
        int b, c, d; cin >> b >> c >> d;
        graph[b].push_back({c, d});
        graph[c].push_back({b, d});
    }

    vector<A2> dst(k+1, {0x3f3f3f3f3f3fll, -1});
    priority_queue<pair<A2, ll>, vector<pair<A2, ll>>, greater<pair<A2, ll>>> pq;
    for(int i=0; i<n; i++){
        //dst[loc[i]] = {0, loc[i]};
        pq.push({{0, loc[i]}, loc[i]});
    }

    while(!pq.empty()){
        auto [d, l] = pq.top(); pq.pop();
        if(dst[l][0] <= d[0]) continue;
        dst[l][0] = d[0];
        dst[l][1] = d[1];
        for(auto [i1, l1]:graph[l]){
            if(dst[i1][0] <= dst[l][0] + l1) continue;
            pq.push({{dst[l][0] + l1, dst[l][1]}, i1});
        }
    }
    ll mn = 0x103f3f3f3f3f3f3fll;
    for(int i=1; i<=k; i++){
        for(auto [j,d]:graph[i]){
            if(dst[i][1] != dst[j][1]){
                ll o = dst[i][0] + dst[j][0] + d;
                mn = min(mn, o);
            }
        }
    }
    mn *= 3;
    cout << mn << "\n";
    return 0;
}