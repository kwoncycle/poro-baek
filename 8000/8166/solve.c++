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

const pii O = {0, 0};

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    vector<pii> v(n);
    for(ll i=0; i<n; i++){
        cin >> v[i].X >> v[i].Y;
    }
    ll sm1 = 0;
    for(ll i=0; i<n; i++){
        ll sm = 0;
        vector<pii> v1;
        for(ll j=0; j<n; j++){
            if(i!=j) v1.push_back(v[j] - v[i]);
        }
        sort(v1.begin(), v1.end(), [&](pii l, pii r){
            return (l < O) != (r < O) ? l < r : (l)/(r) > 0;
        });
        vector<pii> v2;
        for(auto j:v1){
            if(v2.empty()) v2.push_back(j);
            else if(v2.back()/j != 0 or (v2.back()*j < 0)) v2.push_back(j);
            else v2[v2.size()-1] = v2.back() + j;
        }
        v1 = v2;
        ll i1 = 0, i2 = 0;
        pii vecsm = {0, 0};
        for( ; i1<(int)v2.size(); i1++){
            if(i1 == i2){
                i2 = (i1 + 1) % ((int)v2.size());
                vecsm = v1[i1];
            }
            while(v1[i1]/v1[i2] >= 0 and i1 != i2) {
                vecsm = vecsm + v1[i2];
                i2 = (i2 + 1) % ((int)v2.size());
            }
            sm += v1[i1]/vecsm;
            //cout << i1 << " " << i2 << " " << i << "\n";
            assert(v1[i1]/vecsm >= 0);
            vecsm = vecsm - v1[i1];
        }
        sm1 += sm;
    }
    ll o1 = sm1/6, o2 = sm1%6;
    int arr[6] = {0, 2, 3, 5, 7, 8};
    cout << o1 << "." << arr[o2] << "\n";
    return 0;
}