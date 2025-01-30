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


vector<ll> fct_n1(10000014);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m; cin >> n >> m;
    fct_n1[0] = 1;
    for(int i=1; i<=m+5; i++){
        fct_n1[i] = fct_n1[i-1] * ((n-1-(i-1))%m) % m;
    }

    ll ans = 0;
    for(int i=0; i<=m; i++){
        if(n-1-i > 0){
            ans += (ll)(i+1) * ( (n-1-i)%2 == 1 ? 1 : -1 ) * fct_n1[i] % m;
            ans %= m;
        }
    }
    ans %= m;
    if(ans < 0) ans += m;
    cout << ans << '\n';
    return 0;
}