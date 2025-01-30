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

#define MOD 1000000007

ll DP[1001][1001];
ll DP_sm[1001][1001];
ll DP_sm2[1001][1001];
ll DP1[1001][1001];

ll inv2 = (MOD + 1)/2;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    DP[1][0] = 1;
    DP_sm[1][0] = 1;
    for(int i=1; i<=1000; i++) DP_sm[1][i] = 1;
    for(int i=2; i<=1000; i++){
        for(int j=0; j<=1000; j++){
            DP[i][j] = (MOD + DP_sm[i-1][j] - (j-i >= 0 ? DP_sm[i-1][j-i] : 0)) % MOD;
            // DP[i-1][j-(i-1)] + .. + DP[i-1][j]
            DP_sm[i][j] = ((j-1 >= 0 ? DP_sm[i][j-1] : 0) + DP[i][j]) % MOD;
        }
    }

    for(int i=1; i<=1000; i++){
        for(int j=0; j<=1000; j++){
            DP_sm2[i][j] = ((j-2>=0 ? DP_sm2[i][j-2] : 0) + DP[i][j]) % MOD;
        }
    }

    DP1[1][0] = 1; // 1 1
    for(int n=2; n<=1000; n++){
        for(int i=0; i<=1000; i++){
            DP1[n][i] = DP_sm[n][i] - (i-n>=0 ? DP_sm[n][i-n] : 0) + DP_sm2[n-1][i] - (i-2*n >= 0 ? DP_sm2[n-1][i-2*n] : 0);
            DP1[n][i] %= MOD;
            DP1[n][i] = DP1[n][i] * inv2 % MOD;
            if(DP1[n][i] < 0) DP1[n][i] += MOD;
            // 1 2 3 .. n + n  ,  DP[n][i-(n-1)] + .. + DP[n][i] + DP[n-1][i] + DP[n-1][i-2] + ... + DP[n-1][i-2(n-1)]
        }
    }

    for(int i=1; i<=1000; i++){
        for(int j=1; j<=1000; j++){
            DP1[i][j] = (DP1[i][j] + DP1[i][j-1]) % MOD;
        }
    }

    int tt; cin >> tt;
    while(tt--){
        int n, a, b; cin >> n >> a >> b;
        ll ans = DP1[n][b] - (a-1>=0 ? DP1[n][a-1]:0);
        ans %= MOD;
        if(ans < 0) ans += MOD;
        cout << ans << "\n";
    }
    return 0;
}