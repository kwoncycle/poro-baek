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

#define ld long double
ll dst(pii l, pii r){
    return (ll)(l.X-r.X)*(l.X-r.X) + (ll)(l.Y-r.Y)*(l.Y-r.Y);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    vector<pii> tmp(n-1);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    ld mn = 1e10;
    for(int i=0; i<n; i++){
        int idx = 0;
        for(int j=0; j<n; j++){
            if(i-j) tmp[idx++] = v[j];
        }
        sort(tmp.begin(), tmp.end(), [&](pii l, pii r){
            return (l > v[i]) == (r > v[i]) ? (l - v[i])/(r - v[i]) > 0 : l < r;
        });
        for(int j=0; j<n-1; j++){
            ll area = (tmp[j]-v[i])/(tmp[(j+n)%(n-1)]-v[i]);
            area = abs(area);
            mn = min(mn, (ld)area/sqrt((ld)dst(tmp[(j+n)%(n-1)], v[i])));
            area = (tmp[(j+n-2)%(n-1)]-v[i])/(tmp[j]-v[i]);
            area = abs(area);
            mn = min(mn, (ld)area/sqrt((ld)dst(tmp[(j+n-2)%(n-1)], v[i])));
        }
    }

    cout << fixed << setprecision(10) << mn << "\n";
    return 0;
}