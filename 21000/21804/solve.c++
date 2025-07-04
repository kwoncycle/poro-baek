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

const ll MOD = 998244353;

ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, k; cin >> n >> k;
    ll n1 = n;
    ll phi = 1;
    for(ll i=2; i<=40000; i++){
        if(n%i == 0){
            phi *= i-1;
            n /= i;
            while(n%i == 0) {
                n /= i; phi *= i;
            }
        }
    }
    if(n > 1) phi *= n-1;
    n = n1;
    ll c1 = 1, c2 = 1;
    for(ll i=1; i<=k-1; i++){
        c1 = c1*(n-i) % MOD;
        c2 = c2*i % MOD;
    }
    c2 = poww(c2, MOD-2);
    ll ans = c1 * c2 % MOD * phi % MOD;
    cout << ans << "\n";
    return 0;
}