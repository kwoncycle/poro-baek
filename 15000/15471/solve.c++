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
#define MOD 1000000007ll

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
    vector<int> primes(10001, 0);
    for(int i=2; i<=10000; i++){
        if(primes[i] == 0){
            for(int j=i; j<=10000; j+=i){
                primes[j] = i;
            }
        }
    }
    vector<vector<ll>> fct(10001), fctinv(10001);
    for(int i=1; i<=10000; i++){
        if(primes[i] == i){
            fct[i].push_back(1);
            for(int j=1; j<=i; j++){
                fct[i].push_back(fct[i][j-1] * j % MOD);
            }
            fctinv[i] = vector<ll>(i+1, 1);
            fctinv[i][i] = poww(fct[i][i], MOD - 2);
            for(int j=i; j>=1; j--){
                fctinv[i][j-1] = fctinv[i][j] * j % MOD;
            }
        }
    }
    int tt; cin >> tt;
    
    while(tt--){
        ll a, b, m; cin >> a >> b >> m;
        ll ans = 1;
        while(true){
            if(a < b){
                ans = 0; break;
            }
            if(a == b) break;
            if(b == 0) break;
            int d = 0, di = 1;
            while(di * m < a + 1){
                di *= m; d++;
            }
            // 9, 0 ~ 9, 4 -> 1, 0
            // 5, 0 -> 1, 0
            // 10, 5 -> 2, 1
            ll new_a = a / di;
            ll new_b = b / di;
            // ans *= new_a C new_b
            ll o = (fct[m][new_a] * fctinv[m][new_b] % MOD) * fctinv[m][new_a - new_b] % MOD;
            ans = ans * o % MOD;
            a = a - new_a * di;
            b = b - new_b * di;
        }
        cout << ans << "\n";
    }
    return 0;
}