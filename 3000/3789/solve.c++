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

#define MOD 998244353
#define A 15571557
#define Ai 449375313
vector<ll> fct(500000), fctinv(500000);

struct solve{
    int n;
    string s;
    vector<ll> v;
    
    solve(){
        cin >> n;
        cin >> s;
        v.resize(2*n);
        ll o = 1;
        for(int i=0; i<2*n; i++){
            int i1 = i%n;
            v[i1] = (i1-1>=0 ? v[i1-1]:0) + (fct[i] * s[i1] % MOD);
            v[i1] %= MOD;
        }
        int mn = 0;
        for(int i=0; i<n; i++){
            if(gethash(i, i+n-1) == gethash(mn, mn+n-1)) continue;
            int st = -1, ed = n-1; // ed diff
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(gethash(i, i + md) != gethash(mn, mn + md)) ed = md;
                else st = md;
            }
            if(s[(i+ed)%n] < s[(mn + ed)%n]) mn = i;
        }
        cout << mn << "\n";
    }

    ll gethash(ll i, ll j){
        ll u = v[j] - (i-1>=0 ? v[i-1] : 0);
        u = u * fctinv[i] % MOD;
        if(u < 0) u += MOD;
        return u;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    fct[0] = 1; fctinv[0] = 1;
    for(int i=1; i<500000; i++){
        fct[i] = fct[i-1] * A % MOD;
        fctinv[i] = fctinv[i-1] * Ai % MOD;
    }
    int tt; cin >> tt;
    while(tt--){
        solve s;
    }
    return 0;
}