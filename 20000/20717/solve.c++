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

ll poww(ll x, ll a, ll mod){
    ll ans = 1;
    while(a){
        if(a&1) ans = ans * x % mod;
        a >>= 1;
        x = x*x%mod;
    }
    return ans;
}

ll modinv(ll x, ll mod){
    return poww(x, mod-2, mod);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll v, x, m; cin >> v >> x >> m;
    ll vi = modinv(v, m);
    for(ll p=1; p<m; p++){
        ll q = p*vi%m;
        if(p/q == x){
            cout << p << " " << q << "\n";
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}