#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, k, c; cin >> n >> k >> c;
    ll o = 1;
    for(ll i=0; i<c; i++) o*=n+1;

    vector<ll> v(n+1, 0), v1(n+1);
    for(ll i=0;i<n; i++) cin >> v[i];
    ll time_mn = 0x3f3f3f3f3f3f3f3fll;
    for(ll i=0; i<o; i++){
        ll i1 = i;
        for(ll j=0; j<n+1; j++) v1[j] = v[j];
        ll truth = 1;
        for(ll j=0; j<c; j++){
            v1[i1%(n+1)]--;
            if(v1[i1%(n+1)] <= 0 and i1%(n+1) < n){
                truth = 0;
            }
            i1 /= (n+1);    
        }
        assert(i1 == 0);
        if(truth){
            ll st = 0, ed = 0x3f3f3f3f3f3f3fll;
            // ed : able
            while(st+1 < ed){
                ll ttl = 0;
                ll md = (st+ed)/2;
                for(ll j=0; j<n; j++) ttl += md/v1[j];
                if(ttl >= k) ed = md;
                else st = md;
            }
            time_mn = min(time_mn, ed);
        }
        
    }
    assert(time_mn < 0x3f3f3f3f3f3f3f3fll);
    cout << time_mn << "\n";
    return 0;
}