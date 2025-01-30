#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<double,double>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pdd, 2>
// LINE: l[0] + kl[1]

pdd operator + (pdd l, pdd r){return {l.X+r.X, l.Y+r.Y};};
pdd operator - (pdd l, pdd r){return {l.X-r.X, l.Y-r.Y};};
double operator * (pdd l, pdd r){return l.X*r.X + l.Y*r.Y;};
pdd operator * (pdd l, double t){return {l.X*t, l.Y*t};};
double operator / (pdd l, pdd r){return l.X*r.Y - l.Y*r.X;};

double EPS = 1e-10;

double dst(pdd l, pdd r){
    return sqrt((l.X-r.X)*(l.X-r.X) + (l.Y-r.Y)*(l.Y-r.Y));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        int n, k;
        double d;
        cin >> n >> k >> d;
        if(n == 0 and k == 0) return 0;
        vector<pdd> v1(n), v2(k), v;
        for(int i=0; i<n; i++) {
            cin >> v1[i].X >> v1[i].Y;
            v.push_back(v1[i]);
        }
        for(int i=0; i<k; i++) {
            cin >> v2[i].X >> v2[i].Y;
            v.push_back(v2[i]);
        }
        vector<pdd> directions;
        for(int i=0; i<n+k; i++){
            for(int j=i+1; j<n+k; j++){
                directions.push_back({v[i].Y - v[j].Y, -(v[i].X - v[j].X)});
                double d_ij = dst(v[i], v[j]);
                if(d - EPS <= d_ij and d_ij <= d + EPS){
                    directions.push_back(v[i] - v[j]);
                }
                else if(d + EPS < d_ij){
                    double l = d_ij;
                    pdd c = v[j]*(l - d*d/l) + v[i]*(d*d/l);
                    pdd d1 = {v[i].Y - v[j].Y, -(v[i].X - v[j].X)}, d2 = {-d1.X, -d1.Y};
                    pdd c1 = c + d1*(d*sqrt(l*l-d*d)/(l*l)), c2 = c + d2*(d*sqrt(l*l-d*d)/(l*l));
                    directions.push_back(c1 - v[j]);
                    directions.push_back(c2 - v[j]);
                }
            }
        }

        int mn = 30000;
        for(auto &dir:directions){
            dir = dir * (1/dst(dir, {0,0}));
            vector<pair<double, int>> dv;
            for(int i=0; i<n; i++){
                dv.push_back({v[i]*dir, 0});
            }
            for(int i=n; i<n+k; i++){
                dv.push_back({v[i]*dir, 1});
            }
            sort(dv.begin(), dv.end());
            vector<int> cnt1(n+k), cnt2(n+k), cnt3(n+k), cnt4(n+k);
            cnt1[0] = dv[0].Y;
            cnt3[0] = 1 - dv[0].Y;
            for(int i=1; i<n+k; i++){
                cnt1[i] = cnt1[i-1] + dv[i].Y;
                cnt3[i] = cnt3[i-1] + (1 - dv[i].Y);
            }

            for(int i=0, i1=0; i<n+k; i++){
                while(i1+1 < n+k and dv[i1+1].X < dv[i].X + d - EPS) i1++;
                cnt2[i] = cnt1[i1];
                cnt4[i] = cnt3[i1];
            }

            //for(int i=0; i<n+k; i++) cout << cnt1[i] << " " << cnt2[i] << " " << cnt3[i] << " " << cnt4[i] << "\n";

            for(int i=0; i<n+k; i++){
                mn = min(cnt2[i] + (n - cnt3[i]), mn);
                mn = min(cnt4[i] + (k - cnt1[i]), mn);
            }
        }

        cout << mn << "\n";
    }
    return 0;
}