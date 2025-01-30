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

int n;
vector<array<int, 2>> query;
vector<int> S_idx;

struct sx{
    int i;
    sx(int i):i(i){};
    bool operator < (const sx r) const{
        return query[i][0] == query[r.i][0] ? i < r.i : query[i][0] < query[r.i][0];
    }
    bool operator == (const sx r) const{
        return i == r.i;
    }
};

struct sy{
    int i;
    sy(int i):i(i){};
    bool operator < (const sy r) const{
        return query[i][1] == query[r.i][1] ? i < r.i : query[i][1] < query[r.i][1];
    }
    bool operator == (const sy r) const{
        return i == r.i;
    }
};



struct S{
    set<sx> x; set<sy> y;
    pii l, r;
    int color;
};

vector<S> v;

void divide(int target){
    int id = S_idx[target];
    if(v[id].color == 1){
        S new_S;
        new_S.color = 0;
        v[id].color = 0;
        int si = v.size();
        auto i1 = v[id].x.begin();
        auto i2 = v[id].x.rbegin();
        int front = 0;
        for(int i=0; i<n; i++){
            if((*i1).i == target) {
                front = 1; break;
            }
            if((*i2).i == target){
                front = 0; break;
            }
            i1++; i2++;
        }

        if(front){
            new_S.l = v[id].l;
            new_S.r = {query[target][0], v[id].r.Y};
            v[id].l = {query[target][0], v[id].l.Y};
            // v[id].r = v[id].r;

            while(true){
                
                auto i = v[id].x.begin();
                int t = (*i).i;
                v[id].x.erase(v[id].x.find(sx(t)));
                v[id].y.erase(v[id].y.find(sy(t)));
                if(t == target) break;
                new_S.x.insert(sx(t));
                new_S.y.insert(sy(t));
                S_idx[t] = si;
            }
        }
        else{
            new_S.l = {query[target][0], v[id].l.Y};
            new_S.r = v[id].r;
            // v[id].l = v[id].l;
            v[id].r = {query[target][0], v[id].r.Y};

            while(true){
                auto i = v[id].x.rbegin();
                int t = (*i).i;
                v[id].x.erase(v[id].x.find(sx(t)));
                v[id].y.erase(v[id].y.find(sy(t)));

                if(t == target) break;
                new_S.x.insert(sx(t));
                new_S.y.insert(sy(t));
                S_idx[t] = si;
            }
        }
        pii newrct = (new_S.r - new_S.l), vrct = v[id].r - v[id].l;
        ll o1 = (ll)newrct.X * newrct.Y, o2 = (ll)vrct.X * vrct.Y;
        //cout << min(o1, o2) << " " << max(o1, o2) << "\n";
        v.push_back(new_S);
    }
    else{
        S new_S; 
        new_S.color = 1;
        v[id].color = 1;
        int si = v.size();
        auto i1 = v[id].y.begin();
        auto i2 = v[id].y.rbegin();
        int front = 0;
        for(int i=0; i<n; i++){
            if((*i1).i == target) {
                front = 1; break;
            }
            if((*i2).i == target){
                front = 0; break;
            }
            i1++; i2++;
        }

        if(front){
            new_S.l = v[id].l;
            new_S.r = {v[id].r.X, query[target][1]};
            v[id].l = {v[id].l.X, query[target][1]};
            // v[id].r = v[id].r;

            while(true){
                auto i = v[id].y.begin();
                int t = (*i).i;
                v[id].y.erase(v[id].y.find(sy(t)));
                v[id].x.erase(v[id].x.find(sx(t)));

                if(t == target) break;
                new_S.y.insert(sy(t));
                new_S.x.insert(sx(t));
                S_idx[t] = si;
            }
        }
        else{
            new_S.l = {v[id].l.X, query[target][1]};
            new_S.r = v[id].r;
            //v[id].l = v[id].l;
            v[id].r = {v[id].r.X, query[target][1]};

            while(true){
                auto i = v[id].y.rbegin();
                int t = (*i).i;
                v[id].y.erase(v[id].y.find(sy(t)));
                v[id].x.erase(v[id].x.find(sx(t)));

                if(t == target) break;
                new_S.y.insert(sy(t));
                new_S.x.insert(sx(t));
                S_idx[t] = si;
            }
        }
        pii newrct = (new_S.r - new_S.l), vrct = v[id].r - v[id].l;
        ll o1 = (ll)newrct.X * newrct.Y, o2 = (ll)vrct.X * vrct.Y;
        //cout << min(o1, o2) << " " << max(o1, o2) << "\n";
        v.push_back(new_S);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int a, b; cin >> a >> b;

    cin >> n;
    query.resize(n);
    S_idx.resize(n);
    for(int i=0; i<n; i++){
        cin >> query[i][0] >> query[i][1]; // 0,1: x,y / 2: d
    }
    
    S ns; 
    ns.l = {0,0}; ns.r = {a,b}; ns.color = 0; // 1 black 0 white
    for(int i=0; i<n; i++){
        ns.x.insert(sx(i));
        ns.y.insert(sy(i));
    }
    v.push_back(ns);

    for(int i=0; i<n; i++){
        divide(i);
    }

    ll mn = 0x3f3f3f3f3f3fll, mx = 0;
    for(auto s:v){
        ll A = (ll)(s.r.X-s.l.X)*(s.r.Y-s.l.Y);
        mn = min(mn, A);
        mx = max(mx, A);
    }

    cout << mx << " " << mn << "\n";

    return 0;
}