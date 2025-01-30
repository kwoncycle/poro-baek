#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pdd pair<int,int>
#define pll pair<ll,ll>
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
double operator / (pdd l, pdd r){return l.X*r.Y - l.Y*r.X;};

double dst(pdd a, pdd b){
    return sqrt((a-b)*(a-b));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<vector<double>> v(n, vector<double>(5));
    for(int i=0; i<n; i++){
        for(int j=0; j<5; j++) cin >> v[i][j];
    }

    vector<int> able(1<<n); able[0] = 1;
    for(int i=1; i<(1<<n); i++){
        for(int j=0, j1=1; j<n; j++, j1<<=1){
            if(i&j1){
                int id = i^j1;
                if(able[id] == 0) continue;
                int truth = 1;
                for(int k=0, k1=1; k<n; k++, k1<<=1){
                    if(k == j) continue;
                    int istarget = 0;
                    if(id&k1) istarget = 1;
                    pdd p;
                    if(!istarget){
                        p = {v[k][1], v[k][2]};
                    }
                    else p = {v[k][3], v[k][4]};

                    pdd p1 = {v[j][1], v[j][2]}, p2 = {v[j][3], v[j][4]};
                    double mn = min(dst(p1, p), dst(p2, p));
                    if((p-p1)*(p2-p1)>0 and (p-p2)*(p1-p2)>0){
                        mn = min(mn, abs((p-p1)/(p-p2))/dst(p1, p2));
                    }
                    if(mn < v[j][0] + v[k][0]){
                        truth = 0; break;
                    }
                }

                if(truth) able[i] = 1;
            }
        }
    }
    int ans = 0;
    for(int i=0; i<(1<<n); i++){
        int i1 = i, cnt = 0;
        if(able[i]){
            while(i1){
                cnt += i1&1; i1 >>= 1;
            }
        }
        ans = max(ans, cnt);
    }
    cout << ans << "\n";
    return 0;
}