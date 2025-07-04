#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<long double,long double> pii;
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
ll operator * (pii l, pii r){return l.X*r.X + l.Y*r.Y;};
#define ld long double

double dst(pii l, pii r){
    return sqrt((l-r)*(l-r));
}

vector<pii> v;

ld mn(ld x){
    ld st = -1000, ed = 1000;
    while(st + 0.00000001 < ed){
        ld md1 = (st + st + ed) / 3, md2 = (st + ed + ed) / 3;
        ld D1 = 0, D2 = 0;
        for(auto &p:v){
            D1 += dst(p, {x, md1});
            D2 += dst(p, {x, md2});
        }
        if(D1 < D2) ed = md2;
        else st = md1;
    }
    ld D = 0;
    for(auto &p:v){
        D += dst(p, {x, ed});
    }
    return D;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    v.resize(n);
    for(auto &[i,j]:v) cin >> i >> j;

    ld ans = 0x3f3f3f3f;
    for(int i=0; i<n; i++){
        ld sm = 0;
        for(int j=0; j<n; j++) sm += dst(v[i], v[j]);
        ans = min(ans, sm/(ld)(n-1));
    }

    cout << fixed << setprecision(15) << ans << "\n";
    return 0;


    long double stx = -1000, edx = 1000;
    while(stx + 0.00000001 < edx){
        ld md1 = (stx + stx + edx) / 3, md2 = (stx + edx + edx) / 3;
        ld D1 = mn(md1), D2 = mn(md2);
        if(D1 < D2) edx = md2;
        else stx = md1;
    }

    cout << fixed << setprecision(15) << mn(stx)/(double)n << "\n";

    return 0;
}