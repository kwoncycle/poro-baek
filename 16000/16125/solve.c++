#include <bits/stdc++.h>
using namespace std;

#define ld long double
#define pdd pair<ld,ld>
#define X first
#define Y second

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pdd, 2>
// LINE: l[0] + kl[1]

pdd operator + (pdd l, pdd r){return {l.X+r.X, l.Y+r.Y};};
pdd operator - (pdd l, pdd r){return {l.X-r.X, l.Y-r.Y};};
ld operator * (pdd l, pdd r){return l.X*r.X + l.Y*r.Y;};
ld operator / (pdd l, pdd r){return l.X*r.Y - l.Y*r.X;};
pdd operator * (pdd l, ld r){return {l.X*r, l.Y*r};};

const pdd O = {0, 0};
const ld pi = acos(-1);
ld dst(pdd p, pdd q){
    return sqrt((q-p)*(q-p));
}


pdd midpoint(pdd l, pdd r){
    pdd o = l+r; o.X /= 2.0, o.Y /= 2.0;
    return o;
}

bool isin(pdd p, ld r){
    return dst(p, O) <= r;
}


ld Area(pdd p1, ld r1, pdd p2, ld r2){
    ld d = dst(p1, p2);
    if(d > r1+r2) return 0;
    if(d + r2 <= r1) return pi*r2*r2;
    if(d + r1 <= r2) return pi*r1*r1;
    ld t1 = acos((d * d + r1 * r1 - r2 * r2) / (d * r1 * 2.0)) * 2.0;
	ld t2 = acos((d * d + r2 * r2 - r1 * r1) / (d * r2 * 2.0)) * 2.0;
    return (t1 * r1 * r1 + t2 * r2 * r2 - r1 * r1 * sin(t1) - r2 * r2 * sin(t2)) * 0.5;
}


int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    double r;
    pdd p1, p2;
    cin >> r >> p1.X >> p1.Y >> p2.X >> p2.Y;
    pdd md = midpoint(p1, p2);
    pdd dir = p1-p2;
    dir = {dir.Y, -dir.X};
    ld A = dir*dir, B = 2.0*(md*dir), C = (md*md) - r*r;
    if(B*B-4*A*C < 0){
        cout << "0\n"; return 0;
    }
    //cout << A << " " << B << " " << C << "\n";
    ld x1 = (-B + sqrt(B*B-4*A*C))/(A+A), x2 = (-B - sqrt(B*B-4*A*C))/(A+A);
    //cout << x1 << " " << x2 << "\n";
    //cout << (dir*x1).X << " " << dir.Y <<"a \n";
    pdd P1 = md + (dir*x1), P2 = md + (dir*x2);

    if((P1-P2)*(p1-P2) >= 0 and (P2-P1)*(p2-P1) >= 0){
        ld ans = pi*dst(P2, p2)*dst(P2, p2) +  pi*dst(P1, p2)*dst(P1, p2) - 2.0*Area(P2, dst(P2, p2), P1, dst(P1, p2));
        cout << fixed << setprecision(12) << ans << "\n";
        return 0;
    }

    if(dst(p1,P1) > dst(p1, P2)) swap(P1, P2);
    //ld ans = pi * dst(P2, p1) * dst(P2, p1) - Area(P2, dst(P2, p2), P1, dst(P1, p2));
    ld ans = pi*dst(P2, p2)*dst(P2, p2) +  pi*dst(P1, p2)*dst(P1, p2) - 2.0*Area(P2, dst(P2, p2), P1, dst(P1, p2));
    cout << fixed << setprecision(12) << ans << "\n";
    //cout << P1.X << " " << P1.Y << "\n";
    //cout << P2.X << " " << P2.Y << "\n";

    return 0;
}