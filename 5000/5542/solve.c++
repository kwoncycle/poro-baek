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

struct djs
{
    int n;
    vector<int> par;
 
public:
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
// Usage: djs DJS(n)

vector<pii> graph[100010];
vector<int> dst(100010, 0x5f3f3f3f);
vector<int> idx;
vector<int> visited(100010, 0);
djs DJS(100010);

void step(int i){ // idx[i] 살리기
    i = idx[i];
    visited[i] = 1;
    for(auto &[j, _]:graph[i]){
        if(visited[j]) {
            DJS.Union(i, j);
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    for(int i=0; i<m; i++){
        int s, t, d; cin >> s >> t >> d;
        graph[s].push_back({t, d});
        graph[t].push_back({s, d});
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq; // (dst, node)
    for(int i=0; i<k; i++){
        int a; cin >> a;
        pq.push({0, a});
    }

    while(!pq.empty()){
        auto [d, node] = pq.top(); pq.pop();
        if(dst[node] <= d) continue;
        dst[node] = d;
        for(auto &[ni, di]: graph[node]){
            if(dst[ni] > di + dst[node]) pq.push({di + dst[node], ni});
        }
    }

    idx.resize(n);
    for(int i=0; i<n; i++) idx[i] = i + 1;
    sort(idx.begin(), idx.end(), [&](int l, int r){
        return dst[l] < dst[r];
    });

    vector<pii> query(q);
    for(int i=0; i<q; i++) cin >> query[i].X >> query[i].Y;
    vector<int> query_idx(q);
    for(int i=0; i<q; i++) query_idx[i] = i;

    vector<pii> search_range(q, {0, 0x5f3f3f3f});
    while(true){
        for(int i=0; i<=n+1; i++) DJS.par[i] = i;
        fill(visited.begin(), visited.end(), 0);
        int truth = 0;
        for(int i=0; i<q; i++){
            if(search_range[i].X + 1 < search_range[i].Y) truth = 1;
        }
        if(!truth) break;
        sort(query_idx.begin(), query_idx.end(), [&](int l, int r){
            return search_range[l].X + search_range[l].Y < search_range[r].X + search_range[r].Y;
        });
        for(int i1=n-1, i2=q-1; i1>=0; i1--){
            while(i2 >= 0){
                int qi = query_idx[i2];
                int md = (search_range[qi].X + search_range[qi].Y) / 2;
                if(dst[idx[i1]] < md){
                    //cout << md << " ";
                    if(DJS.find(query[qi].X) == DJS.find(query[qi].Y)) search_range[qi].X = md;
                    else search_range[qi].Y = md;
                    i2--;
                }
                else break;
            }
            step(i1);
        }
    }

    for(int i=0; i<q; i++) cout << search_range[i].X << "\n";

    return 0;
}