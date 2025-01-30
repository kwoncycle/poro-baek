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
        e >>= 1;
        a = a * a % MOD;
    }
    return ans;
}

int DP[10001][10001];
ll inv[10001];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    DP[1][0] = 1;
    DP[2][0] = 0 + 1; DP[2][1] = 0;
    for(int i=1; i<=10000; i++) inv[i] = poww(i, MOD - 2);
    for(int i=3; i<=10000; i++){
        for(int j=0; j<i; j++){
            int J = i-1-j;
            DP[i][j] = (((ll)DP[i-2][j] - (ll)DP[j][j] + (ll)DP[i-2][J] - (ll)DP[J][J])*inv[i-1] + DP[i-1][j])%MOD;
        }
    }
    
    int tt; cin >> tt;
    for(int tc=1; tc<=tt; tc++){
        int i, j; cin >> i >> j; j--;
        ll o = (ll)DP[i][j] - (ll)DP[i-1][j]; o %= MOD;
        o = 1 - o; o %= MOD;
        if(o < 0) o += MOD;
        cout << "Case #" << tc << ": " << o << "\n";
    }
    return 0;
}