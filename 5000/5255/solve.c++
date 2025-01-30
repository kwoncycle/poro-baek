#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define ld long double
#define pdd pair<ld, ld>

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

// LINE: l.s + kl.t

const ld EPS = 1e-9;
const pdd O = {0.0,0.0};

pdd operator + (pdd l, pdd r){return {l.X+r.X, l.Y+r.Y};};
pdd operator - (pdd l, pdd r){return {l.X-r.X, l.Y-r.Y};};
pdd operator * (pdd l, ld k){ return {l.X*k, l.Y*k}; };
ld operator * (pdd l, pdd r){return l.X*r.X + l.Y*r.Y;};
ld operator / (pdd l, pdd r){return l.X*r.Y - l.Y*r.X;};

ld dst(pdd l, pdd r){
    return (r-l)*(r-l);
}

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
    int n;
    vector<LINE> ln;
    vector<pdd> CH;
    HPI(int _n, vector<LINE> &_ln): n(_n), ln(_ln){
        sort(ln.begin(), ln.end(), [&](LINE l, LINE r){
            return (l.t>l.s) == (r.t>r.s) ? (l.t-l.s)/(r.t-r.s) > 0 : (l.t-l.s) < (r.t-r.s);
        });
        deque<LINE> dq;
        for(auto &l:ln){
            while(dq.size()>= 2 and bad(*(dq.rbegin()+1), *dq.rbegin(), l)) dq.pop_back();
            while(dq.size()>= 2 and bad(*(dq.begin()+1), *dq.begin(), l)) dq.pop_front();
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

    ld find_mx(){
        ld mx = 0;
        int cn = CH.size();
        for(int i=0, j=0; i<cn; i++){
            mx = max(mx, dst(CH[i], CH[j]));
            while((j+1)%cn != i and (CH[(i+1)%cn]-CH[i])/(CH[(j+1)%cn]-CH[j]) >= 0){
                j = (j+1)%cn;
                mx = max(mx, dst(CH[i], CH[j]));
            }
        }
        return sqrtl(mx);
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pdd> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    ld st = 0, ed = 30000000;
    while(st + 0.000001 < ed){
        ld md = (st + ed) / 2.0;
        vector<LINE> vl(n);
        for(int i=0; i<n; i++){
            vl[i].s = v[i], vl[i].t = v[(i+1)%n];
            pdd dir = vl[i].t - vl[i].s;
            dir = {-dir.Y, dir.X};
            ld sz = sqrt(dir*dir);
            dir = dir * (md/sz);
            vl[i].s = vl[i].s + dir;
            vl[i].t = vl[i].t + dir;
        }
        HPI H(n, vl);
        ld mx = 0;
        if(H.CH.size() >= 3){
            mx = H.find_mx();
        }
        if(mx >= 2*md) st = md;
        else ed = md;
    }
    cout << fixed << setprecision(3) << st << "\n";
    return 0;
}