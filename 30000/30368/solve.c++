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


#define MOD 998244353

ll m; 

ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        e >>= 1;
        a = a*a%MOD;
    }
    return ans;
}

ll fct[500005], fctinv[500005];

ll C(ll a, ll b){
    return fct[a] * fctinv[b] % MOD * fctinv[a-b] % MOD;
}

ll cnt(ll t, ll r){
    return C(2*t, r) * poww(m-1, 2*t-r) % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    fct[0] = 1;
    for(int i=1; i<=500000; i++) fct[i] = fct[i-1] * i % MOD;
    fctinv[500000] = poww(fct[500000], MOD - 2);
    for(int i=500000; i>=1; i--){
        fctinv[i-1] = fctinv[i] * i % MOD;
    }

    ll cur = 0;
    cin >> m;
    for(int i=1; i<=m; i++){
        if(i == 1) cur = 1;
        else{
            ll o1 = cur + cnt(i-1, i-1);
            ll o2 = cur * 2 * (m-1) % MOD;
            ll o3 = (cur - cnt(i-1, i))%MOD * (m-1) % MOD * (m-1) % MOD;
            cur = (o1 + o2 + o3) % MOD;
        }

        ll ans = poww(m, 2*i) - m * cur % MOD;
        ans %= MOD;
        if(ans < 0) ans += MOD;
        cout << ans << "\n";
    }
    return 0;
}