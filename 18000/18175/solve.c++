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

typedef long double ld;

ll n, r, a, b;

ld dst(pii l, pii r){
    return sqrt((ld)((l-r)*(l-r)));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> r >> a >> b;
    pii p0 = {0, 0}, p1 = {a, b};
    vector<ld> add;
    vector<pair<ld,ld>> Q;
    ld mn = 0, mx = dst(p0, p1);
    while(n--){
        pii p; cin >> p.X >> p.Y;
        ld H = abs(p1/p) / dst(p0, p1);
        ld D = sqrt(p*p - H*H);
        if(p*p1 < 0) D = -D;
        if(H > r) continue;
        ld Da = sqrt(r*r - H*H);
        ld D0 = D-Da, D1 = D+Da;
        add.push_back(D0); add.push_back(D1);
        Q.push_back({D0, D1});
    }
    add.push_back(-0x3f3f3f3f); add.push_back(0x3f3f3f3f);
    sort(all(add));
    add.erase(unique(all(add)), add.end());
    map<ld, int> mp;
    for(int i=0; i<(int)add.size(); i++){
        mp[add[i]] = i;
    }
    vector<int> P(add.size());
    for(auto [i,j]:Q){
        P[mp[i]]++; P[mp[j] + 1]--;
    }
    for(int i=1; i<P.size(); i++){
        P[i] += P[i-1];
    }

    int ans = 0;
    for(int i:P) ans = max(ans, i);
    cout << ans << "\n";
    return 0;
}