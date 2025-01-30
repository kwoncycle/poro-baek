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

struct CHT{
    vector<pll> ln; // ax+b
    CHT(){}
    void insert(pll l){
        if(ln.empty()){
            ln.push_back(l); return;
        }
        while(!ln.empty() and ln.back().X == l.X and ln.back().Y > l.Y) ln.pop_back();
        while(ln.size() >= 2){
            ll sz = ln.size();
            pll o1 = cx(ln[sz-2], ln[sz-1]), o2 = cx(ln[sz-1], l);
            if((__int128)o1.X*o2.Y >= (__int128)o2.X*o1.Y) ln.pop_back();
            else break;
        }
        ln.push_back(l);
    }

    ll query(ll x){
        ll st = 0, ed = ln.size()-1; // mnrange(st) < x
        if((__int128)mnrange(ed).X < (__int128)x*mnrange(ed).Y){
            return ln[ed].X*x + ln[ed].Y;
        }
        while(st + 1 < ed){
            ll md = (st + ed)/2;
            if((__int128)mnrange(md).X < (__int128)x*mnrange(md).Y) st = md;
            else ed = md;
        }
        return ln[st].X*x + ln[st].Y;
    }

    pll mnrange(ll i){
        if(i == 0) return {0, 1};
        else{
            return cx(ln[i-1], ln[i]);
        }
    }

    pll cx(pll l, pll r){
        return {(r.Y - l.Y), (l.X - r.X)};
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    vector<pll> inp(n);
    for(ll i=0; i<n; i++) cin >> inp[i].X >> inp[i].Y;
    sort(inp.begin(), inp.end());
    vector<pll> v;
    for(ll i=0; i<n; i++){
        if(v.empty()) v.push_back(inp[i]);
        else{
            if(v.back().X <= inp[i].X and v.back().Y <= inp[i].Y){
                v.pop_back();
                i--;
                continue;
            }
            v.push_back(inp[i]);
        }
    }
    // DP[i] = min_{j=0~i-1}(DP[j] + v[i].X * v[j+1].Y)
    CHT C;
    C.insert({v[0].Y, 0});
    n = v.size();
    vector<ll> DP(n);
    for(ll i=0; i<n; i++){
        //if(i == 0) DP[i] = v[i].X * v[i].Y;
        //else{
        DP[i] = C.query(v[i].X);
        //}
        if(i+1 < n) C.insert({v[i+1].Y, DP[i]});
    }
    cout << DP[n-1] << "\n";
    //for(ll i=0; i<n; i++) cout << DP[i] << " ";
    return 0;
}