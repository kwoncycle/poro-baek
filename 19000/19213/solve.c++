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

#define MOD 1000000007

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
    ll n; cin >> n;
    // E(x_n) = (E(X0) + ... + E(X_n-1))/n*2;

    // E(X_n^2) = 2/n * (E(X0)+...+E(Xn-1)/n)^2 + 2*(E(X_0^2) + ... + E(X_n-1^2))/n
    ll ninv = poww(n, MOD - 2);
    vector<ll> EX(n+1), EX2(n+1);
    EX[0] = 1;
    EX2[0] = 1;
    vector<ll> EXsm(n+1), EX2sm(n+1);

    EXsm[0] = 1;
    EX2sm[0] = 1;
    for(int i=1; i<=n; i++){
        EX[i] = EXsm[i-1] * ninv * 2 % MOD;
        EX2[i] = ((2 * ninv * ninv % MOD) * EXsm[i-1] % MOD) * EXsm[i-1] % MOD + 2 * ninv * EX2sm[i-1] % MOD;
        EX2[i] %= MOD;
        EXsm[i] = (EXsm[i-1] + EX[i]) % MOD;
        EX2sm[i] = (EX2sm[i-1] + EX2[i]) % MOD;
    }

    ll v = (EX2[n] - EX[n]*EX[n]) % MOD;
    v = (v + MOD) % MOD;
    cout << v << "\n";
    //cout << v % MOD << "\n";
    return 0;
}