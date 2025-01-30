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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll tt; cin >> tt;
    while(tt--){
        ll n, k; cin >> n >> k;
        vector<ll> v(n), c(n);
        for(ll i=0; i<n; i++) cin >> v[i];
        for(ll i=0; i<n; i++) cin >> c[i];
        ll sm = 0, sm12 = 0;
        vector<vector<ll>> pre(2*n+3);
        pre[sm + n].push_back(sm12);
        for(ll i=0; i<n; i++){
            if(v[i] == 1) sm12++;
            else sm12--;
            if(v[i] == 1) sm += c[i];
            else sm -= c[i];
            pre[sm12+n].push_back(sm);
        }
        ll ans = 0;
        for(ll i=0; i<=2*n+2; i++){
            sort(pre[i].begin(), pre[i].end());
            //for(ll j:pre[i]) cout << j << " "; cout << "\n";
            for(ll j1=0, j2=0; j1<(ll)pre[i].size(); j1++){
                if(j2 <= j1) j2 = j1;
                while(j2+1 < (ll)pre[i].size() and pre[i][j2+1] - pre[i][j1] <= k) j2++;
                ans += j2-j1; 
            }
        }
        cout << ans << "\n";
    }
    return 0;
}