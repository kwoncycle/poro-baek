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
#define CRC pair<pii, int>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};


bool LL_intersect(LINE l1, LINE l2){
    if((l1[1]-l1[0])/(l2[1]-l2[0]) == 0){
        if((l2[0]-l1[0])/(l2[1]-l1[0]) or (l1[0]-l2[0])/(l1[1]-l2[0])) return false;
        if(max(l1[0],l1[1]) < min(l2[0],l2[1]) or max(l2[0],l2[1]) < min(l1[0],l1[1])) return false;
        return true;
    }
    else{
        l1[1] = l1[1] - l1[0]; l2[1] = l2[1] - l2[0];
        ll k1 = (l2[0]-l1[0])/l2[1], k2 = l1[1]/l2[1];
        ll t1 = (l1[0]-l2[0])/l1[1], t2 = l2[1]/l1[1];
        if(k2 < 0) k1 *= -1, k2 *= -1;
        else t1 *= -1, t2 *= -1;
        return (0<=k1) and (k1<=k2) and (0<=t1) and (t1<=t2);
    }
}

int LR_intersect(LINE l, CRC c){
    l[1] = l[1] - l[0];
    ll A = l[1]*l[1], B = (l[1]*(l[0]-c.X)), C = ((l[0]-c.X)*(l[0]-c.X)) - c.Y*c.Y;
    if(B*B-A*C < 0) return 0;
    if(B*B-A*C == 0){
        if(0 <= -B and -B <= A) return 1;
        else return 0;
    }
    int cnt = 0;
    __int128 lv = (__int128)B*abs(B), rv = (__int128)(A+B)*abs(A+B);
    __int128 t = (__int128)B*B-(__int128)A*C;
    if(lv <= t and t <= rv) cnt++;
    if(lv <= -t and -t <= rv) cnt++;
    return cnt;
}

int RR_intersect(CRC c1, CRC c2){
    ll dst = (c1.X - c2.X)*(c1.X - c2.X);
    ll r1 = c1.Y, r2 = c2.Y;
    ll A = -2*r1*r2, B = r1*r1+r2*r2-dst, C = 2*r1*r2;
    if(A<B and B<C) return 2;
    if(A==B or B==C) return 1;
    return 0;
}

 
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<vector<pii>> poly;
    vector<CRC> circle;
    vector<vector<int>> graph(n+1);
    for(int i=0; i<n; i++){
        int a; cin >> a;
        if(a == 1){
            pii c; int r;
            cin >> c.X >> c.Y >> r;
            circle.push_back({c, r});
        }
        else{
            vector<pii> v;
            while(a--){
                int x,y; cin >> x >> y;
                v.push_back({x, y});
            }
            poly.push_back(v);
        }
    }

    vector<pii> connect;
    ll ans = 1;
    for(int i=0; i<(int)poly.size(); i++){
        for(int j=0; j<i; j++){
            int cnt = 0;
            int ni = poly[i].size(), nj = poly[j].size();
            for(int i1=0; i1<ni; i1++){
                for(int j1=0; j1<nj; j1++){
                    if(LL_intersect({poly[i][i1], poly[i][(i1+1)%ni]}, {poly[j][j1], poly[j][(j1+1)%nj]})) cnt++;
                }
            }
            if(cnt){
                connect.push_back({i, j});
            }
            ans += cnt;
            //cout << cnt << " " << i << "p" << j << "p\n"; 
        }
    }

    for(int i=0; i<(int)circle.size(); i++){
        for(int j=0; j<(int)poly.size(); j++){
            int nj = poly[j].size();
            int cnt = 0;
            for(int j1=0; j1<nj; j1++){
                cnt += LR_intersect({poly[j][j1], poly[j][(j1+1)%nj]}, circle[i]);
            }
            if(cnt) connect.push_back({j, i+(int)poly.size()});
            ans += cnt;
            //cout << cnt << " " << i << "c" << j << "p\n"; 
        }
        for(int j=0; j<i; j++){
            int cnt = RR_intersect(circle[j], circle[i]);
            if(cnt) connect.push_back({j+(int)poly.size(), i+(int)poly.size()});
            ans += cnt;
            //cout << cnt << " " << i << "c" << j << "c\n"; 
        }
    }
    djs DJS(n+1);
    for(auto [x,y]:connect){
        DJS.Union(x, y);
    }
    for(int i=0; i<n; i++){
        if(DJS.find(i) == i) ans++;
    }
    cout << ans << "\n";

    return 0;
}