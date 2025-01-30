#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
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
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

vector<pii> convex_hull(vector<pii> &v){
    pii p1 = *min_element(v.begin(), v.end(), [&](pii l, pii r){ return l.Y == r.Y ? l.X < r.X : l.Y < r.Y;});
    sort(v.begin(), v.end(), [&](pii l, pii r){
        ll o = (l-p1)/(r-p1);
        return o == 0 ? (l-p1)*(l-p1) < (r-p1)*(r-p1) : o > 0;
    });
    vector<pii> st;
    for(auto &p:v){
        while(st.size() >= 2 and (st.back() - st[st.size()-2])/(p - st.back()) <= 0) st.pop_back();
        st.push_back(p);
    }
    return st;
}

pll get_d2(pii &p1, pii &p2, pii &p3){
    ll a = abs((p1/p2) + (p2/p3) + (p3/p1));
    ll l = (p2-p1)*(p2-p1);
    return {a*a, l};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for(int tc=1; ; tc++){
        int n; cin >> n;
        if(!n) break;
        vector<pii> v(n);
        for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;

        vector<pii> CH = convex_hull(v);
        n = CH.size();

        pll ans = {1, 0};

        for(int i=0, j=0; i<n; i++){
            while((CH[(i+1)%n]-CH[i])/(CH[(j+1)%n]-CH[j]) >= 0){
                j = j + 1; if(j >= n) j -= n;
            }
            pll d2 = get_d2(CH[i], CH[(i+1)%n], CH[j]);
            if(ans.X*d2.Y > ans.Y*d2.X) ans = d2;
        }

        double ansd = (double)ans.X / (double)ans.Y;
        ansd = sqrt(ansd);
        ansd += 0.00499999;
        cout << fixed << setprecision(2) << "Case " << tc << ": " << ansd << "\n";
    }

    return 0;
}