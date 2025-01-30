#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<frac,frac>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

struct frac{
    ll first, second;
    frac(ll _x, ll _y):first(_x), second(_y){
    }

    frac():first(1), second(1){

    }

    frac operator + (const frac &r){
        ll a = X*r.Y + Y*r.X, b = Y*r.Y;
        return frac(a, b);
    }

    frac operator - (const frac &r){
        ll a = X*r.Y - Y*r.X, b = Y*r.Y;
        return frac(a, b);
    }

    frac operator * (const frac &r){
        ll a = X*r.X, b = Y*r.Y;
        return frac(a, b);
    }

    frac operator / (const frac &r){
        ll a = X*r.Y, b = Y*r.X;
        if(b < 0) b *= -1, a *= -1;
        return frac(a, b);
    }

    bool operator == (const frac &r){
        return X * r.Y == r.X * Y;
    } 
    bool operator < (const frac &r) const {
        return X * r.Y < r.X * Y;
    }
};

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
frac operator * (pii l, pii r){return l.X*r.X + l.Y*r.Y;};
frac operator / (pii l, pii r){return l.X*r.Y - l.Y*r.X;};

frac cross(LINE l1, LINE l2){
    return ((l2[0]-l1[0])/l2[1])/(l1[1]/l2[1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    pii cur = pii({1,1},{1,1}); cin >> cur.X.X >> cur.Y.X;
    vector<LINE> ln(n); vector<pii> mv(n);
    for(ll i=0; i<n; i++){
        for(ll j=0; j<2; j++) cin >> ln[i][j].X.X >> ln[i][j].Y.X;
        ln[i][1] = ln[i][1] - ln[i][0];
        cin >> mv[i].X.X >> mv[i].Y.X;
    }

    if(n <= 2){
        cout << "0\n"; return 0;
    }

    ll mn = n+5;
    for(ll i=0; i<n; i++){
        vector<pair<frac,ll>> v;
        ll st = 0;
        for(ll j=0; j<n; j++){
            if(i-j){
                frac f1 = cross(ln[i], ln[j]);
                frac f2 = cross(ln[i], {ln[j][0] + mv[j] - mv[i], ln[j][1]});
                frac f3 = cross(ln[i], {cur, ln[j][1]});
                ll b = 0;
                if(f3 < f1) b = 1; // b = 1 left 0 right
                st += b;
                v.push_back({f2, b});
            }
        }
        ll mx = st;
        sort(v.begin(), v.end());
        //for(auto [x,y]:v) cout << x.X << " " << x.Y << " " << y << " --> "; cout << "\n";
        for(ll j=0; j<n-1; j++){
            ll j1 = j;
            while(j1 < n-1 and v[j1].X == v[j].X) {
                if(v[j1].Y) st -= 1;
                else st += 1;
                j1++;
            }
            mx = max(mx, st);
            j = j1-1;
        }
        mn = min(mn, n - 1 - mx);
    }

    cout << mn << "\n";
    
    return 0;
}