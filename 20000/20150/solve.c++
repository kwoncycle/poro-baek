#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

typedef array<pll, 2> LINE;
// LINE: l[0] + kl[1]

pll operator + (pll l, pll r){return {l.X+r.X, l.Y+r.Y};}
pll operator - (pll l, pll r){return {l.X-r.X, l.Y-r.Y};}
__int128 operator * (pll l, pll r){return (__int128)l.X*r.X + (__int128)l.Y*r.Y;}
__int128 operator / (pll l, pll r){return (__int128)l.X*r.Y - (__int128)l.Y*r.X;}
pll operator * (pll l, ll r){return {l.X*r, l.Y*r};}

const ll MX = 0x3f3f3f3f3f3f3f3fll;

int sign(__int128 a){
    if(a) return (a>0) ? 1 : -1;
    return 0;
}

bool isintersect(LINE &l, LINE &r){ // segment
    auto &[a,b] = l; auto &[u,v] = r;
    if( (b-a)/(v-u) != 0 ){
        return sign((u-a)/(b-a))*sign((v-a)/(b-a))<=0 && sign((a-u)/(v-u))*sign((b-u)/(v-u))<=0;
    }
    else {
        return ((a-u)/(b-u)==0 && (u-a)/(v-a)==0) && !(max(a,b)<min(u,v) or max(u,v)<min(a,b));
    }
}

bool is_cross_exist(vector<LINE> &v){
    // determines whether there exists crosses, NOT including vertice-cross
    int n = v.size();
    vector<ll> mex;
    bool fail = 0;
    for(auto &[v0, v1]:v){
        if(v0.X == v1.X) fail = 1;
        else{
            if((v1.Y - v0.Y) % (v1.X - v0.X) == 0){
                ll o = (v1.Y - v0.Y) / (v1.X - v0.X);
                if(o >= 0) mex.push_back(o);
            }
        }
    }
    sort(all(mex)); mex.erase(unique(all(mex)), mex.end());
    int id = 0;
    while(id < mex.size() and mex[id] == id) id++;
    if(fail){
        pll p1 = {id, 1}, p2 = {-1, id};
        for(auto &[v0, v1]:v){
            v0 = p1*v0.X + p2*v0.Y, v1 = p1*v1.X + p2*v1.Y;
            if(v0 > v1) swap(v0, v1);
        }
    }
    v.push_back(LINE{pll(-MX, -MX), pll(+MX, -MX)});
    v.push_back(LINE{pll(-MX, +MX), pll(+MX, +MX)});
    vector<array<ll, 4>> event;
    int erase = 1; // 꼭짓점 허용: 0 erase // 허용ㄴㄴ: 1 erase
    for(int i=0; i<n; i++){ 
        event.push_back({v[i][0].X, 1-erase, v[i][0].Y, i});
        event.push_back({v[i][1].X, erase, v[i][0].Y, i});
    }
    sort(all(event)); // 꼭짓점 비허용시 그냥 sort
    set<pll> st;
    st.insert({-MX, n}); st.insert({MX, n+1});
    for(auto &[x, e, y, i]: event){
        if(e != erase){
            auto above = st.lower_bound({y, i}), below = above;
            below--;
            if(isintersect(v[i], v[(*above).Y]) or isintersect(v[i], v[(*below).Y])){
                return true;
            }
            st.insert({y, i});
        }
        else{
            st.erase({y, i});
            auto above = st.lower_bound({y, i}), below = above;
            below--;
            if(isintersect(v[(*below).Y], v[(*above).Y])){
                return true;
            }
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<LINE> v(n);
    for(auto &[p1, p2]:v){
        cin >> p1.X >> p1.Y >> p2.X >> p2.Y;
    }
    if(is_cross_exist(v)) cout << "1\n";
    else cout << "0\n";
    return 0;
}