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
    int n;
    vector<pii> v;
    vector<int> chosen;
    solve(){
        cin >> n;
        v.resize(n); chosen.resize(n);
        for(auto &[i,j]:v) cin >> i >> j;
        while(true){
            int max_x = 0, max_y = 0;
            for(auto &[x,y]:v){
                max_x = max(x, max_x);
                max_y = max(y, max_y);
            }
            vector<pii> v1;
            for(auto &[x,y]:v){
                if(x == max_x and y == max_y){
                    cout << "YES\n"; return;
                }
                if(x != max_x and y != max_y) v1.push_back({x, y});
            }
            v = v1;
            if(v.empty()) break;
        }
        cout << "NO\n";
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    for(int tc=1; tc<=tt; tc++){
        cout << "Case #" << tc << ": ";
        solve S;
    }
    return 0;
}