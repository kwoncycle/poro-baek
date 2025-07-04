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

int mp[1000][1000];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int k; cin >> k;
    vector<array<int, 3>> v(k);
    for(auto &[i,j,t]:v) {
        cin >> i >> j >> t;// cout << i << " " << j << " " << t << "\n";
        mp[i][j] = t;
    }
    for(int i=1; i<1000; i++){
        for(int j=0; j<1000; j++){
            mp[i][j] = mp[i][j] + mp[i-1][j];
        }
    }
    int qq; cin >> qq;
    vector<ll> ans(3+qq, 0);
    for(int i=0; i<qq; i++){
        ll h, x, y; cin >> h >> x >> y; //cout << h << " " << x << " " << y << "\n";
        //assert(x >= 0 and y >= 0 and h >= 0);
        //h ^= ans[i]; x ^= ans[i+1]; y ^= ans[i+2];
        // if(h > n) h = n; 
        // if(x >= 300010) x = 300010;
        // if(y >= 300010) y = 300010;
        // assert(h <= n);
        ll ans1 = 0;
        for(int i=x; i<=y; i++){
            for(int j=i; j<=y; j++){
                ll cur = 0;
                for(int k=i; k<=j; k++){
                    cur += mp[h][k];
                }
                ans1 = max(ans1, cur);
            }
        }
        ans[i+3] = ans1;
        cout << ans[i+3] << "\n";
    }

    return 0;
}