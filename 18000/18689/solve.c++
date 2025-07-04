#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
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
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        int x, y, z, c;
        cin >> x >> y >> z >> c;
        vector<array<int, 3>> v(c);
        for(auto &[x0,y0,z0]:v) cin >> x0 >> y0 >> z0;
        if(c == 0) v.push_back({1, 1, 1});
        int x0 = v[0][0], x1 = v[0][0];
        int y0 = v[0][1], y1 = v[0][1];
        int z0 = v[0][2], z1 = v[0][2];
        for(auto &[xn, yn, zn]:v){
            x0 = min(x0, xn); x1 = max(x1, xn);
            y0 = min(y0, yn); y1 = max(y1, yn);
            z0 = min(z0, zn); z1 = max(z1, zn);
        }
        x0--; y0--; z0--;
        x1 = x-x1;
        y1 = y-y1;
        z1 = z-z1;
        if(x0^x1^y0^y1^z0^z1) cout << "Alice\n";
        else cout << "Bob\n";
    }
    return 0;
}