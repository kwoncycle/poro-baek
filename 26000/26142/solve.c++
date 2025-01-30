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
    ll n; cin >> n;
    vector<pll> dh(n+1);
    for(int i=1; i<=n; i++){
        cin >> dh[i].X >> dh[i].Y;
    }

    sort(dh.begin(), dh.end());

    vector<ll> ans(n+1, 0);
    ans[1] = dh[1].Y;
    for(ll i=2; i<=n; i++){
        for(ll j=i; j>=1; j--){
            ans[j] = max(ans[j], ans[j-1] + dh[i].X*(j-1) + dh[i].Y);
        }
    }

    for(auto i=ans.begin() + 1; i< ans.end(); i++) cout << *i << "\n";
    
    return 0;
}