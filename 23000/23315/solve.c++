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

vector<pii> graph[1001001];
int deg[1001001], ban[1001001];
pii linklist[1001001];
vector<ll> cur;
vector<ll> v;


void nxt(){
    int n = cur.size();
    for(int i=0; i<n; i++) {
        linklist[i] = {(i-1+n)%n, (i+1)%n};
        ban[i] = 0;
    }
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for(int i=0; i<n; i++) pq.push({cur[i], i});
    n /= 2;
    while(n){
        pll p = pq.top(); pq.pop();
        int i = p.Y;
        if(ban[i]) continue;
        v.push_back(p.X); 
        n--; 
        auto [p0, p1] = linklist[i];
        cur[i] = cur[p0] + cur[p1] - cur[i];
        pq.push({cur[i], i});
        linklist[i].X = linklist[p0].X;
        linklist[linklist[p0].X].Y = i;
        ban[p0] = 1;
        linklist[i].Y = linklist[p1].Y;
        linklist[linklist[p1].Y].X = i;
        ban[p1] = 1;
    }
}

void DFS(int node, int rt){
    deg[node] = 0;
    for(auto &[i, c]:graph[node]){
        if(i == rt) continue;
        cur.push_back(c);
        DFS(i, node);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for(int i=0; i<m; i++){
        int x, y, c; cin >> x >> y >> c;
        graph[x].push_back({y+n, c});
        graph[y+n].push_back({x, c});
        deg[x]++; deg[y+n]++;
    }

    for(int i=1; i<=n*2; i++){
        if(deg[i] == 1){
            DFS(i, -1);
            cur.push_back(0x3f3f3f3f3f3f3fll);
            nxt();
            cur.clear();
        }
    }
    for(int i=1; i<=n*2; i++){
        if(deg[i] == 2){
            auto [nd, c] = graph[i].back();
            graph[i].pop_back();
            if(graph[nd][0].X == i) swap(graph[nd][0], graph[nd][1]);
            graph[nd].pop_back();
            DFS(i, -1);
            cur.push_back(c);
            nxt();
            cur.clear();
        }
    }

    ll ans = 0;
    sort(all(v));
    for(int i=0; i<(int)v.size(); i++){
        ans += v[i]; cout << ans << "\n";
        n--;
    }
    assert(n >= 0);
    while(n--) cout << "-1\n";

    return 0;
}