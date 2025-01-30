#include <bits/stdc++.h>
using namespace std;
 
#define ll __int128
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n
#define ld long double
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pll> v(n);
    for(int i=0; i<n; i++) {
        int o1, o2; cin >> o1 >> o2;
        v[i].X = o1; v[i].Y = o2;
    }
    v.push_back(v[0]);
    ll cx2=0, cx1=0, cy2=0, cy1=0, c0=0;

    for(int i=0; i<n; i++){
        auto [a1, b1] = v[i];
        auto [a2, b2] = v[i+1];
        cx2 += (a2*a2*a2 + a2*a2*a1 + a2*a1*a1 + a1*a1*a1)*(b2-b1);
        cy2 -= (b2*b2*b2 + b2*b2*b1 + b2*b1*b1 + b1*b1*b1)*(a2-a1);
        cx1 += 2*(a2*a2+a2*a1+a1*a1)*(b2-b1);
        cy1 -= 2*(b2*b2+b2*b1+b1*b1)*(a2-a1);
        c0 += 6*(a1+a2)*(b2-b1);
    }
    //cout << cx2 << " " << cy2 << " " << cx1 << " " << cy1 << " " << c0 << "\n";
    ll ans = c0*cx2 + c0*cy2 - 2*cy1*cy1 - 2*cx1*cx1 + (cx2+cy2)*c0;
    //cout << ans << '\n';
    cout << fixed << setprecision(12) << (ld)ans/(ld)(c0*c0) << "\n";
    return 0;
}