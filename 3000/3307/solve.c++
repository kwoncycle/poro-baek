#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<double,double>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
double operator * (pii l, pii r){return l.X*r.X + l.Y*r.Y;};
double operator / (pii l, pii r){return l.X*r.Y - l.Y*r.X;};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(auto &[i,j]:v) cin >> i >> j;

    vector<double> ans(n);
    vector<pii> S;
    for(int i=0; i<n; i++){
        if(S.empty()){
            S.push_back({v[i].X, v[i].Y});
            ans[i] = v[i].Y;
        }
        else{
            double r1 = v[i].Y;
            while(!S.empty()){
                auto [x, r] = S.back();
                r1 = min(r1, (v[i].X - x) * (v[i].X - x) / (4.0*r));
                if(r1 >= r){
                    S.pop_back();
                    if(S.empty()){
                        S.push_back({v[i].X, r1});
                        ans[i] = r1;
                        break;
                    }
                }
                else{
                    S.push_back({v[i].X, r1});
                    ans[i] = r1;
                    break;
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        cout << fixed << setprecision(12) << ans[i] << "\n";
    }
    return 0;
}