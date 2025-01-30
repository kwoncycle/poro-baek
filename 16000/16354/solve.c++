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

ll MOD = 1000000007;

map<pll, ll> DP;

ll poww(ll a, ll x){
    ll ans = 1;
    while(x){
        if(x&1) ans = ans * a % MOD;
        a = a * a % MOD;
        x >>= 1;
    }
    return ans;
}

vector<ll> p2(62, 1);
vector<ll> p4(62, 1);

ll JG(ll n, ll k){
    if(n == 1){
        if(k == 2) return 1;
        if(k == 0) return 6;
        if(k == -2) return 3;
    }
    if(k/2 > p2[n] - 1) return 0;
    if(-p2[n] + 1 > (k/2)) return 0;
    if(DP.find({n, k}) != DP.end()){
        return DP[{n, k}];
    }
    if(k == 0){
        ll o = (p4[n-1] * (p2[n-1] % MOD) % MOD) * 4 % MOD;
        ll a = (o + 2*JG(n-1, k)) % MOD;
        DP[{n, k}] = a;
        return a;
    }
    // 6: 1, 4: 2, 2: 3
    // 2^n - k/2
    else if(k > 0 and k <= p2[n] - 2){
        ll i1 = p2[n-1] - k/2;
        ll i2 = k/2;
        ll o = (p4[n-1] * 4 * (i1 % MOD) % MOD);
        ll a = (o + 2*JG(n-1, k) + JG(n-1, k - p2[n]))%MOD;
        DP[{n, k}] = a;
        return a;
    }
    else if(k > p2[n] - 2){
        ll a = JG(n-1, k - p2[n]);
        DP[{n, k}] = a;
        return a;
    }
    else if(k < 0 and k >= -p2[n] + 2){
        ll i1 = p2[n-1] + k/2;
        ll i2 = -k/2;
        ll o = (p4[n-1] * 4 * (i1 % MOD) % MOD) + (p4[n-1] * 2 * (i2 % MOD) % MOD);
        o %= MOD;
        ll a = (o + 2*JG(n-1, k) + JG(n-1, k + p2[n])) % MOD;
        DP[{n, k}] = a;
        return a;
    }
    else{
        ll i2 = p2[n-1] + (k/2 + p2[n-1]);
        ll o = (i2 % MOD) * 2 * p4[n-1] % MOD;
        ll a = (o + JG(n-1, k + p2[n])) % MOD;
        DP[{n, k}] = a;
        return a;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for(int i=1; i<=61; i++) {
        p2[i] = p2[i-1] * 2;
        p4[i] = poww(4, i);
    }

    ll n, k; cin >> n >> k;
    if(k % 2 == 1) cout << "0\n";
    else {
        ll ans = JG(n, k);
        ans %= MOD;
        ans = (ans + MOD) % MOD;
        cout << ans << "\n";
    }
    return 0;
}