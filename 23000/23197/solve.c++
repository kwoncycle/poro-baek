#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> pii;

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
__int128 operator * (pii l, pii r){return (__int128)l.X*r.X + (__int128)l.Y*r.Y;};
__int128 operator / (pii l, pii r){return (__int128)l.X*r.Y - (__int128)l.Y*r.X;};

ll w;
bool depth(pii p1, pii p2, pii p3){
    __int128 A = abs((p1-p2)/(p3-p2));
    __int128 B = (p1-p2)*(p1-p2);
    return (__int128)A*A <= (__int128)w*w*B;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n >> w;
    vector<pii> v(n);
    for(auto &[i,j]:v) cin >> i >> j;
    sort(all(v));
    vector<int> idx(n), loc(n);
    vector<pii> dir;
    for(int i=0; i<n; i++) idx[i] = i, loc[i] = i;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            dir.push_back({j, i});
        }
    }
    sort(all(dir), [&](pii l, pii r){
        return (v[l.Y] - v[l.X]) / (v[r.Y] - v[r.X]) > 0;
    });
    int ans = 0;
    for(int i=0; i<(int)dir.size(); i++){
        auto [i_cur, j_cur] = dir[i];
        int i1 = loc[i_cur], j1 = loc[j_cur];
        if(i1 > j1){
            swap(idx[i1], idx[j1]);
            swap(loc[i_cur], loc[j_cur]);
            swap(i1, j1);
        }
        assert(i1+1 == j1);
        int st = j1, ed = n;
        while(st + 1 < ed){
            int md = (st + ed) / 2;
            if(depth(v[idx[i1]], v[idx[j1]], v[idx[md]])) st = md;
            else ed = md;
        }
        ans = max(ans, st - i1 + 1);
        st = -1, ed = i1;
        while(st + 1 < ed){
            int md = (st + ed) / 2;
            if(depth(v[idx[i1]], v[idx[j1]], v[idx[md]])) ed = md;
            else st = md;
        }
        ans = max(ans, j1 - ed + 1);
    }
    cout << ans << "\n";
    return 0;
}