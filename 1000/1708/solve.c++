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
    pii p1 = *min_element(v.begin(), v.end(), [&](pii l, pii r){return l.Y == r.Y ? l.X < r.X : l.Y < r.Y;});
    sort(v.begin(), v.end(), [&](pll l, pll r){
        ll o = (l-p1)/(r-p1);
        return o == 0 ? (l-p1)*(l-p1) < (r-p1)*(r-p1) : o > 0;
    });
    // if you need 3 point lined
    auto idx = v.size()-1;
    while((v[idx-1]-p1)/(v.back()-p1) == 0) idx--;
    reverse(v.begin()+idx, v.end());

    vector<pii> st;
    for(int i=0; i<(int)v.size(); i++){
        while(true){
            int sz = st.size();
            if(sz >= 2 and (st[sz-1]-st[sz-2])/(v[i]-st[sz-1])<0) st.pop_back();
            else break;
        }
        st.push_back(v[i]);
    }
    return st;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    vector<pii> CH = convex_hull(v);
    cout << CH.size() << "\n";

    return 0;
}