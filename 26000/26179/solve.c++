#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> pii;

#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
__int128 operator * (pii l, pii r){return (__int128)l.X*r.X + (__int128)l.Y*r.Y;};
__int128 operator / (pii l, pii r){return (__int128)l.X*r.Y - (__int128)l.Y*r.X;};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<array<ll, 4>> v(n);
    for(auto &[i,j,k,l]:v) cin >> i >> j >> k >> l;
    ll mn_x = 0x3f3f3f3f, mx_x = -mn_x;
    ll mn_y = mn_x, mx_y = mx_x;
    for(auto &[x1,y1,x2,y2]:v){
        mn_x = min(mn_x, x2);
        mx_x = max(mx_x, x1);
        mn_y = min(mn_y, y2);
        mx_y = max(mx_y, y1);
    }
    if(mx_x <= mn_x or mx_y <= mn_y){
        cout << "possible\n";
        return 0;
    }

    return 0;
}