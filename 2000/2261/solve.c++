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
ll o;
vector<pii> st;

void convex_hull(vector<pii> &v){
    pii p1 = *min_element(v.begin(), v.end(), [&](pii l, pii r){ return l.Y == r.Y ? l.X < r.X : l.Y < r.Y;});
    sort(v.begin(), v.end(), [&](pii l, pii r){ 
        o = (l-p1)/(r-p1);
        return o == 0 ? (l-p1)*(l-p1)<(r-p1)*(r-p1) : o > 0;
    });
    //int id = v.size() - 1;
    //while(id > 1 and (v[id-1]-p1)/(v.back()-p1) == 0) id--;
    //reverse(v.begin() + id, v.end());
    
    for(auto &p:v){
        while(st.size() >= 2 and (st.back() - st[st.size()-2])/(p - st.back()) <= 0) st.pop_back();
        st.push_back(p);
    }
}

ll dst(pii &l, pii &r){
    return (ll)(l.X-r.X)*(l.X-r.X) + (ll)(l.Y-r.Y)*(l.Y-r.Y);
}

ll find_min(int i1, int i2, vector<pii> &v){ // [i1, i2)
    if(i2 - i1 <= 4){
        ll mn = 0x3f3f3f3f3fll;
        for(int i=i1; i<i2; i++){
            for(int j=i+1; j<i2; j++) mn = min(mn, dst(v[i], v[j]));
        }
        return mn;
    }

    int md = (i1 + i2) >> 1;
    ll m1 = find_min(i1, md, v);
    ll m2 = find_min(md, i2, v);
    ll d = min(m1, m2);
    vector<int> v1;
    for(int i=md-1; i>=i1; i--){
        if((v[md].X - v[i].X)*(v[md].X - v[i].X) <= d) v1.push_back(i);
        else break;
    }
    for(int i=md; i<i2; i++){
        if((v[i].X - v[md].X)*(v[i].X - v[md].X) <= d) v1.push_back(i);
        else break;
    }

    sort(v1.begin(), v1.end(), [&](int i1, int i2){return v[i1].Y < v[i2].Y;});

    for(int i=0; i<(int)v1.size(); i++){
        for(int j=i+1; j<=min(i+8, (int)v1.size()-1); j++){
            d = min(d, dst(v[v1[i]], v[v1[j]]));
        }
    }

    return d;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    sort(v.begin(), v.end());
    cout << find_min(0, n, v) << "\n";

    return 0;
}