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

class djs
{
    int n;
    vector<int> par;
 
public:
    djs(int n) : n(n) {
        par.resize(n);
        for(int i=0; i<n; i++) par[i] = i;
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
 
    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);
 
        if(px == py) return false;
 
        par[px] = py;
        return true;
    }
};
// Usage: djs DJS(n)

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        vector<pii> v(n);
        for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
        djs DJS(2*n+1);
        vector<int> cnt1(2*n+1), cnt2(2*n+1);
        for(auto [x,y]:v) DJS.Union(x,y);
        for(int i=1; i<=2*n; i++) cnt1[DJS.find(i)]++;
        for(auto [x,y]:v){
            cnt2[DJS.find(x)]++;
        }
        int truth = 1;
        for(int i=1; i<=2*n; i++){
            if(cnt1[i] < cnt2[i]) truth = 0;
        }
        if(truth) cout << "possible\n";
        else cout << "impossible\n";
    }
    return 0;
}