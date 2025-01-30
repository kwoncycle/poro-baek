#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return l.X*r.X + l.Y*r.Y;};
ll operator / (pii l, pii r){return l.X*r.Y - l.Y*r.X;};

vector<pii> CH;
ll o;
void convex_hull(vector<pii> &v){
    pii p1 = *min_element(v.begin(), v.end(), [&](pii l, pii r){ return l.Y == r.Y ? l.X < r.X : l.Y < r.Y; });
    sort(v.begin(), v.end(), [&](pii l, pii r){ 
        o = (l-p1)/(r-p1);
        return o == 0 ? (l-p1)*(l-p1)<(r-p1)*(r-p1) : o > 0;
    });

    for(auto &p:v){
        while(CH.size() >= 2 and (CH.back() - CH[CH.size()-2])/(p - CH.back()) <= 0) CH.pop_back();
        CH.push_back(p);
    }
}

ll dst(pii &l, pii &r){
    return (ll)(l.X-r.X)*(l.X-r.X) + (ll)(l.Y-r.Y)*(l.Y-r.Y);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        vector<pii> v(n);
        for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
        CH.clear();
        convex_hull(v);

        n = CH.size();
        if(n == 2){
            int m0 = 0, m1 = 1;
            cout << CH[m0].X << " " << CH[m0].Y << " " << CH[m1].X << " " << CH[m1].Y << "\n";
            continue;
        }
        int m0 = 0, m1 = 0;
        ll mxdst = 0;
        for(int i=0, j=0; i<n; i++){
            ll d = dst(CH[i], CH[j]);
            if(mxdst < d) m0 = i, m1 = j, mxdst = d;
            while((CH[(i+1)%n] - CH[i])/(CH[(j+1)%n] - CH[j]) >= 0){
                j = (j+1); if(j >= n) j -= n;
                ll d = dst(CH[i], CH[j]);
                if(mxdst < d) m0 = i, m1 = j, mxdst = d;
            }
        }

        cout << CH[m0].X << " " << CH[m0].Y << " " << CH[m1].X << " " << CH[m1].Y << "\n";

    }
    return 0;
}