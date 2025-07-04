#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

vector<pair<pair<double, double>, int>> G[10005];
double dst[10005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, t;
    cin >> n >> m >> t;
    vector<array<int,4>> v(m);
    for(auto &[i,j,k,l]:v) {
        cin >> i >> j >> k >> l;
        G[i].push_back({{k, l}, j});
        G[j].push_back({{k, l}, i});
    }

    double st = 0, ed = 1e10+1000;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    while(st + 0.0000001 < ed){
        double md = (st + ed)/2;
        for(int i=0; i<=n; i++) dst[i] = 0x3f3f3f3f3f3f3f3fll;
        dst[1] = 0;
        pq.push({0, 1});
        while(!pq.empty()){
            auto [d, i] = pq.top(); pq.pop();
            if(dst[i] > d) continue;
            for(auto &[nd, ni]:G[i]){
                if(nd.X / (nd.Y + md) + d < dst[ni] - 0.000000001){
                    dst[ni] = nd.X / (nd.Y + md) + d;
                    pq.push({dst[ni], ni});
                }
            }
        }
        if(dst[n] <= t) ed = md;
        else st = md;
    }
    if(ed <= 0.0000001) cout << 0 << "\n";
    else cout << fixed << setprecision(15) << ed << "\n";

    return 0;
}