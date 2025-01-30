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

class djs
{
public:
    int n;
    vector<int> par;
 

    djs(int n) : n(n) {
        par.resize(n);
        for(int i=0; i<n; i++) par[i] = i;
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
 
    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);
 
        if(px == py) return false;
 
        par[px] = py;
        return true;
    }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, r; cin >> n >> m >> r;
    vector<vector<int>> graph(n+1);
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> is_in(n+1, 0x3f3f3f);
    vector<int> checked(n+1, 0);
    pq.push({graph[r].size(), r});
    is_in[r] = graph[r].size();
    checked[r] = 1;

    ll ans = 0;
    while(!pq.empty()){
        auto [val, node] = pq.top(); pq.pop();
        if(is_in[node] < val) continue;
        checked[node] = 1;
        ans += val - graph[node].size();
        for(int i:graph[node]){
            if(checked[i]) continue;
            if(is_in[i] > (int)graph[node].size() + graph[i].size()){
                pq.push({(int)graph[node].size() + (int)graph[i].size(), i});
                is_in[i] = graph[node].size() + (int)graph[i].size();
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}