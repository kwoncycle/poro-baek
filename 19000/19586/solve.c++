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

using ld = long double;

struct Convex_hull{
    int n;
    vector<pii> v, ch;
    ld ans = 0x3f3f3f3f3f3f;
    Convex_hull(int _n, vector<pii> &_v): n(_n), v(_v){
        make_CH();
        if(n == 2){
            pii u = ch[0] - ch[1];
            ans = 2*sqrtl((ld)(u*u));
        }
        else rotate_Calliph();
        cout << fixed << setprecision(12) << ans << '\n';
    }
    
    void make_CH(){
        pii p = *min_element(v.begin(), v.end(), [&](pii l, pii r){
            return l.Y == r.Y ? l.X < r.X : l.Y < r.Y;
        });
        sort(v.begin(), v.end(), [&](pii l, pii r){
            return (l-p)/(r-p) == 0 ? (l-p)*(l-p) < (r-p)*(r-p) : (l-p)/(r-p) > 0;
        });
        for(auto vi:v){
            while((int)ch.size() >= 2 and (ch.back() - ch[ch.size()-2]) / (vi - ch.back()) <= 0) ch.pop_back();
            ch.push_back(vi);
        }
        v.clear();
        n = ch.size();
    }

    void rotate_Calliph(){
        for(int i=0, j1 = 0, j2 = 0, j3 = 0; i<n; i++){
            pii u1 = ch[(i+1)%n] - ch[i];
            pii u2 = {-u1.Y, u1.X};
            while((j1+1)%n != i and u1/(ch[(j1+1)%n] - ch[j1]) >= 0){
                j1 = (j1+1)%n;
            }
            while((j2) != j1 and u2/(ch[(j2+1)%n] - ch[j2]) <= 0){
                j2 = (j2+1)%n;
            }
            if(i == 0) j3 = j1;
            while((j3) != i and u2/(ch[(j3+1)%n] - ch[j3]) >= 0){
                j3 = (j3+1)%n;
            }
            ll A1 = (ch[j1] - ch[i])*u2, A2 = (ch[j2] - ch[j3])*u1, A3 = u1*u1;
            ld l1 = (ld)A1/sqrtl((ld)A3), l2 = (ld)A2/sqrtl((ld)A3);
            ans = min(ans, l1+l1+l2+l2);
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    Convex_hull solve(n, v);
    return 0;
}