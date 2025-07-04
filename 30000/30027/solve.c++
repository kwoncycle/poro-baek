#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<pii> v(k);
    for(auto &[i,j]:v) cin >> i >> j;
    ll ans = 0;
    vector<pii> p = {{1,1}, {1, m}, {n, 1}, {n, m}};
    for(auto &[x,y]:p){
        ll mn = 0x3f3f3f3f;
        for(auto &[i,j]:v){
            mn = min(mn, (ll)(abs(x-i) + abs(y-j)));
        }
        ans = max(ans, mn);
    }

    if(k > 1){
        ll ans1 = 0x3f3f3f3f;
        for(int i=0; i<k; i++){
            for(int j=i+1; j<k; j++){
                pii t = v[i] - v[j];
                ans1 = min(ans1, (ll)(abs(t.X) + abs(t.Y))/2);
            }
        }
        ans = max(ans, ans1);
    }
    cout << ans << "\n";
    return 0;
}