#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pdd pair<double,double>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pdd, 2>
// LINE: l[0] + kl[1]

pdd operator + (pdd l, pdd r){return {l.X+r.X, l.Y+r.Y};};
pdd operator - (pdd l, pdd r){return {l.X-r.X, l.Y-r.Y};};
double operator * (pdd l, pdd r){return l.X*r.X + l.Y*r.Y;};
double operator / (pdd l, pdd r){return l.X*r.Y - l.Y*r.X;};
pdd operator * (pdd l, double r){return {l.X*r, l.Y*r};};

vector<pdd> v;
const double EPS = 1e-9;

bool allin(pdd p, double r){
    bool truth = 1;
    for(pdd p1:v){
        if((p1-p)*(p1-p) < r*r + EPS) continue;
        truth = 0; break;
    }
    return truth;
}

pdd rotate(pdd p){
    return {-p.Y, p.X};
}

pdd cross(LINE l1, LINE l2){
    double a = ((l2[0]-l1[0])/l2[1]) / (l1[1]/l2[1]);
    return l1[0] + l1[1] * a;
}

double dst(pdd p1, pdd p2){
    return sqrt((p1-p2)*(p1-p2));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    v.resize(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    double mx = 0x3f3f3f3f3fll;
    for(int i1=0; i1<n; i1++){
        for(int i2=i1+1; i2<n; i2++){
            for(int i3=i2+1; i3<n; i3++){
                LINE l1 = {(v[i1]+v[i2])*0.5, rotate(v[i1]-v[i2])};
                LINE l2 = {(v[i3]+v[i2])*0.5, rotate(v[i2]-v[i3])};
                if(abs(l1[1]/l2[1]) < EPS) continue;
                pdd c = cross(l1, l2);
                if(allin(c, dst(c, v[i1]))){
                    mx = min(mx, dst(c, v[i1]));
                }
            }
        }
    }

    for(int i1=0; i1<n; i1++){
        for(int i2=i1+1; i2<n; i2++){
            pdd c = (v[i1] + v[i2]) * 0.5;
            if(allin(c, dst(c, v[i1]))){
                mx = min(mx, dst(c, v[i1]));
            }
        }
    }

    int o = (int)(mx*200.0);
    if((int)(mx*2000.0) % 10 >= 5) o++;
    printf("%.2lf\n", mx+mx);
    //cout << o/100 << "." << o%100 << "\n";

    //cout << fixed << setprecision(2) << mx+mx << "\n";
    return 0;
}