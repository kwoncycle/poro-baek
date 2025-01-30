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

int dst(pii l, pii r){
    return (l.X-r.X)*(l.X-r.X) + (l.Y-r.Y)*(l.Y-r.Y);
}

int dst_wp(LINE w1, pii p){
    pii o = w1[1] - w1[0];
    int d = o.X + o.Y;
    o.X /= d; o.Y /= d;
    int d1 = o * (p - w1[0]);
    o.X *= d1; o.Y *= d1;
    pii cross = w1[0] + o;
    if(w1[0] <= cross and cross <= w1[1]) ;
    else cross = w1[0];
    return min(dst(w1[0], p), min(dst(w1[1], p), dst(cross, p)));
}

int dst_ww(LINE w1, LINE w2){
    int o = 0x3f3f3f;
    o = min(o, dst_wp(w2, w1[0]));
    o = min(o, dst_wp(w2, w1[1]));
    o = min(o, dst_wp(w1, w2[0]));
    o = min(o, dst_wp(w1, w2[1]));
    return o;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    int u, v2, w, l; cin >> u >> v2 >> w >> l;

    vector<pii> river_down(u), river_up(v2);
    for(int i=0; i<u; i++) cin >> river_down[i].X >> river_down[i].Y;
    for(int i=0; i<v2; i++) cin >> river_up[i].X >> river_up[i].Y;

    vector<LINE> wood(w+1);
    for(int i=1; i<=w; i++){
        for(int j=0; j<2; j++) {
            cin >> wood[i][j].X >> wood[i][j].Y;
        }
        if(wood[i][0] > wood[i][1]) swap(wood[i][0], wood[i][1]);
    }



    vector<vector<ll>> graph(w+2, vector<ll>(w+2, 0x2f3f3f3f3f3f3ll));
    for(int i=1; i<=w; i++){
        for(int j=i+1; j<=w; j++){
            ll o = dst_ww(wood[i], wood[j]);
            if(o <= l) {
                graph[i][j] = o;
                graph[j][i] = o;
            }
        }
    }

    for(int i=1; i<=w; i++){
        ll mn = 0x2f3f3f3f3f3f3ll;
        for(int j=0; j<(int)river_down.size()-1; j++){
            ll o = dst_ww(wood[i], {river_down[j], river_down[j+1]});
            if(o <= l) mn = min(mn, o);
        }
        graph[0][i] = mn;
        graph[i][0] = mn;
    }

    for(int i=1; i<=w; i++){
        ll mn = 0x2f3f3f3f3f3f3ll;
        for(int j=0; j<(int)river_up.size()-1; j++){
            ll o = dst_ww(wood[i], {river_up[j], river_up[j+1]});
            if(o <= l) mn = min(mn, o);
        }
        graph[w+1][i] = mn;
        graph[i][w+1] = mn;
    }

    {
        ll mn = 0x2f3f3f3f3f3f3ll;
        for(int i=0; i<(int)river_down.size()-1; i++){
            for(int j=0; j<(int)river_up.size()-1; j++){
                ll o = dst_ww({river_down[i], river_down[i+1]}, {river_up[j], river_up[j+1]});
                if(o <= l) mn = min(mn, o);
            }
        }
        graph[0][w+1] = mn;
        graph[w+1][0] = mn;
    }

    vector<ll> dst(w+2, 0x3f3f3f3f3f3f3f3fll);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, 0});
    while(!pq.empty()){
        auto [val, node] = pq.top(); pq.pop();
        if(dst[node] <= val) continue;
        dst[node] = val;
        for(int j=0; j<=w+1; j++){
            if(graph[node][j] == 0x2f3f3f3f3f3f3ll) continue;
            ll d = dst[node] + graph[node][j];
            if(d < dst[j]) pq.push({d, j});
        }
    }

    if(dst[w+1] > 0x3f3f3f3f3f3fll) cout << "-1\n";
    else cout << dst[w+1] << "\n";

    return 0;
}