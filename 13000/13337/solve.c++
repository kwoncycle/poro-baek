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

#define MOD 1000000007

ll fct[20001], fcti[20001];

ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    fct[0] = 1;
    for(int i=1; i<=10000; i++) fct[i] = fct[i-1] * i % MOD;
    ll n; cin >> n;
    ll o = (MOD + 1) / 2;
    ll ans1 = o;
    for(int i=1; i<=n; i++){
        ans1 = ans1 * i % MOD;
    }

    ll ans2 = 0;
    for(int i=1; i+i<=n; i++){

    }

    return 0;
}