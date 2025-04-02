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

#define MOD 1000000007

ll fct[1000005], fcti[1000005];
ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        e >>= 1;
        a = a * a % MOD;
    }
    return ans;
}

ll C(ll a, ll b){
    if(a < b) return 0;
    return fct[a]*fcti[b]%MOD*fcti[a-b]%MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    fct[0] = 1;
    for(ll i=1; i<=1000001; i++) fct[i] = fct[i-1] * i % MOD;
    fcti[1000001] = poww(fct[1000001], MOD - 2);
    for(int i=1000001; i>=1; i--) fcti[i-1] = fcti[i] * i % MOD;
    ll n, k; cin >> n >> k;
    // // k+1
    // if(k == n){
    //     cout << "0\n"; return 0;
    // }
    // ll ans = 0;
    // for(ll i=1; i<=n; i++){
    //     ans = (ans + i*C(n-i, k)*fct[k+1]%MOD*fct[n-(k+1)]%MOD*(n-k)%MOD) % MOD;
    // }
    //ll ans = fct[n]*((n-k+1)*(n-k)/2 % MOD)%MOD;
    ll ans = 0;
    for(ll i=k; i<=n; i++){
        ans = (ans + ((n+1)*C(n, i+1)%MOD - (i+1)*C(n+1, i+2)%MOD)*fct[i+1]%MOD*fct[n-i]%MOD) % MOD;
    }
    if(ans < 0) ans += MOD;
    cout << ans << "\n";
    return 0;
}