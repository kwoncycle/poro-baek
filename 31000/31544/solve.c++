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
        e >>= 1; a = a*a%MOD;
    }
    return ans;
}

ll modinv(ll a){
    return poww(a, MOD - 2);
}


int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    ll n, m, k; cin >> n >> m >> k;
    vector<ll> DP(1000001, 0), DP2(1000001, 0);
    vector<ll> isprime(1000001, 0);
    isprime[1] = 1;
    for(ll i=2; i<=1000000; i++){
        if(isprime[i] == 0){
            isprime[i] = 1;
            for(ll j=i*2; j<=1000000; j+=i) isprime[j]++;
            for(ll j=i*i; j<=1000000; j+=i*i) isprime[j] = -999999;
        }
    }
    vector<ll> frac;
    for(ll i=1; i<=n; i++){
        if(n%i == 0) frac.push_back(i);
    }    

    vector<vector<ll>> fracs(1000001);
    for(ll i:frac){
        
        for(ll j:frac){
            if(j > i) break;
            if(i % j == 0) fracs[i].push_back(j);
        }
    }
    ll ans = 0;
    for(ll i:frac){
        DP2[i] = poww(2, i) - 1;
        for(ll j:fracs[i]){ // j = length
            if(i == j) continue;
            DP2[i] -= DP2[j];
            DP2[i] %= MOD;
        }
        DP[i] = DP2[i]*modinv(i)%MOD;
        //cout << i << " " << DP[i] << " " << DP2[i] << "\n";
        //for(ll j:fracs[i]){
        //    if(i == j) continue;

            //DP[i] += DP[j];
        //    DP[i] %= MOD;
        //}
        cout << i << " " << DP[i] << " " << DP2[i] << "\n";
        if((n/i)%2 == 1) ans += DP[i]; 
        else ans += DP[i]/2;
        ans %= MOD;
    }
    ll ans1 = 0;
    ans1 = ans * m % MOD;
    for(int i=0; i<m-1; i++){
        ans1 += (poww(2, (i+1)*n) - 1); ans1 %= MOD;
    }

    cout << ans1 << "\n";
    
    int sm = 0;
    vector<int> v1(n+1, 0);
    for(int i=1; i<=n; i++) v1[i] = i;

    vector<int> cnt(n, 0);
    for(int i=0; i<(1<<n); i++){
        int s = 0;
        for(int j=0; j<n; j++){
            if(i&(1<<j)) s += v1[j];
        }
        int truth = 1;
        for(int j=1; j<n; j++){
            vector<int> v2, v3;
            for(int j1=0; j1<n; j1++){
                if(i&(1<<j1)){
                    v2.push_back(j1);
                    v3.push_back((j1+j)%n);
                }
            }
            sort(v3.begin(), v3.end());
            int diff = 0;
            for(int j1=0; j1<(int)v2.size(); j1++){
                if(v2[j1] != v3[j1]) diff = 1;
            }
            if(!diff) truth = 0;
        }
        if(truth)
        cnt[s%n]++;
    }
    for(int c:cnt) cout << c << " "; cout << "\n";
    return 0;
}