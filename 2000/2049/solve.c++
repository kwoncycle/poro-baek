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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    if(v.size() == 1) { cout << "0\n"; return 0; }
    
    convex_hull(v);
    if(st.size() == 2){
        cout << dst(st[0], st[1]) << "\n"; return 0;
    }
    n = st.size();
    ll mx = 0, j = 0;
    for(int i=0; i<n; i++){
        mx = max(mx, dst(st[i], st[j]));
        while((st[(i+1)%n] - st[i])/(st[(j+1)%n] - st[j]) >= 0){
            j = (j+1) % n;
            mx = max(mx, dst(st[i], st[j]));
        }
    }
    cout << mx << "\n";

    return 0;
}