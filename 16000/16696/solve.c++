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

ll n;

bool goal(bitset<64> b, vector<ll> &v){
    for(ll i:v) b = b | (b>>i);
    ll id = 0;
    while(id<n and b[id] == 1) id++;
    return id >= n;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    n = s.size();
    ll b = 0, b1 = 0;
    for(ll i=0; i<n; i++) {
        b <<= 1;
        if(s[i] == '1') b++;
    }
    if((b&(1ll<<(n-1))) == 0) cout << "-1\n";
    else{
        if(b == (1ll<<(n-1))){
            ll cnt = 0, u=1;
            while(u < n){
                u <<= 1; cnt++;
            }
            cout << cnt << "\n";
            return 0;
        }
        ll mn = 5;
        for(ll i=0; i<30*30*30*30; i++){
            ll i1 = i, cnt = 0;
            b1 = b;
            while(i1%30){
                ll o = i1%30;
                b1 = b1 | (b1>>o);
                i1/=30;
                cnt++;
            }
            ll id = 0;
            if(b1 == (1ll<<n)-1) mn = min(mn, cnt);
        }
        cout << mn << "\n";
    }
    return 0;
}