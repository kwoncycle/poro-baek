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

int ban[1001001];
pii linklist[1001001];
vector<ll> cur;
vector<ll> nxt(){
    int n = cur.size();
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for(int i=0; i<n; i++) {
        linklist[i] = {(i-1>=0) ? i-1 : -1, (i+1)<n ? i+1 : -1};
        ban[i] = 0;
    }
    for(int i=0; i<n; i++) pq.push({cur[i], i});
    vector<ll> ans;
    while(!pq.empty()){
        pll p = pq.top(); pq.pop();
        int i = p.Y;
        if(ban[i]) continue;
        ans.push_back({p.X});
        auto [p0, p1] = linklist[i];
        int me = i;
        if(p0 != -1 and p1 != -1){
            cur[i] = cur[p0] + cur[p1] - cur[i];
            pq.push({cur[i], i});
        }
        else me = -1;
        if(p0 != -1) {
            linklist[i].X = linklist[p0].X;
            linklist[linklist[p0].X].Y = me;
            ban[p0] = 1;
        }
        if(p1 != -1) {
            linklist[i].Y = linklist[p1].Y;
            linklist[linklist[p1].Y].X = me;
            ban[p1] = 1;
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k; cin >> n >> k;
    vector<ll> t1(n);
    for(auto &i:t1) cin >> i;
    for(int i=0; i<n-1; i++) cur.push_back(t1[i+1] - t1[i]);
    vector<ll> t = nxt();
    ll sm = 0;
    for(int i=0; i<k; i++) sm += t[i];
    cout << sm << "\n";

    return 0;
}