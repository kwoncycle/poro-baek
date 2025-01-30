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

ll n, m, k;

ll cnt(ll u){ // count number of x in [1, m] s.t x&i = i 
    ll u1 = u;
    for(ll d=(1<<24); d>=1; d>>=1){
        if((u&d) == d) continue;
        if((u1^d) <= m) u1 ^= d;
    }
    ll ans = 0, o = 1;
    for(ll d=1; d<=(1<<24); d <<= 1){
        if((u&d) != d){
            if((u1&d) == d){
                ans ^= o;
            }
            o <<= 1;
        }
    }
    return ans + (u ? 1:0);
}

#define MOD 998244353

ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        e >>= 1;
        a = a * a % MOD;
    }
    return ans;
}

ll fct[5000005], fctinv[5000005];

ll C(ll a, ll b){
    return fct[a]*fctinv[a-b]%MOD*fctinv[b]%MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    fct[0] = 1;
    for(ll i=1; i<=5000000; i++) fct[i] = fct[i-1] * i % MOD;
    fctinv[5000000] = poww(fct[5000000], MOD - 2);
    for(ll i=5000000; i>=1; i--) fctinv[i-1] = fctinv[i] * i % MOD;
    assert(fctinv[0] == 1);
    cin >> n >> k >> m;
    vector<ll> v(m+1, 0);
    for(ll i=1; i<=m; i++){
        ll t = cnt(i);
        if(t < n) continue;
        v[i] = C(t, n);
    }

    ll ans = 0, ans1 = 0;
    for(ll i=1; i<=m; i++){
        ll d = __builtin_popcount(i);
        
        if(d >= k){
            ll o = 0;
            for(int u=k; u<=d; u++){
                o = o + ((u-d)%2==0 ? 1 : -1) * C(d, u); o %= MOD;
            }
            //cout << d << " " << k << " " << o << " " << v[i] << "\n";
            ans = (ans + o*v[i]) % MOD;
        }
    }
    if(ans < 0) ans += MOD;
    ans = ans * fct[n] % MOD;
    cout << ans << "\n";
    return 0;
}