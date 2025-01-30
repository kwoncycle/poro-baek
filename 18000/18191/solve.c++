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
    ll n, m, k; cin >> n >> m >> k;
    vector<ll> v(m);
    for(int i=0; i<m; i++) cin >> v[i];
    ll st = -1, ed = 20000000000ll;
    while(st + 1 < ed){
        ll md = (st + ed) / 2;
        ll mn = 1, mx = n;
        for(int i=0; i<m-1; i++){
            ll x = v[i+1] - v[i];
            // |uk - x| <= md
            // -md <= uk - x <= md
            // -md+x <= uk <= md + x
            ll u1, u2;
            if(md + x >= 0){
                // u <= (md + x) / k
                u1 = (md + x)/k;
            }
            else if(md + x < 0){
                // -uk >= -(md + x),  k: 1 k+1:2
                // -u >= (-(md+x)-1)/k + 1
                // u <= -((-(md+x)-1)/k + 1)
                u1 = -((-(md+x)-1)/k + 1);
            }

            if(-md + x > 0){
                // (-md+x) <= uk, (-md+x-1)/k + 1
                u2 = (-md + x - 1)/k + 1;
            }
            else if(-md + x <= 0){
                // -md + x <= uk,  (md - x) >= -uk
                // (md - x)/k >= -u
                // -(md - x)/k <= u
                u2 = -((md - x)/k);
            }
            if(u1 < u2){
                mx = -1, mn = n; break;
            }
            mx = min(n, mx + u1);
            mn = max(1ll, mn + u2);
            if(mn > mx) break;
        }
        if(mn > mx){
            st = md;
        }
        else ed = md;
    }
    cout << ed << "\n";
    return 0;
}