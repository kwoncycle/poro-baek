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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    for(auto &i:v) cin >> i;
    int cur = 0;
    for(int i=0; i<n; i++){
        cur += (1<<i) * v[i];
    }

    vector<int> node(n);
    for(int i=0; i<n; i++){
        int t; cin >> t;
        
        while(t--){
            int a; cin >> a; a--;
            node[i] += (1<<a);
        }
        node[i] += (1<<i);
    }

    vector<vector<int>> G((1<<n));
    for(int i=0; i<(1<<n); i++){
        for(int j=0; j<n; j++){
            if(!(i&(1<<j))){
                G[i].push_back(i^node[j]);
            }
        }
    }

    vector<int> val((1<<n), 0x3f3f3f3f);
    queue<pii> q;
    q.push({cur, 0});
    while(!q.empty()){
        auto [node, dist] = q.front(); q.pop();
        if(dist >= val[node]){
            continue;
        }
        val[node] = dist;
        for(int i:G[node]){
            if(val[i] > dist + 1){
                q.push({i, dist + 1});
            }
        }
    }
    if(val[(1<<n) - 1] == 0x3f3f3f3f) cout << "-1\n";
    else cout << val[(1<<n) - 1] << "\n";
    return 0;
}