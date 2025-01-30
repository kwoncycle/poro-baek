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
    vector<pll> v(m);
    for(int i=0; i<m; i++) cin >> v[i].X >> v[i].Y;

    vector<pll> v1(m);
    for(int i=0; i<m; i++){
        v1[i].X = v[i].Y;
        v1[i].Y = n - v[i].X + v[i].Y;
    }

    sort(v1.begin(), v1.end());
    //for(auto xy:v1) cout << xy.X << " " << xy.Y << "\n";
    ll ans = 0;
    ll mx = 0;
    for(int i=0; i<m; i++){
        if(v1[i].Y <= mx) continue;
        ll o = mx - v1[i].X + 1;
        ll h = v1[i].X - v1[i].Y + n;
        h = n - h + 1;
        //cout << h << " " << o << '\n';
        ans += h*(h+1)/2;
        if(o >= 0) ans -= o*(o+1)/2;
        mx = max(mx, v1[i].Y);
    }

    cout << ans << "\n";

    return 0;
}