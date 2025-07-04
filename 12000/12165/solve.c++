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

const pii O = {0,0};

struct solve{
    int n;
    vector<pii> v;
    solve(){
        cin >> n;
        v.resize(n);
        for(auto &[i,j]:v) cin >> i >> j;
        if(n <= 3){
            while(n--) cout << "0\n";
            return;
        }
        for(int i=0; i<n; i++){
            vector<pii> P;
            for(int j=0; j<n; j++){
                if(i == j) continue;
                P.push_back(v[j] - v[i]);
            }
            sort(all(P), [&](pii l, pii r){
                return (l>O) == (r>O) ? (l/r) > 0 : l < r;
            });
            int ans = n-1;
            for(int i0=0, i1=0; i0<n-1; i0++){
                if(i1 < i0) i1 = i0;
                while((i1+1-i0 < n-1) and P[i0]/P[(i1+1)%(n-1)] >= 0) i1++;
                ans = min(ans, n-1 - (i1-i0+1));
            }
            cout << ans << "\n";
        }
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    for(int tc=1; tc<=tt; tc++){
        cout << "Case #" << tc << ":\n";
        solve S;
    }
    return 0;
}