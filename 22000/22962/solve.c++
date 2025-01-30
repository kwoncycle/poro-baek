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

struct Convex_hull{
    ll n, mx;
    vector<pii> v;
    vector<pii> CH;
    Convex_hull(ll _n, vector<pii> &_v): n(_n), v(_v){
        make_ch();
        rotate(CH.begin(), min_element(CH.begin(), CH.end()), CH.end());
        mx = max_element(CH.begin(), CH.end()) - CH.begin();
        n = CH.size();
    }

    void make_ch(){
        pii p = *min_element(v.begin(), v.end(), [&](pii l, pii r){ return l.Y == r.Y ? l.X < r.X : l.Y < r.Y;});
        sort(v.begin(), v.end(), [&](pii l, pii r){
            return (l-p)/(r-p) == 0 ? (l-p)*(l-p) < (r-p)*(r-p) : (l-p)/(r-p) > 0;
        });
        for(auto &pv : v){
            while((ll)CH.size() >= 2 and (CH.back() - CH[CH.size()-2]) / (pv - CH.back()) <= 0) CH.pop_back();
            CH.push_back(pv);
        }
    }

    ll isin(pii p){
        if(p < CH[0] or CH[mx] < p) return 0;
        if(p == CH[0]) return 1;
        ll l = lower_bound(CH.begin(), CH.begin() + mx, p) - CH.begin();
        ll r = lower_bound(CH.begin() + mx, CH.end(), p, [&](pii l1, pii r1){ return l1 > r1; }) - CH.begin();
        ll ld = (CH[(l-1)%n] - p)/(CH[l%n] - p), rd = (CH[(r-1)%n] - p)/(CH[r%n] - p);
        //cout << l << " " << r << "\n";
        if(ld > 0 and rd > 0) return 2;
        if(ld == 0 or rd == 0) return 1;
        return 0;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m; cin >> n >> m;
    vector<pii> v(n);
    for(ll i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    Convex_hull ch_v(n, v);
    vector<pii> sh(m);
    for(ll i=0; i<m; i++) cin >> sh[i].X >> sh[i].Y;
    if(n == 1){
        int ans = 1;
        for(ll i=0; i<m; i++) if(sh[i] == v[0]) ans = 0;
        cout << ans << "\n";
        return 0;
    }
    ll out = 0;
    for(ll i=0; i<m; i++){
        if(ch_v.isin(sh[i]) >= 1) out++;
    }
    assert(out >= 0);
    ll S = 0, A = 0, B = 0;
    n = ch_v.CH.size();
    for(ll i=0; i<n; i++){
        S += ch_v.CH[i]/ch_v.CH[(i+1)%n];
        pii l = ch_v.CH[i] - ch_v.CH[(i+1)%n];
        ll o = __gcd(abs(l.X), abs(l.Y)); //cout << o << " ";
        A += o;
    }
    assert((S - A + 2)%2 == 0);
    B = (S - A + 2)/2;
    ll ans = A + B;
    ans -= out;
    assert(ans >= 0);
    cout << ans << "\n";

    return 0;
}