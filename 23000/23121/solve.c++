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

ll poww(ll a, ll e, ll p){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % p;
        e >>= 1;
        a = a * a % p;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll p, q; cin >> p >> q;
    while(q--){
        ll a, b, c, d; cin >> a >> b >> c >> d;
        if((a + b) % p != (c + d) % p){
            cout << "-1\n"; continue;
        }
        ll T = (a + b) % p;
        ll Ti = poww(T, p-2, p);
        if(a == c){
            cout << "0\n"; continue;
        }
        ll a1 = a;
        for(int i=1; i<=40; i++){
            a1 = (a1 + a1) % p;
            ll D = (a1 - c + p) * Ti % p;
            if(D < (1ll<<i)){
                cout << i << "\n"; break;
            }
        }
    }
    return 0;
}