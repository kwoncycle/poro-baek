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

vector<ll> mp;

ll dst(pii l, pii r){
    return (ll)(l.X - r.X)*(l.X - r.X) + (ll)(l.Y - r.Y)*(l.Y - r.Y);
}

vector<pii> convex_hull(vector<pii> v){
    pii p1 = *min_element(v.begin(), v.end(), [&](pii l, pii r){ return l.Y == r.Y ? l.X < r.X : l.Y < r.Y; });
    sort(v.begin(), v.end(), [&](pii l, pii r){ return (l-p1)/(r-p1)==0 ? (l-p1)*(l-p1)<(r-p1)*(r-p1) : (l-p1)/(r-p1) > 0; });
    vector<pii> st;
    for(auto &p:v){
        while(st.size() >= 2 and (st.back() - st[st.size() - 2]) / (p - st.back()) <= 0) st.pop_back();
        st.push_back(p);
    }
    return st;
}


ll find_min(int t, vector<pii> &v, vector<pii> &dv){
    if(mp[t] >= 0) return mp[t];
    int n = v.size();
    vector<pii> v1(n);
    for(int i=0; i<n; i++) v1[i] = v[i] + pii(dv[i].X*t, dv[i].Y*t);
    sort(v1.begin(), v1.end());
    v1.erase(unique(v1.begin(), v1.end()), v1.end());
    if(v1.size() <= 1) {
        mp[t] = 0;
        return 0;
    }
    
    vector<pii> CH = convex_hull(v1);
    if(CH.size() == 2) {
        mp[t] = dst(CH[0], CH[1]);
        return mp[t];
    }
    n = CH.size();
    ll mx = 0;
    for(int i=0, j=0; i<n; i++){
        mx = max(mx, dst(CH[i], CH[j]));
        while((CH[(i+1)%n] - CH[i])/(CH[(j+1)%n] - CH[j]) >= 0){
            j = j+1; if(j >= n) j -= n;
            mx = max(mx, dst(CH[i], CH[j]));
        }
    }
    mp[t] = mx;
    return mx;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, t; cin >> n >> t;
    vector<pii> v(n), dv(n);
    mp = vector<ll>(t+1, -1);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y >> dv[i].X >> dv[i].Y;
    int s = 0, e = t;
    while(s + 2 < e){
        int m1 = (s*2 + e)/3, m2 = (s + 2*e)/3;
        ll os = find_min(s, v, dv), o1 = find_min(m1, v, dv), o2 = find_min(m2, v, dv), oe = find_min(e, v, dv);
        if(o1 < o2) e = m2;
        else s = m1;
    }

    int id = s;
    for(int i=s; i<=e; i++){
        if(find_min(i, v, dv) < find_min(id, v, dv)) id = i;
    }
    
    ll o = find_min(id, v, dv);
    if(o == find_min(0, v, dv)){
        cout << "0\n";
        cout << o << "\n";
        return 0;
    }
    s = 0, e = id;
    while(s + 1 < e){
        int md = (s + e) >> 1;
        if(find_min(md, v, dv) == o) e = md;
        else s = md;
    }

    cout << e << "\n";
    cout << o << "\n";

    return 0;
}