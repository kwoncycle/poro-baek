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

ll DP1[1000010], p2[1000010]; 
// DP[i]: # that contain i with collide, DP1[i] = DP[1] + ... + DP[i], DP2[i] = sum i*DP[i]
// .. wait, We actually don't have to use DP, just use DP1
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    p2[0] = 1;
    for(int i=1; i<1000010; i++){
        p2[i] = p2[i-1] * 2 % MOD;
    }

    int n; cin >> n;
    for(int i=2; i<=n; i++){
        int j = 1;
        ll val = 0;
        while(j*2 <= i){
            if(j & i){
                // j .. 2*j-1
                val += (p2[2*j-1] - p2[j-1]); 
                val -= (DP1[2*j-1] - DP1[j-1]);
            }
            j <<= 1;
        }
        val += DP1[i-1]; 
        DP1[i] = (DP1[i-1] + val) % MOD;
    }
    ll ans = (p2[n] - 1 - DP1[n]) % MOD;
    if(ans < 0) ans += MOD;
    cout << ans << "\n";
    return 0;
}