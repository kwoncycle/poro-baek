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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    for(int tc = 1; tc <= tt; tc++){
        ll n; cin >> n;
        ll ans = 0;
        for(ll i=2; i<=min(n-1, 1000005ll); i++){
            ll n1 = n;
            while(n1 > 1 and n1 % i == 1) {
                n1 /= i;
            }
            if(n1 == 1){
                ans = i;
                break;
            }
        }
        if(ans == 0) {
            ans = n-1;
            ll o = sqrtl(4*n-3);
            if(o*o == 4*n-3) ans = o/2;
        }
        cout << "Case #" << tc << ": " << ans << "\n";
    }
    return 0;
}