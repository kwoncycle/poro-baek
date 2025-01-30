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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

vector<ll> ans(101, 0x3f3f3f3f3f3f);
vector<ll> ans1(101, 0x3f3f3f3f3f3f);
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    vector<ll> v(n);
    for(ll i=0; i<n; i++) cin >> v[i];
    sort(v.begin(), v.end());

    for(ll i=1; i<=100000; i++){
        ll mx = 0;
        for(ll j=0; j<n; j++){
            ll j1 = j, o = v[j]/i;
            while(j1 < n and v[j1]/i == o) j1++;
            ans[j1-j] = min(ans[j1-j], (ll)i);
            j = j1-1;
        }
        
    }

    for(ll d=0; d<=1001; d++){
        for(ll i=0; i<n; i++){
            for(ll j=i; j<n; j++){
                //if(a[i]/(d+1) + 1 <= X <= a[i]/d)
                ll mn = (v[j]/(d+1) + 1), mx = d>0 ? (v[i]/d) : 0x3f3f3f3f3fll;
                ll mn1 = i-1 >= 0 ? (d>0 ? ((v[i-1]/d) + 1) : 0x3f3f3f3f3f3fll) : -1557, mx1 = j+1 < n ? v[j+1]/(d+1) : 0x3f3f3f3f3f3fll;
                mn = max(mn, mn1), mx = min(mx, mx1);
                if(mn <= mx) ans[j-i+1] = min((ll)ans[j-i+1], mn);
            }
        }
    }
    
    for(ll i=1; i<=n; i++) cout << (ans[i]<=v[n-1]+1 ? ans[i] : -1) << "\n";
    return 0;
}