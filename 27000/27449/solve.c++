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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

ll DP[5001][5001][2];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m; cin >> n >> m;
    vector<pll> v(n);
    for(ll i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    sort(v.begin(), v.end());
    ll id = 0;
    while(id < n and v[id].X < 0) id++;
    if(id == n){ // - - - 0
        ll sm = m;
        ll cur = 0;
        for(ll i=n-1; i>=0; i--){
            if(cur - v[i].X < m){
                m += v[i].Y; sm += v[i].Y; m -= cur - v[i].X;
                cur = v[i].X;
            }
            else{
                break;
            }
        }
        cout << sm << "\n"; return 0;
    }
    if(id == 0){ // 0 - - 
        ll sm = m;
        ll cur = 0;
        for(ll i=0; i<n; i++){
            if(v[i].X - cur < m){
                m += v[i].Y; sm += v[i].Y; m -= v[i].X - cur;
                cur = v[i].X;
            }
            else{
                break;
            }
        }
        cout << sm << "\n"; return 0;
    }
    vector<ll> presm(n);

    for(ll i=0; i<n; i++){
        presm[i] = (i-1>=0 ? presm[i-1] : 0) + v[i].Y;
    }

    for(ll i=0; i<n; i++){
        for(ll j=0; j<n; j++){
            DP[i][j][0] = -0x3f3f3f3f3f3f3fll;
            DP[i][j][1] = -0x3f3f3f3f3f3f3fll;
        }
    }
    // DP[i][j][t] = i~j eat all end t(0:i 1:j), maximum height. if impossible -0x3f3f3f3f
    //DP[id-1][id-1]
    if(0 - v[id-1].X < m) {
        DP[id-1][id-1][0] = m - (-v[id-1].X) + v[id-1].Y;
        DP[id-1][id-1][1] = m - (-v[id-1].X) + v[id-1].Y;
    }

    if(0 + v[id].X < m) {
        DP[id][id][0] = m - (v[id].X) + v[id].Y;
        DP[id][id][1] = m - (v[id].X) + v[id].Y;
    }

    for(ll i=id; i>=0; i--){
        for(ll j=id-1; j<n; j++){
            if(i >= j) continue;
            //DP[i][j][0] = DP[i+1][j]
            if(DP[i+1][j][0] > v[i+1].X - v[i].X) DP[i][j][0] = max(DP[i][j][0], DP[i+1][j][0] - (v[i+1].X - v[i].X) + v[i].Y);
            if(DP[i+1][j][1] > v[j].X - v[i].X) DP[i][j][0] = max(DP[i][j][0], DP[i+1][j][1] - (v[j].X - v[i].X) + v[i].Y);

            if(DP[i][j-1][0] > v[j].X - v[i].X) DP[i][j][1] = max(DP[i][j][1], DP[i][j-1][0] - (v[j].X - v[i].X) + v[j].Y);
            if(DP[i][j-1][1] > v[j].X - v[j-1].X) DP[i][j][1] = max(DP[i][j][1], DP[i][j-1][1] - (v[j].X - v[j-1].X) + v[j].Y);
        }
    }

    ll ans = m;
    for(ll i=0; i<n; i++){
        for(ll j=i; j<n; j++){
            if(DP[i][j][0] > 0 or DP[i][j][1] > 0){
                ans = max(ans, m + presm[j] - (i-1>=0 ? presm[i-1] : 0));
            }
        }
    }
    /*
    {
        ll sm = m;
        ll cur = 0;
        for(ll i=id-1; i>=0; i--){
            if(cur - v[i].X < m){
                m += v[i].Y; sm += v[i].Y; m -= cur - v[i].X;
                cur = v[i].X;
            }
            else{
                break;
            }
        }
        ans = max(ans, sm);
    }

    { // 0 - - 
        ll sm = m;
        ll cur = 0;
        for(ll i=id; i<n; i++){
            if(v[i].X - cur < m){
                m += v[i].Y; sm += v[i].Y; m -= v[i].X - cur;
                cur = v[i].X;
            }
            else{
                break;
            }
        }
        ans = max(ans, sm);
    }*/
    cout << ans << "\n";

    return 0;
}