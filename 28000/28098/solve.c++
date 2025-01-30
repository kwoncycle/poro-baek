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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    pii O = {0,0};
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    sort(v.begin(), v.end(), [&](pii l, pii r){ return (l > O) == (r > O) ? (l/r) > 0 : l < r;});
    vector<pii> v1;
    for(int i=0; i<n; i++){
        if(v[(i+1)%n]/v[i] == 0 and v[(i+1)%n]*v[i] > 0) continue;
        v1.push_back(v[i]);
    }
    v = v1;
    n = v.size();
    if(n <= 1) {
        cout << "Yes\n"; return 0;
    }
    int truth = 0;
    for(int i=0; i<n; i++){
        if(v[(i+1)%n]/v[i] >= 0) {truth = 1; break;}
    }
    if(truth) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}