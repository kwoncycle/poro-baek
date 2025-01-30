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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

struct frac{
    ll x, y;
    frac(ll x, ll y):x(x),y(y){}
    bool operator < (const frac r) const{
        return (__int128)x*r.y < (__int128)r.x*y;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    ll l = 50000, r = -50000;
    for(int i=0; i<n; i++){
        if(v[i].Y == 0){
            l = min(l, (ll)v[i].X);
            r = max(r, (ll)v[i].X);
        }
    }
    v.push_back(v[0]);
    ll A = 0, G = 0;
    for(int i=0; i<n; i++){
        A += v[i]/v[i+1];
        G += (v[i].X + v[i+1].X) * (v[i]/v[i+1]);
    }
    G = G * (A / abs(A)); A = abs(A);
    // A /= 2, G /= 3*A
    pair<frac,frac> wt = {frac(-5,1), frac(0x3f3f3f3f3f3f3fll,1)};
    {
        if(v[0].X == r){
            if(G > r*A*3){
                cout << "unstable\n"; return 0;
            }
        }

        if(v[0].X == l){
            if(l*A*3 > G){
                cout << "unstable\n"; return 0;
            }
        }

        if(v[0].X < r){
            ll a1 = G-3*r*A, a2 = (r-v[0].X)*6;
            wt.X = max(frac(a1, a2), wt.X);
        }
        else if(v[0].X > r){
            ll a1 = -(G-3*r*A), a2 = (-r+v[0].X)*6;
            wt.Y = min(frac(a1, a2), wt.Y);
        }

        if(l < v[0].X){
            ll a1 = 3*l*A - G, a2 = (v[0].X - l)*6;
            wt.X = max(frac(a1, a2), wt.X);
        }
        else if(l > v[0].X){
            ll a1 = -(3*l*A - G), a2 = (l - v[0].X)*6;
            wt.Y = min(frac(a1, a2), wt.Y);
        }
    }
    if(wt.Y < wt.X) cout << "unstable\n";
    else if(wt.Y < frac(0, 1)){
        cout <<"unstable\n";
    }
    else{
        if(wt.X < frac(0,1)) cout << "0";
        else{
            cout << (wt.X).x/(wt.X).y;
        }

        cout << " .. ";
        
        ll a1 = (wt.Y).x, a2 = (wt.Y).y;
        if(frac(0x3f3f3f3f3f3f31ll, 1) < wt.Y) cout << "inf\n";
        else cout << (a1 + a2 - 1)/a2 << "\n";
    }
    return 0;
}