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
vector<ll> fct(100001, 1), fctinv(100001, 1);


ll poww(ll a, ll x){
    ll ans = 1;
    while(x){
        if(x&1) ans = ans * a % MOD;
        a = a * a % MOD;
        x >>= 1;
    }
    return ans;
}

ll nCr(ll n, ll r){
    ll o = fct[n];
    o = o * fctinv[r] % MOD;
    o = o * fctinv[n-r] % MOD;
    return o;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for(ll i=1; i<=100000; i++){
        fct[i] = fct[i-1] * i % MOD;
    }
    fctinv[100000] = poww(fct[100000], MOD - 2);
    for(ll i=100000; i>=1; i--){
        fctinv[i-1] = fctinv[i] * i % MOD;
    }

    int n; cin >> n;
    vector<string> s(n);
    for(int i=0; i<n; i++) cin >> s[i];

    int n_nc = 0, n_n = 0, n_c = 0, n_cn = 0;
    for(int i=0; i<n; i++){
        int isn = 0, isnc = 0, isc = 0;
        for(char j:s[i]){
            if(j == 'N'){
                isn = 1;
            }
            if(j == 'C'){
                if(isn) isnc = 1;
                isc = 1;
            }
        }
        if(isn and !isc) n_n++;
        else if(isc and !isn) n_c++;
        else if(isn and isc and !isnc) n_cn++;
        else n_nc++;
    }

    ll ans = 0;
    for(ll i=1; i<=n; i++){
        ll o = nCr(n, i);
        o *= fct[i]; o %= MOD;
        ans += o;
        ans %= MOD;
    }

    ll onlyc = 0, onlyn = 0;
    for(ll i=0; i<=n_n; i++){
        ll o = nCr(n_n, i);
        o *= fct[i]; o %= MOD;
        onlyn += o; onlyn %= MOD;
    }    

    for(ll i=0; i<=n_c; i++){
        ll o = nCr(n_c, i);
        o *= fct[i]; o %= MOD;
        onlyc += o; onlyc %= MOD;
    }

    ll nonc = (onlyc * onlyn % MOD) * (n_cn + 1) % MOD;
    nonc--;
    ans -= nonc;
    ans %= MOD;
    ans = (ans + MOD) % MOD;
    cout << ans << "\n";

    return 0;
}