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
#define ld long double
#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

ll dst(pii l, pii r){
    return (ll)(l.X - r.X)*(l.X - r.X) + (ll)(l.Y - r.Y)*(l.Y - r.Y);
}

struct Convex_hull{
    int n;
    vector<pii> v;
    vector<pii> ch;
    int mx = 0;
    bool option = 0;
    Convex_hull(int _n, vector<pii> &_v, bool opt): n(_n), v(_v){
        if(opt) option = 1;
        make_CH();
        rotate(ch.begin(), min_element(ch.begin(), ch.end()), ch.end());
        mx = max_element(ch.begin(), ch.end()) - ch.begin();
        n = ch.size();
    }
    void make_CH(){
        pii p = *min_element(v.begin(), v.end(), [&](pii l, pii r){
            return l.Y == r.Y ? l.X < r.X : l.Y < r.Y;
        });
        sort(v.begin(), v.end(), [&](pii l, pii r){
            return (l-p)/(r-p) == 0 ? (l-p)*(l-p) < (r-p)*(r-p) : (l-p)/(r-p) > 0;
        });
        if(option){
            int id = n-1;
            while(id >= 0 and (v[id] - v[0])/(v[n-1] - v[0]) == 0) id--; id++;
            if(id == 0) return;
            reverse(v.begin() + id, v.end());
        }
        for(int i=0; i<(int)v.size(); i++){
            if(option) while((int)ch.size() >= 2 and (ch.back() - ch[ch.size()-2]) / (v[i] - ch.back()) < 0) ch.pop_back();
            else while((int)ch.size() >= 2 and (ch.back() - ch[ch.size()-2]) / (v[i] - ch.back()) <= 0) ch.pop_back();
            ch.push_back(v[i]);
        }
    }

    int isin(pii p){ // 2 strictly in 1 boundart 0 out
        if(p < ch[0] or ch[mx] < p) return 0;
        int l = lower_bound(ch.begin(), ch.begin()+mx, p) - ch.begin();
        int r = lower_bound(ch.begin()+mx, ch.end(), p, [&](pii i, pii j){ return i > j; }) - ch.begin();
        ll bl = (ch[(l-1)%n] - p)/(ch[l%n] - p), br = (ch[(r-1)%n] - p)/(ch[r%n] - p);
        if(bl > 0 and br > 0) return 2;
        if(bl < 0 or br < 0) return 0;
        return 1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        pii cur; cin >> cur.X >> cur.Y;
        pii out; cin >> out.X >> out.Y;

        int n; cin >> n;
        vector<pii> v(n);
        for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;

        Convex_hull CH_v(n, v, 0);
        if(CH_v.isin(cur) == 2 or CH_v.isin(out) == 2){
            cout << "IMPOSSIBLE\n"; continue;
        }

        v.push_back(cur); v.push_back(out);
        Convex_hull CH_all(n+2, v, 1);
        n = CH_all.ch.size();
        int i_cur = 0, i_out = 0;
        while(i_cur < n and CH_all.ch[i_cur] != cur) i_cur++;
        while(i_out < n and CH_all.ch[i_out] != out) i_out++;
        
        if(i_cur == n or i_out == n){
            ll d = dst(cur, out);
            ld ans = sqrtl((ld)d);
            cout << fixed << setprecision(3) << ans << "\n";
            continue;
        }

        long double v1 = 0;
        for(int i=i_cur; i != i_out; i = (i+1)%(n)){
            ll d = dst(CH_all.ch[i], CH_all.ch[(i+1)%n]);
            v1 += sqrtl((ld)d);
        }
        long double v2 = 0;
        for(int i=i_cur; i != i_out; i = (i+n-1)%(n)){
            ll d = dst(CH_all.ch[i], CH_all.ch[(i+n-1)%n]);
            v2 += sqrtl((ld)d);
        }
        cout << fixed << setprecision(3) << min(v1, v2) << "\n";
    }
    return 0;
}