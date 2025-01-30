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

#define MOD 1000003
ll comb[55][55];
string s[51];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    comb[0][0] = 1;
    for(int i=1; i<=51; i++){
        comb[i][0] = 1;
        comb[i][i] = 1;
        for(int j=1; j<i; j++){
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
        }
    }
    int n, k; cin >> n >> k;
    
    for(int i=0; i<n; i++) cin >> s[i];
    ll poww[55];
    poww[0] = 1;
    for(int i=1; i<=52; i++){
        poww[i] = poww[i-1] * 26 % MOD;
    }
    vector<ll> cnt(n+1);
    for(int i=0; i<(1<<n); i++){
        int i1 = i;
        int c = 0;
        string T((int)s[0].size(), '?');
        int truth = 1;
        for(int j=0; j<n; j++){
            if(i & (1<<j)){
                c++;
                for(int t=0; t<(int)s[j].size(); t++){
                    if(s[j][t] != '?' and T[t] != '?' and T[t] != s[j][t]){
                        truth = 0; break;
                    }
                    if(s[j][t] != '?') T[t] = s[j][t];
                }
            }
            if(!truth) break;
        }
        int ask = 0;
        for(char t:T){
            if(t == '?') ask++;
        }
        cnt[c] = (cnt[c] + (truth ? poww[ask] : 0)) % MOD;
    }

    ll ans = 0;
    for(int i=k; i<=n; i++){
        ans += (((i-k)%2 == 0 ? 1 : -1) * comb[i][k] * cnt[i] % MOD);
        ans %= MOD;
    }
    ans %= MOD;
    if(ans < 0) ans += MOD;
    cout << ans << "\n";
    return 0;
}