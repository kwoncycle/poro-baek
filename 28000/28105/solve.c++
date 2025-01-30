#include <bits/stdc++.h>
using namespace std;
#define ll long long int
ll pow(ll a,ll x,ll m){
	if(x==1) return a%m;
	if(x==0) return 1;
	ll v = pow(a, x/2, m);
	v = v*v%m;
	if(x%2) v = v*a%m;
	return v;
}
// a^x (mod m)
 
ll modInverse(ll A, ll M){
    ll m0 = M;
    ll y = 0, x = 1;
    if (M == 1)
        return 0;
    while (A > 1) {
        ll q = A / M;
        ll t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}
#define MOD 998244353

ll fct[1000010] = {1,1}, fctinv[1000010] = {1,1};
int main(){
    ll n, x, y;
    cin >> n >> x >> y;
    for(ll i=2; i<2*n+6; i++){
        fct[i] = fct[i-1]*i%MOD;
        fctinv[i] = modInverse(fct[i], MOD);
    }
    ll ans = 0;
    if(x>y){
        x ^= y; y ^= x; x ^= y;
    }
    for(ll i=0; i<=y-x-1; i++){
        if((x-1+i)%2) continue;
        if(x-1<i or 2*n-y<y-x-1-i) continue;
        ll tmp = 1;
        ll a = (x-1+i)/2, b = (x-1-i)/2;
        tmp *= (a+1-b); tmp %= MOD;
        tmp *= fct[a+b]; tmp %= MOD;
        tmp *= fctinv[a+1]; tmp %= MOD;
        tmp *= fctinv[b]; tmp %= MOD;
        
        a = (2*n-y+(y-x-1-i))/2, b = (2*n-y-(y-x-1-i))/2;
        tmp *= (a+1-b); tmp %= MOD;
        tmp *= fct[a+b]; tmp %= MOD;
        tmp *= fctinv[a+1]; tmp %= MOD;
        tmp *= fctinv[b]; tmp %= MOD;
        
        tmp *= fct[y-x-1]; tmp %= MOD;
        tmp *= fctinv[i]; tmp %= MOD;
        tmp *= fctinv[y-x-1-i]; tmp %= MOD;

        ans += tmp; ans %= MOD;
    }

    cout << ans;
}