#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;
ll DP[1000055]; // A1..Ar, B1..Br, DP[i]: # of case s.t B1 == i, A1 > i

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    if(n <= 3){
        int ans = 1; 
        while(n >= 1) ans *= n--;
        cout << ans << "\n"; return 0;
    }
    for(int i=4; i<=1000000; i+=4){
        DP[i] = 1; DP[i+1] = 1; DP[i+3] = 1;
    }
    
    for(int i=5; i<=1000000; i++){
        ll a = (DP[i] + 1) % MOD;
        DP[i+1] += a;
        for(int j=i+i; j<=1000000; j+=i){
            DP[j-1] += a; DP[j] += a; DP[j+1] += a;
        }
        DP[i] = a;
    }
    ll ans = 0;
    for(int i=1; i<=n-1; i++) ans += DP[i];
    ans %= MOD;
    ans = (ans*4 + 4) % MOD * n % MOD;
    cout << ans << "\n";
    
    return 0;
}