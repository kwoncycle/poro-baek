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
    int n, q; cin >> n >> q;
    vector<ll> v(n+1, 0);
    for(int i=1; i<=n; i++) cin >> v[i];
    sort(v.begin()+1, v.end());
    
    vector<ll> sm1(n+1, 0), sm2(n+2, 0);
    for(int i=1; i<=n; i++) sm1[i] = sm1[i-1] + v[i];
    for(int i=1; i<=n; i++) sm2[i] = sm2[i-1] + v[n+1-i];

    while(q--){
        ll x; cin >> x;
        int id = CNT_LOWER(v, x) - 1;
        if(id == 0){
            cout << sm1[n] - x*n << "\n";
        }
        else if(id == n){
            cout << x*n - sm2[n] << "\n";
        }
        else{
            ll smm1 = -sm1[id] + x*id;
            ll smm2 = -x*(n-id) + sm2[n-id];
            cout << smm1 + smm2 << "\n";
        }
    }
    return 0;
}