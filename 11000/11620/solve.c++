#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define ld long double
#define pdd pair<ld, ld>

const ld EPS = 1e-8;

pdd operator + (pdd l, pdd r){return {l.X+r.X, l.Y+r.Y};};
pdd operator - (pdd l, pdd r){return {l.X-r.X, l.Y-r.Y};};
pdd operator * (pdd l, ld k){ return {l.X*k, l.Y*k}; };
ld operator * (pdd l, pdd r){return l.X*r.X + l.Y*r.Y;};
ld operator / (pdd l, pdd r){return l.X*r.Y - l.Y*r.X;};

inline bool equal(ld a, ld b){
    return abs(a-b) < EPS;
}
struct LINE{
    pdd s, t;
    LINE(){};
    LINE(pdd _s, pdd _t):s(_s), t(_t){};
    bool intersect(LINE &r, pdd &out){ // 직선
        if(equal(0, (t-s)/(r.t-r.s))) return 0;
        ld k = ((r.s-s)/(r.t-r.s)) / ((t-s)/(r.t-r.s));
        out = s + (t - s)*k;
        return 1;
    }
};
struct HPI{
    vector<LINE> ln1, ln;
    vector<pdd> CH;
    pdd tmp;
    HPI(vector<LINE> &_ln): ln1(_ln){
        sort(ln1.begin(), ln1.end(), [&](LINE l, LINE r){
            return (l.t>l.s) == (r.t>r.s) ? ((l.t-l.s)/(r.t-r.s) > 0) : (l.t-l.s) < (r.t-r.s);
        });
        for(auto &l:ln1){
            if(ln.empty()) ln.push_back(l);
            else{
                if(!ln.back().intersect(l, tmp) and (ln.back().t - ln.back().s)*(l.t - l.s) > 0){
                    if((ln.back().t - ln.back().s)/(l.t - ln.back().s) >= -EPS){
                        ln.pop_back(); ln.push_back(l);
                    }
                }
                else ln.push_back(l);
            }
        }
        deque<LINE> dq; 
        for(auto &l:ln){
            while(dq.size()>=2 and bad(*(dq.rbegin()+1), *dq.rbegin(), l)) dq.pop_back();
            while(dq.size()>=2 and bad(*(dq.begin()+1), *dq.begin(), l)) dq.pop_front();
            if(dq.size() < 2 or !bad(*dq.rbegin(), l, *dq.begin())) dq.push_back(l); 
        }
        if(dq.size() >= 3){
            dq.push_back(dq[0]);
            for(int i=0; i<(int)dq.size()-1; i++){
                pdd v;
                if(!dq[i].intersect(dq[i+1], v)) continue;
                CH.push_back(v);
            }
        }
    }
    bool bad(LINE &a, LINE &b, LINE &c){
        pdd v;
        if(!a.intersect(b, v)) return 0;
        ld o = (c.t-c.s)/(v-c.s);
        return o < 0 or equal(o, 0.0);
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    pdd p[4];
    for(int i=0; i<4; i++) cin >> p[i].X >> p[i].Y;
    pdd dice[4];
    dice[0] = {0.5, -0.5};
    dice[1] = {-0.5, -0.5};
    dice[2] = {-0.5, 0.5};
    dice[3] = {0.5, 0.5};

    ld ttl = 125 - 1;
    ld ans = 0;
    ans += 5*5*4*5;
    ld vals[4] = {1, 4, 6, 3};
    // 1
    for(int id=0; id<4; id++){
        vector<LINE> v;
        for(int i=0; i<4; i++) v.push_back({p[i], p[(i+1)%4]});
        v.push_back({dice[id], dice[(id+1)%4]});
        HPI hpi(v);
        ld area = 0;
        int t = hpi.CH.size();
        for(int i=0; i<(int)t; i++){
            area += (hpi.CH[(i+1)%t]/hpi.CH[i]);
        }
        area *= -0.5;
        ans += area * 5 * vals[id];
    }

    cout << fixed << setprecision(15) << ans/ttl << "\n";

    return 0;
}