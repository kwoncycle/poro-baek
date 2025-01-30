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
    int n; cin >> n;
    vector<ll> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    ll mn = *min_element(a.begin(), a.end()); mn--;
    ll mx = 1000000000ll;
    while(mn + 1 < mx){
        ll mid = (mn + mx)/2;
        vector<ll> DP(1<<n, 9999999999ll);
        for(int i=0; i<(1<<n); i++){
            for(int j=0; j<n; j++){
                if(i == (1<<j)){
                    if(a[j] <= mid){
                        DP[i] = a[j];
                    }
                    break;
                }
                else{
                    if(i & (1<<j)){
                        ll u = max(DP[i - (1<<j)] + a[j], a[j]);
                        if(u <= mid) DP[i] = min(DP[i], u);
                        else continue;
                    }
                }
            }
        }
        if(DP[(1<<n)-1] <= mid) mx = mid;
        else mn = mid;
    }
    cout << mx << "\n";
    return 0;
}