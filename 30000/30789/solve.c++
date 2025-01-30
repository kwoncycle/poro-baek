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
    ll n, m; cin >> n >> m;
    vector<ll> ai(2*n), a(2*n);
    for(ll i=0; i<2*n; i++) cin >> ai[i];
    

    vector<ll> cnt1(2*n, 0), cnt2(2*n, 0);
    ll out1, out2;
    if(true){
        for(ll i=0; i<n; i++) a[i] = ai[i] - ai[i+n];
        ll sm = 0;
        for(ll i=0; i<n; i++) sm += a[i];
        sm %= m;
        if(sm<0) sm += m;
        ll sm1 = 0;
        for(ll i=0; i<n-1; i++){
            ll u = (sm1 + a[i]) % m;
            if(u < 0) u += m;
            if(abs(sm - 2*u) > abs(sm - 2*(u-m))) u -= m;
            ll t = u - sm1;
            cnt1[i] = (t - a[i]) / m;
            a[i] += cnt1[i] * m;
            sm1 += a[i];
        }

        ll t = sm - sm1;
        cnt1[n-1] = (t - a[n-1]) / m;
        a[n-1] += cnt1[n-1] * m;
        sm1 += a[n-1];
        
        ll mx = abs(sm);
        sm1 = 0;
        for(ll i=0; i<n; i++){
            sm1 += a[i];
            mx = max(mx, abs(sm - sm1*2));
        }

        for(ll i=0; i<n; i++){
            if(cnt1[i] < 0){
                cnt1[i+n] -= cnt1[i];
                cnt1[i] = 0;
            }
        }
        out1 = mx;
    }

    if(true){
        for(ll i=0; i<n; i++) a[i] = ai[i] - ai[i+n];
        ll sm = 0;
        for(ll i=0; i<n; i++) sm += a[i];
        sm %= m;
        if(sm<0) sm += m;
        sm -= m;
        ll sm1 = 0;
        for(ll i=0; i<n-1; i++){
            ll u = (sm1 + a[i]) % m;
            if(u < 0) u += m;
            if(abs(sm - 2*u) > abs(sm - 2*(u-m))) u -= m;
            ll t = u - sm1;
            cnt2[i] = (t - a[i]) / m;
            a[i] += cnt2[i] * m;
            sm1 += a[i];
        }

        ll t = sm - sm1;
        cnt2[n-1] = (t - a[n-1]) / m;
        a[n-1] += cnt2[n-1] * m;
        sm1 += a[n-1];
        
        ll mx = abs(sm);
        sm1 = 0;
        for(ll i=0; i<n; i++){
            sm1 += a[i];
            mx = max(mx, abs(sm - sm1*2));
        }

        for(ll i=0; i<n; i++){
            if(cnt2[i] < 0){
                cnt2[i+n] -= cnt2[i];
                cnt2[i] = 0;
            }
        }
        out2 = mx;
    }

    if(out1 < out2){
        cout << out1 << "\n";
        for(ll i:cnt1) cout << i << " ";
        cout << "\n";
    }
    else{
        cout << out2 << "\n";
        for(ll i:cnt2) cout << i << " ";
        cout << "\n";
    }
    return 0;
}