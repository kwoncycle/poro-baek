#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};
pii operator * (pii l, ll r){return {l.X*r, l.Y*r};};

bool isonLine(LINE L, pii p){
    if((p-L[0])/L[1] == 0) return true;
    return false;
}

pii cross(LINE &l1, LINE &l2){
    pll t = {(l1[0]-l2[0])/l1[1], l2[1]/l1[1]};
    if(t.X%t.Y != 0){
        return {-0x3f3f3f3f, -0x3f3f3f3f};
    }
    return l2[0] + l2[1]*(t.X/t.Y);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll tt; cin >> tt;
    while(tt--){
        ll n; cin >> n;
        vector<pii> v(n);
        for(ll i=0; i<n; i++) {
            cin >> v[i].X >> v[i].Y;
        }
        vector<LINE> entry;
        vector<pii> dots;
        vector<LINE> e1;
        set<pii> d1;
        entry.push_back({v[0], {0, 1}});
        entry.push_back({v[0], {1, 1}});
        entry.push_back({v[0], {1, 0}});
        entry.push_back({v[0], {1, -1}});
        for(ll i=1; i<n; i++){
            e1.clear(); d1.clear();
            for(auto d:dots){
                if(d.X == v[i].X or d.Y == v[i].Y or abs(d.X-v[i].X) == abs(d.Y - v[i].Y)) d1.insert(d);
            }

            for(auto &ln:entry){
                LINE L = {v[i], {0, 1}};
                if(ln[1] == L[1]){
                    if(isonLine(L, ln[0])) e1.push_back(ln);
                }
                else{
                    auto t = cross(L, ln);
                    if(t.X != -0x3f3f3f3f) d1.insert(t);
                }

                L = {v[i], {1, 1}};
                if(ln[1] == L[1]){
                    if(isonLine(L, ln[0])) e1.push_back(ln);
                }
                else{
                    auto t = cross(L, ln);
                    if(t.X != -0x3f3f3f3f) d1.insert(t);
                }

                L = {v[i], {1, 0}};
                if(ln[1] == L[1]){
                    if(isonLine(L, ln[0])) e1.push_back(ln);
                }
                else{
                    auto t = cross(L, ln);
                    if(t.X != -0x3f3f3f3f) d1.insert(t);
                }

                L = {v[i], {1, -1}};
                if(ln[1] == L[1]){
                    if(isonLine(L, ln[0])) e1.push_back(ln);
                }
                else{
                    auto t = cross(L, ln);
                    if(t.X != -0x3f3f3f3f) d1.insert(t);
                }
            }

            entry = e1;
            dots.clear();
            for(auto &d:d1) {
                int truth = 1;
                for(auto &ln:entry){
                    if(isonLine(ln, d)){
                        truth = 0; break;
                    }
                }
                if(truth) dots.push_back(d);
            }

            //for(auto [x, y]:entry) cout << x.X << "," << x.Y << " + " << y.X << "," << y.Y << "\n";
            //for(auto [x, y]:dots) cout << x << "," << y << " dots\n"; 
        }
        if(entry.empty() and dots.empty()){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
            if(!entry.empty()) cout << entry[0][0].X << " " << entry[0][0].Y << "\n";
            else cout << dots[0].X << " " << dots[0].Y << "\n";
        }
        
    }
    return 0;
}