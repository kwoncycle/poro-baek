#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
__int128 operator * (pii l, pii r){return (__int128)l.X*r.X + (__int128)l.Y*r.Y;};
__int128 operator / (pii l, pii r){return (__int128)l.X*r.Y - (__int128)l.Y*r.X;};
pii operator * (pii l, ll r){return {l.X*r, l.Y*r};};

pii O = {0, 0};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    map<pii, ll> mp;
    ll ttl = 0;
    for(ll i=0; i<n; i++) {
        ll x, y, p;
        cin >> x >> y >> p;
        if(x==0 and y==0) continue;
        ttl += p;
        ll o = abs(__gcd(x, y));
        x /= o; y /= o;
        if(mp.find({x,y}) == mp.end()) mp[{x,y}] = 0;
        mp[{x,y}] += p;
    }
    if(mp.empty()){
        cout << "1557 1557\n"; return 0;
    }
    set<pii> st;
    for(auto &[p, v]:mp){
        if(p > O) st.insert(p);
        else st.insert(O-p);
    }

    vector<pii> v1;
    for(auto i:st) v1.push_back(i);
    sort(all(v1), [&](pii l, pii r){
        return l/r > 0;
    });

    vector<pair<pii, ll>> v;

    if(v1.size() == 1){
        ll sm1 = 0, sm2 = 0;
        for(auto &[p,k]:mp){
            if(p > O) sm1 += k;
            else sm2 += k;
        }
        //cout << min(sm1, sm2) << "\n";
        cout << "888484 15577\n";
        return 0;
    }
    
    ll sz = v1.size();
    v1.push_back(O-v1[0]);
    for(ll i=0; i<sz; i++){
        pii o = v1[i] + v1[(i+1)];
        v.push_back({o, 0});
        v.push_back({O-o, 0});
    }
    for(auto &[p, val]:mp) v.push_back({p, val});

    sort(all(v), [&](pair<pii, ll> l, pair<pii, ll> r){
        return (l.X > O) == (r.X > O) ? l.X/r.X > 0 : l.X < r.X;
    });

    n = v.size();
    ll sm = 0;
    ll ans = 0;
    pll ansi = {-1, -1};
    for(ll i1=0, i2=-1; i1<n; i1++){
        if(i1 > i2) {
            i2 = i1 - 1; sm = 0;
        }
        while(i2+1 < i1+n and v[i1].X / v[(i2+1)%n].X >= 0) {
            i2++;
            sm += v[i2%n].Y;
        }

        ll t1 = v[i1].Y;
        ll t2 = 0;
        if(i1 != i2 and v[i2%n].X/v[i1].X==0){
            t2 = v[i2%n].Y;
        }

        ll mx = max(sm - t1 - t2, ttl - sm) + t1 + t2;

        ll o = ttl - mx;
        if(o > ans){
            ans = o;
            ansi = v[i1].X;
        }
        sm -= v[i1].Y;
    }
    assert(abs(ansi.Y)<=2e9 and abs(ansi.X)<=2e9);
    cout << ansi.Y << " " << ansi.X << "\n";
    return 0;
}