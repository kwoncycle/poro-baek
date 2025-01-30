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

#define A3 array<ll, 3>

struct solve{
    int n, m;
    vector<vector<pll>> graph;
    vector<A3> edge;
    vector<ll> ans;
    map<pll, int> mp;
    vector<vector<pll>> G;
    vector<ll> dst;
    solve(){
        cin >> n >> m;
        graph.resize(n);
        edge.resize(m); ans.resize(m);
        dst.resize(n*2);
        int id = 0;
        for(auto &e:edge){
            for(int j=0; j<3; j++) cin >> e[j];
            e[0]--; e[1]--;
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
            mp[{min(e[0],e[1]), max(e[0],e[1])}] = id;
            id++;
        }
    
        for(ll w=0; w<n; w++){
            G = vector<vector<pll>>(n*2);
            fill(dst.begin(), dst.end(), 0x3f3f3f3f3f3f3fll);
            for(int i=0; i<n; i++){
                for(auto [j,d]:graph[i]){
                    G[i*2].push_back({j*2, d});
                    if(i != w) G[i*2].push_back({j*2+1, d});
                }
            }
            dijk(w*2);
            for(auto [i, d]:graph[w]){
                id = mp[{min(i,w), max(i,w)}];
                ans[id] = dst[i*2+1];
            }
        }

        for(int i=0; i<m; i++){
            if(ans[i] >= 0x3f3f3f3f3f3fll) cout << "-1\n";
            else cout << ans[i] << "\n";
        }
    }

    void dijk(int s){
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({0, s});
        while(!pq.empty()){
            auto [d, i] = pq.top(); pq.pop();
            if(dst[i] <= d) continue;
            dst[i] = d;
            for(auto [j, d1]: G[i]){
                if(dst[j] <= d + d1) continue;
                pq.push({d + d1, j});
            }
        }
    }


};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve s;
    return 0;
}