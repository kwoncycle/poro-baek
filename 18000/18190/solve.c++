#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define pff pair<frac,frac>
#define pdd pair<ld, ld>
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n
#define ld long double
#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

pdd operator + (pdd l, pdd r){ return {l.X + r.X, l.Y + r.Y};};
pdd operator - (pdd l, pdd r){ return {l.X - r.X, l.Y - r.Y};};
ld operator / (pdd l, pdd r){ return l.X*r.Y - l.Y*r.X; };

pdd pll2pdd(pll o){
    return pdd(o.X, o.Y);
}

pdd cross_point(LINE l1, LINE l2){
    l1[1] = l1[1] - l1[0];
    l2[1] = l2[1] - l2[0];
    __int128 k1 = (l2[0]-l1[0])/l2[1], k2 = (l1[1]/l2[1]);
    if(k2 < 0) k1 *= -1, k2 *= -1;
    __int128 o = __gcd(k1, k2); k1 /= o, k2 /= o;
    assert(0 <= k1 and k1 <= k2);
    ll o1 = (ll)(l1[0].X*k2 + l1[1].X*k1), o2 = (ll)(l1[0].Y*k2 + l1[1].Y*k1), o3 = (ll)k2, o4 = k2;
    o = __gcd(o1, o3); o1/=o; o3/=o;
    o = __gcd(o2, o4); o2/=o; o4/=o;
    return pdd((ld)o1/(ld)o3, (ld)o2/(ld)o4);
}


bool cross(LINE l1, LINE l2){
    if(l1[1]/l2[1]){
        ll k1 = (l2[0]-l1[0])/l2[1], k2 = (l1[1]/l2[1]);
        ll t1 = (l1[0]-l2[0])/l1[1], t2 = (l2[1]/l1[1]);
        if(k2 < 0) k1 *= -1, k2 = t2;
        else t1 *= -1, t2 = k2;
        return (0<=k1 and k1<=k2 and 0<=t1 and t1<=t2);
    }
    else{
        if((l2[0]-l1[0])/l1[1] or (l2[0]-l1[0])/l2[1]) return false;
        return !(max(l1[0], l1[0]+l1[1]) < min(l2[0], l2[0]+l2[1]) or max(l2[0], l2[0]+l2[1]) < min(l1[0], l1[0]+l1[1]));
    }
}

struct polygon{
    int n;
    vector<pii> P;
    int mx;
    vector<ll> sum_pre;
    polygon(int n): n(n){
        P.resize(n);
        sum_pre.resize(2*n+1);
        for(int i=0; i<n; i++) cin >> P[i].X >> P[i].Y;
        rotate(P.begin(), min_element(P.begin(), P.end()), P.end());
        mx = max_element(P.begin(), P.end()) - P.begin();
        
        for(int i=1; i<=2*n; i++){
            sum_pre[i] = sum_pre[i-1] + P[(i-1)%n]/P[i%n];
        }
    }

    int isin(pii p){ // 0 out 1 in 2 boundary
        if(p < P[0] or P[mx] < p) return 0;
        if(p == P[0]) return 2;
        int l = lower_bound(P.begin(), P.begin() + mx, p) - P.begin();
        int r = lower_bound(P.begin() + mx, P.end(), p, [&](pii i, pii j){
            return i > j;
        }) - P.begin();

        ll l1 = (p - P[l-1])/(p - P[l%n]); // > 0 : in
        ll l2 = (p - P[r-1])/(p - P[r%n]); // same
        if(l1 > 0 and l2 > 0) return 1;
        if(l1 < 0 or l2 < 0) return 0;
        return 2;
    }

    pii lr(pii p){
        ll i1 = 0;
        pii ans;
        if((P[i1]-p)/(P[(i1+1)%n]-P[i1]) == 0) i1 = (i1+1) % n;
        if((P[i1]-p)/(P[(i1+1)%n]-P[i1]) > 0){
            for(ll T = (1<<16); T >= 1; T >>= 1){
                if(T >= n) continue;
                ll id = (i1 + T) % n;
                if((P[id]-p) / (P[(id+1)%n]-P[id]) > 0){
                    if((P[i1] - p) / (P[id] - p) > 0) i1 = id;
                }
            }
            i1 = (i1 + 1) % n;
            ans.X = i1;
            if((P[i1]-p)/(P[(i1+1)%n]-P[i1]) == 0) i1 = (i1+1) % n;
            for(ll T = (1<<16); T >= 1; T >>= 1){
                if(T >= n) continue;
                ll id = (i1 + T) % n;
                if((P[id]-p) / (P[(id+1)%n]-P[id]) < 0){
                    if((P[i1] - p) / (P[id] - p) < 0) i1 = id;
                }
            }
            i1 = (i1 + 1) % n;
            ans.Y = i1;
            return ans;
        }
        else{
            for(ll T = (1<<16); T >= 1; T >>= 1){
                if(T >= n) continue;
                ll id = (i1 + T) % n;
                if((P[id]-p) / (P[(id+1)%n]-P[id]) < 0){
                    if((P[i1] - p) / (P[id] - p) < 0) i1 = id;
                }
            }
            i1 = (i1 + 1) % n;
            ans.Y = i1;
            if((P[i1]-p)/(P[(i1+1)%n]-P[i1]) == 0) i1 = (i1+1) % n;
            for(ll T = (1<<16); T >= 1; T >>= 1){
                if(T >= n) continue;
                ll id = (i1 + T) % n;
                if((P[id]-p) / (P[(id+1)%n]-P[id]) > 0){
                    if((P[i1] - p) / (P[id] - p) > 0) i1 = id;
                }
            }
            i1 = (i1 + 1) % n;
            ans.X = i1;
            return ans;
        }
    }

    ll crossA(pii p, pii u){
        ll i1 = 0;
        for(ll T = (1<<16); T >= 1; T >>= 1){
            if((u-p)/(P[i1]-p)==0) {
                if((u-p)*(P[i1]-p)>0) return i1;
                else i1 = (i1 + 1) % n;
            }
            ll id = (i1 + T) % n;
            if((u-p) / (P[id]-p) > 0){
                if((u-p) / (P[i1]-p) > 0){
                    if((P[i1]-p)/(P[id]-p) > 0) i1 = id;
                }
                else{
                    continue;
                }
            }
            else{
                if((u-p) / (P[i1]-p) > 0){
                    i1 = id;
                }
                else{
                    if((P[i1]-p)/(P[id]-p) > 0) i1 = id;
                }
            }
        }
        return i1;
    }

};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m, qq;
    cin >> n >> m >> qq;
    polygon A(n), B(m);

    while(qq--){
        pii p; cin >> p.X >> p.Y;
        int a = A.isin(p), b = B.isin(p);
        if(a == 0 or a == 2) {
            cout << "OUT\n"; continue;
        }
        if(b >= 1){
            cout << "IN\n"; continue;
        }
        auto [li, ri] = B.lr(p);
        ll la = A.crossA(p, B.P[li]), ra = A.crossA(p, B.P[ri]);
        pdd pl = cross_point({A.P[la], A.P[(la+1)%n]}, {p, B.P[li]}), pr = cross_point({A.P[ra], A.P[(ra+1)%n]}, {p, B.P[ri]});
        pdd p1 = pll2pdd({p.X, p.Y});
        pii plb = B.P[li];
        pii prb = B.P[ri];

        ll area_minus = p/prb + plb/p;
        if(true){
            int l1 = li, r1 = ri;
            if(l1 > r1) r1 += m;
            area_minus -= B.sum_pre[r1] - B.sum_pre[l1];
        }

        if(la == ra){
            ld area = ((((p1/pr) + pr/pl) + pl/p1) - (B.sum_pre[m] + area_minus))/2;
            cout << fixed << setprecision(10) << area << "\n";
        }
        else{
            int l1 = la, r1 = ra;
            if(l1 < r1+1) l1 += n;
            ll areall = A.sum_pre[l1] - A.sum_pre[r1+1];
            pdd pl1 = pll2pdd(A.P[la]), pr1 = pll2pdd(A.P[(ra+1)%n]);
            areall += A.P[la]/p + p/A.P[(ra+1)%n];
            ld area1 = (pl1 - p1)/(pl - p1);
            ld area2 = (pr - p1)/(pr1 - p1);
            ld area = (area1 + area2 + (ld)(areall - (B.sum_pre[m] + area_minus)))/(ld)2;
            cout << fixed << setprecision(10) << area << "\n";
        }
    }

    return 0;
}