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

bool cross(LINE &l1, LINE &l2){
    if((l1[1]/l2[1]) == 0){
        if((l1[0]-l2[0])/l1[1]) return false;
        ll a = l1[0]*l1[1], b = (l1[0]+l1[1])*l1[1], c = l2[0]*l1[1], d = (l2[0]+l2[1])*l1[1];
        if(a>b) swap(a,b);
        if(c>d) swap(c,d);
        if(b<c or d<a) return false;
        else return true;
    }
    else{
        pll t = {(l1[0]-l2[0])/l1[1], l2[1]/l1[1]};
        pll k = {(l2[0]-l1[0])/l2[1], l1[1]/l2[1]};
        if(t.Y < 0) t.X *= -1, t.Y *= -1;
        if(k.Y < 0) k.X *= -1, k.Y *= -1;
        if(0<=t.X and t.X <= t.Y and 0<=k.X and k.X <= k.Y) return true;
        else return false;
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    LINE l1, l2;
    for(int i=0; i<2; i++) cin >> l1[i].X >> l1[i].Y;
    for(int i=0; i<2; i++) cin >> l2[i].X >> l2[i].Y;
    l1[1] = l1[1] - l1[0];
    l2[1] = l2[1] - l2[0];

    bool b = cross(l1, l2);
    cout << (int)b << "\n";
    return 0;
}