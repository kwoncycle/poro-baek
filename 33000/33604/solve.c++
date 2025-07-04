#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<ll,ll> pii;
typedef pair<ll,ll> pll;

#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
__int128 operator * (pii l, pii r){return (__int128)l.X*r.X + (__int128)l.Y*r.Y;};
__int128 operator / (pii l, pii r){return (__int128)l.X*r.Y - (__int128)l.Y*r.X;};
pii operator * (pii l, ll r){return {l.X*r, l.Y*r};};

pll nxt(pll t, ll d){
    if(t.Y <= d) return {d-t.Y, d+t.Y};
    if(t.X >= d) return {t.X-d, t.Y+d};
    return {0, t.Y+d};
}

bool on_line(pll l1, pll r1, pll p){
    return (l1-r1)/(l1-p)==0 and (l1-p)*(r1-p) <= 0;
}

pair<pll, int> C(pll l1, pll r1, pll l2, pll r2){
    if(on_line(l2, r2, l1)) return {l1, 1};
    if(on_line(l2, r2, r1)) return {r1, 1};
    if(on_line(l1, r1, l2)) return {l2, 1};
    if(on_line(l1, r1, l2)) return {r2, 1};
    if((l1-r1)/(l2-r2) == 0){
        return {l1, 0};
    }
    __int128 D1 = (l2-l1)/(r2-l2), D2 = (r1-l1)/(r2-l2);
    if(D2<0){
        D1 *= -1; D2 *= -1;
    }
    if(0 <= D1 and D1 <= D2){
        pll P = r1 - l1;
        if((__int128)P.X*D1%D2 or (__int128)P.Y*D1%D2){
            return {l1, 0};
        }
        P = {(__int128)P.X*D1/D2, (__int128)P.Y*D1/D2};
        pll U = l1 + P;
        if(on_line(l1, r1, U) and on_line(l2, r2, U)) return {U, 1};
        else return {l1, 0};
    }
    return {l1, 0};
}

pll dir[4] = {{1,0}, {0,1}, {-1, 0}, {0, -1}};

pll cross(pll p1, ll d1, pll p2, ll d2){
    vector<pll> V1, V2;
    for(int i=0; i<4; i++){
        V1.push_back(p1 + dir[i]*d1);
    }
    for(int i=0; i<4; i++){
        V2.push_back(p2 + dir[i]*d2);
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            auto [x,y] = C(V1[i], V1[(i+1)%4], V2[j], V2[(j+1)%4]);
            if(y){
                return x;
            }
        }
    }
    assert(false);
    return {-1557, -1557};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n; n--;
    pll p; cin >> p.X >> p.Y;
    vector<ll> v(n);
    for(auto &i:v) cin >> i;

    vector<pll> rng(n+1);
    ll d = abs(p.X) + abs(p.Y);
    ll sm = 0;
    for(ll i:v) sm += i;
    if(d%2 != sm%2){
        cout << "NO\n"; return 0;
    }
    
    rng[0] = {d, d};
    for(int i=1; i<=n; i++){
        rng[i] = nxt(rng[i-1], v[i-1]);
    } 

    if(rng[n].X != 0){
        cout << "NO\n"; return 0;
    }

    vector<ll> dst(n+1);
    for(int i=n-1; i>=0; i--){
        ll cur = dst[i+1];
        ll v1 = abs(cur - v[i]), v2 = cur + v[i];
        if(rng[i].X <= v1 and v1 <= rng[i].Y){
            dst[i] = v1;
        }
        else if(rng[i].X <= v2 and v2 <= rng[i].Y){
            dst[i] = v2;
        }
        else{
            dst[i] = rng[i].X;
        }
    }
    vector<pll> points(n+1);
    for(int i=1; i<=n; i++){
        points[i] = cross(points[i-1], v[i-1], p, dst[i]);
    }

    cout << "YES\n";
    for(auto [x,y]:points) cout << x << " " << y << "\n";

    return 0;
}