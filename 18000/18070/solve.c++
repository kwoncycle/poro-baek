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

const ll MOD = 998244353;

ll DP[100500];
ll n, k; 
ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1){
            ans = ans * a % MOD;
        }
        e >>= 1;
        a = a * a % MOD;
    }
    return ans;
}

ll getN(ll n0){
    if(n0%2 == 0) return (n0/2) * (poww(k, n0/2) + poww(k, n0/2 + 1)) % MOD;
    else return n0 * poww(k, n0/2 + 1) % MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> k;
    for(int t=1; t<=n; t++){
        DP[t] = (DP[t] + getN(t)) % MOD;
        for(int j=t+t; j<=n; j+=t){
            DP[j] = (DP[j] - DP[t]*(j/t)) % MOD;
        }
    }
    ll ans = 0;
    for(int i=1; i<=n; i++){
        ans = (ans + DP[i] * (n/i)) % MOD;
    }
    if(ans < 0) ans += MOD;
    cout << ans << "\n";

    return 0;
}