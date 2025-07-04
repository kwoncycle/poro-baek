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

vector<int> color[102][102];
pii loc(int i){
    return {1 + (i-1)/50, ((i-1)%50)*2 + 1};
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    if(n == 1){
        cout << "0\n"; return 0;
    }
    int d = 1;
    while((1<<d) < n) d++;
    for(int i=1; i<=100; i++){
        for(int j=1; j<=100; j++){
            if(j % 2 == 0 or i == 100){
                for(int t=0; t<d; t++) color[i][j].push_back(t);
            }
        }
    }
    for(int i=1; i<=n-2; i++){
        auto [x,y] = loc(i);
        for(int j=0; j<d; j++){
            if((i>>j) & 1) color[x][y].push_back(j);
        }
    }
    vector<vector<pii>> ans(d);
    
    for(int i=1; i<=100; i++){
        for(int j=1; j<=100; j++){
            for(int t:color[i][j]){
                ans[t].push_back({i, j});
            }
        }
    }
    cout << d << "\n";
    for(int t=0; t<d; t++){
        cout << ans[t].size() << " ";
        for(auto &[x,y]:ans[t]) cout << x << " " << y << " "; cout << "\n";
    }
    return 0;
}