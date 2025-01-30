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
#define MOD 998244353ll
//#define MOD 19
ll n, k;
void f_mul(vector<ll> &f1, vector<ll> &f2, vector<ll> &out){
    vector<ll> o(n+1, 0);
    for(int i=1; i<=n; i++){
        for(int j=1; j*i<=n; j++){
            o[i*j] = (o[i*j] + f1[i]*f2[j]) % MOD;
        }
    }
    for(int i=1; i<=n; i++) out[i] = o[i];
}

void f_pow(vector<ll> &f, ll e){
    vector<ll> out(n+1, 0); out[1] = 1;
    while(e){
        if(e&1) f_mul(f, out, out);
        e /= 2;
        f_mul(f, f, f);
    }
    for(int i=1; i<=n; i++) f[i] = out[i];
}

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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> k;
    vector<ll> f(n+1, 0);
    for(int i=1; i<=n; i++) cin >> f[i];
    ll e = modInverse(k, MOD);
    f_pow(f, e);
    for(ll i=1; i<=n; i++) cout << f[i] << " "; cout << "\n";
    return 0;
}