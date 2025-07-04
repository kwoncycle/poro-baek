#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<double,double> pdd;

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
pdd operator * (pdd l, double r){return {l.X*r, l.Y*r};}

const double eps = 0.000000001;

pdd mid(pdd l, pdd r){
    return (l+r) * 0.5;
}

pdd rot90(pdd l){
    return {l.Y, -l.X};
}

pdd intersect(pdd a, pdd b, pdd u, pdd v){
    b = b-a; v = v-u;
    return u + v*(((a-u)/b) / (v/b));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        pdd A, B, C;
        cin >> A.X >> A.Y >> B.X >> B.Y >> C.X >> C.Y;
        pdd PA = intersect(mid(A,C), mid(A,C) + rot90(A-C), A, A + rot90(A-B));
        pdd PB = intersect(mid(B,A), mid(B,A) + rot90(B-A), B, B + rot90(B-C));
        pdd PC = intersect(mid(C,B), mid(C,B) + rot90(C-B), C, C + rot90(C-A));

        if(abs((A-C)*(A-B)) < eps) PA = mid(A, C);
        if(abs((B-A)*(B-C)) < eps) PB = mid(B, A);
        if(abs((C-B)*(C-A)) < eps) PC = mid(C, B);

        //cout << PA.X << " " << PA.Y << " " << PB.X << " " << PB.Y << " " << PC.X << " " << PC.Y << "\n";

        pdd ans = intersect(A, A + rot90(PB-PA), B, B + rot90(PB-PC));
        cout << fixed << setprecision(5) << ans.X << " " << ans.Y << "\n";
    }
    return 0;
}