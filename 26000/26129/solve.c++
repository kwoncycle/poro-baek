#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pll operator + (pll l, pll r){return {l.X+r.X, l.Y+r.Y};};
pll operator - (pll l, pll r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pll l, pll r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pll l, pll r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

struct solve{
    int n;
    vector<array<ll, 3>> v;
    vector<pll> C1, C2;
    solve(){
        cin >> n;
        v.resize(n);
        for(auto &[i,j,k]:v){
            cin >> i >> j >> k;
        }
        pll mx = {1, 0x3f3f3f3f}, mn = {1, -0x3f3f3f3f};
        for(auto &[t, l, r]:v){
            // C1
            pll L = {t, l}, R = {t, r};
            if(C1.size() <= 2){
                for(auto &p:C1){
                    pll o = R-p;
                    if(o/mx > 0) mx = o;
                }
            }
            else{
                int sz = C1.size();
                if( (C1[1]-C1[0])/(R-C1[0]) >= 0 ){
                    pll o = R - C1[0];
                    if(o/mx > 0) mx = o;
                }
                else if( (C1[sz-1]-C1[sz-2])/(R-C1[sz-2]) < 0 ){
                    pll o = R - C1[sz-1];
                    if(o/mx > 0) mx = o;
                }
                else{
                    int st = 0, ed = sz-2; // C1[st+1]-C1[st]/R-C1[st] < 0,  ed: >= 0
                    while(st + 1 < ed){
                        int md = (st + ed) / 2;
                        if((C1[md+1]-C1[md])/(R-C1[md]) < 0) st = md;
                        else ed = md;
                    }
                    pll o = R - C1[ed];
                    if(o/mx > 0) mx = o;
                }
            }
            if(C1.empty() or C1.size() == 1){
                C1.push_back(L);
            }
            else{
                while(C1.size() >= 2){
                    int sz = C1.size();
                    if((C1[sz-1] - C1[sz-2]) / (L - C1[sz-1]) >= 0) C1.pop_back();
                    else break;
                }
                C1.push_back(L);
            }

            // C2

            if(C2.size() <= 2){
                for(auto &p:C2){
                    pll o = L-p;
                    if(o/mn < 0) mn = o;
                }
            }
            else{
                int sz = C2.size();
                if( (C2[1]-C2[0])/(L-C2[0]) <= 0 ){
                    pll o = L - C2[0];
                    if(o/mn < 0) mn = o;
                }
                else if( (C2[sz-1]-C2[sz-2])/(L-C2[sz-2]) > 0 ){
                    pll o = L - C2[sz-1];
                    if(o/mn < 0) mn = o;
                }
                else{
                    int st = 0, ed = sz-2; // C2[st+1]-C2[st]/L-C1[st] > 0,  ed: <= 0
                    while(st + 1 < ed){
                        int md = (st + ed) / 2;
                        if((C2[md+1]-C2[md])/(L-C2[md]) > 0) st = md;
                        else ed = md;
                    }
                    pll o = L-C2[ed];
                    if(o/mn < 0) mn = o;
                }
            }
            if(C2.empty() or C2.size() == 1){
                C2.push_back(R);
            }
            else{
                while(C2.size() >= 2){
                    int sz = C2.size();
                    if((C2[sz-1] - C2[sz-2]) / (R - C2[sz-1]) <= 0) C2.pop_back();
                    else break;
                }
                C2.push_back(R);
            }

        }
        cout << fixed << setprecision(15) << (long double)mn.Y/(long double)mn.X << " " << (long double)mx.Y/(long double)mx.X << "\n";
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve s;
    return 0;
}