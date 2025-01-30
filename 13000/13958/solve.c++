#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
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
    ll n; cin >> n;
    vector<pii> v(n), v1;
    ll up_same = 0, down_same = 0, same_up = 0, same_down = 0, same = 0;
    for(ll i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    ll rank = 1;
    for(ll i=1; i<n; i++){
        if(v[i].X > v[0].X and v[i].Y > v[0].Y) {
            rank++;
            continue;
        }
        if(v[i].X < v[0].X and v[i].Y < v[0].Y) continue;
        if(v[i] == v[0]) same++;
        else if(v[i].X == v[0].X){
            if(v[i].Y > v[0].Y) same_up++;
            else same_down++;
        }
        else if(v[i].Y == v[0].Y){
            if(v[i].X > v[0].X) up_same++;
            else down_same++;
        }
        else v1.push_back(v[i]);
    }

    ll pos = 0, neg = 0;

    for(auto &[x, y]:v1){
        x -= v[0].X; y -= v[0].Y;
        if(x > 0) pos++;
        else neg++;
    }

    sort(v1.begin(), v1.end(), [&](pii l, pii r){
        return abs(l.X)*abs(r.Y) > abs(r.X)*abs(l.Y);
    });

    ll curpos = 0, curneg = 0;
    ll n1 = v1.size();
    ll best = v1.size() + up_same + same_up, worse = up_same + same_up + same;
    //for(auto [x,y]:v1) cout << x << " " << y << " v1\n";
    for(ll i=0; i<n1; i++){
        ll i1 = i;
        ll posnow = 0, negnow = 0;
        while(i1 < n1 and v1[i1].X*v1[i].Y == v1[i].X*v1[i1].Y){
            if(v1[i1].X > 0) posnow++;
            else negnow++;
            i1++;
        }

        ll low = curpos + (neg - curneg - negnow) + up_same + same_up;
        ll high = i1 - i + low + same;
        best = min(best, low);
        worse = max(worse, high);
        i = i1-1;
        curpos += posnow;
        curneg += negnow;
    }

    // (0, +)
    best = min(best, (ll)neg + same_up);
    worse = max(worse, (ll)neg + same_up + up_same + down_same + same);
    // (+, 0)
    best = min(best, (ll)pos + up_same);
    worse = max(worse, (ll)pos + up_same + same_up + same_down + same);

    cout << best + rank << " " << worse + rank << "\n";

    return 0;
}