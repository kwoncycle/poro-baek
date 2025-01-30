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

bool iscross(LINE &l1, LINE &l2){
    if(l1[1]/l2[1] == 0){
        if((l1[0]-l2[0])/l1[1]) return false;
        ll a = l1[0]*l1[1], b = (l1[0]+l1[1])*l1[1], c = (l2[0])*l1[1], d = (l2[0]+l2[1])*l1[1];
        if(b<c or d<a) return false;
        return true;
    }
    else{
        pll k1 = {(l2[0]-l1[0])/l2[1], l1[1]/l2[1]};
        pll k2 = {(l1[0]-l2[0])/l1[1], l2[1]/l1[1]};
        if(k1.Y < 0) k1.X *= -1, k1.Y *= -1;
        if(k2.Y < 0) k2.X *= -1, k2.Y *= -1;
        if(0 <= k1.X and k1.X <= k1.Y and 0 <= k2.X and k2.X <= k2.Y) return true;
        else return false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    v.push_back(v[0]);
    pii p[3];
    for(int i=0; i<3; i++) cin >> p[i].X >> p[i].Y;

    for(int t=0; t<3; t++){
        int cnt = 0;
        int truth = 0;
        for(int i=0; i<n; i++){
            LINE l1 = {v[i], v[i+1]-v[i]}, l2 = {p[t], {0,0}}, l3 = {p[t], {0x3f3f3f3f-1, 0x3f3f3f3f}};
            if(iscross(l1, l2)) {
                truth = 1;
            }
            if(iscross(l1, l3)) cnt++;
        }
        if(truth or cnt%2 == 1){
            cout << "1\n";
        }
        else cout << "0\n";
    }
    return 0;
}