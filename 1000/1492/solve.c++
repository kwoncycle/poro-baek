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
    ll n, k; cin >> n >> k;
    vector<vector<ll>> v(k+2, vector<ll>(k+2));
    vector<ll> outp(k+2, 0);
    for(ll i=0; i<k+2; i++){
        ll fi = 0;
        for(int j=1; j<=i+1; j++){
            fi = (fi + poww(j, k)) % MOD;
        }
        outp[i] = fi;
        for(int j=0; j<k+2; j++){
            v[i][j] = poww(i+1, j);
        }
    }

    for(int i=0; i<k+2; i++){
        for(int j=i+1; j<k+2; j++){
            ll t = v[j][i] * poww(v[i][i], MOD - 2) % MOD;
            for(int j1=0; j1<k+2; j1++){
                v[j][j1] = (v[j][j1] - v[i][j1] * t) % MOD;
            }
            outp[j] -= outp[i] * t;
            outp[j] %= MOD;
        }
    }

    for(int i=k+1; i>=0; i--){
        for(int j=0; j<i; j++){
            ll t = v[j][i] * poww(v[i][i], MOD - 2) % MOD;
            outp[j] -= outp[i]*t;
            outp[j] %= MOD;
            v[j][i] -= v[i][i]*t;
            v[j][i] %= MOD;
        }
    }
    for(int i=0; i<k+2; i++){
        outp[i] = (outp[i] * poww(v[i][i], MOD - 2)) % MOD;
    }

    ll ans = 0;
    for(int i=0; i<k+2; i++){
        ans = (ans + poww(n, i)*outp[i]) % MOD;
    }
    ans %= MOD;
    if(ans < 0) ans += MOD;
    cout << ans << "\n";
    return 0;

    for(int i=0; i<k+2; i++){
        for(int j=0; j<k+2; j++){
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}