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

pii operator + (pii l, pii r){ return {l.X+r.X, l.Y+r.Y};}
pii operator - (pii l, pii r){ return {l.X-r.X, l.Y-r.Y};}
ll operator / (pii l, pii r){ return (ll)l.X*r.Y - (ll)l.Y*r.X;}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> p(n);
    for(int i=0; i<n; i++) cin >> p[i].X >> p[i].Y;
    ll ans = 0;
    for(int i=0; i<n; i++){
        ans += p[i]/p[(i+1)%n];
    }
    ans = abs(ans);
    cout << fixed << setprecision(1) << (double)ans/2.0 << "\n";
    return 0;
}