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

struct solve{
    ll n, m, q;
    vector<pll> T;
    vector<ll> Tsm, L, extra, dead;
    solve(){
        cin >> n >> m >> q;
        T.resize(n+2); Tsm.resize(n+2); L.resize(m+2); extra.resize(n+2); dead.resize(n+2);
        for(int i=1; i<=n; i++) cin >> T[i].X;
        for(int i=1; i<=n; i++) cin >> T[i].Y;
        T[n+1] = {0, 20000000000000000ll};
        for(int i=1; i<=m; i++) cin >> L[i];
        L[m+1] = 21000000000000000ll;
        sort(T.begin()+1, T.end(), [&](pll l, pll r){
            return l.Y < r.Y;
        });
        n++; m++;
        for(int i=1; i<=n; i++){
            Tsm[i] = Tsm[i-1] + T[i].X;
            dead[i] = T[i].Y;
        }
        for(int i=1; i<=m; i++){
            L[i] = L[i] + L[i-1];
        }
        extra[n] = T[n].Y - Tsm[n];
        for(int i=n-1; i>=1; i--){
            extra[i] = min(extra[i+1], T[i].Y - Tsm[i]);
        }
        extra[0] = extra[1];
        while(q--){
            ll t; cin >> t;
            int id = CNT_UPPER(dead, t);
            ll ans = min(extra[id], t - Tsm[id-1]);
            ll cnt = CNT_UPPER(L, ans) - 1;
            cout << cnt << " ";
        }
        cout << "\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        solve S;
    }
    return 0;
}