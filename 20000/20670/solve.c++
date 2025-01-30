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

bool cross(LINE l1, LINE l2){
    if(l1[1]/l2[1] == 0){
        if((l1[0]-l2[0])/l2[1] != 0) return false;
        ll a = l1[0]*l2[1], b = (l1[0]+l1[1])*l2[1], c = l2[0]*l2[1], d = (l2[0]+l2[1])*l2[1];
        if(b<c or d<a) return false;
        else return true;
    }
    else{
        pll k1 = {(l2[0]-l1[0])/l2[1], l1[1]/l2[1]};
        pll k2 = {(l1[0]-l2[0])/l1[1], l2[1]/l1[1]};
        if(k1.Y < 0) k1.X *= -1, k1.Y *= -1;
        if(k2.Y < 0) k2.X *= -1, k2.Y *= -1;
        if(0 <= k1.X and k1.X <= k1.Y and 0 <= k2.X and k2.X <= k2.Y) return true;
        return false;
    }
}

bool in_polygon(vector<pii> &C, pii p){
    if((C[1]-C[0])/(p-C[0])<=0 or (C.back()-C[0])/(p-C[0])>=0) return false;
    int st, ed;
    for(st = 1, ed = C.size()-1; st + 1 < ed; ){
        int md = (st + ed) >> 1;
        if((C[md]-C[0])/(p-C[0])>0) st = md;
        else ed = md;
    }
    return !cross({C[0], p-C[0]}, {C[st], C[st+1]-C[st]});

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<pii> A(n), B(m), sign(k);
    for(int i=0; i<n; i++) cin >> A[i].X >> A[i].Y;
    for(int i=0; i<m; i++) cin >> B[i].X >> B[i].Y;
    for(int i=0; i<k; i++) cin >> sign[i].X >> sign[i].Y;

    int cnt = 0;
    for(int i=0; i<k; i++){
        if(in_polygon(A, sign[i]) and !in_polygon(B, sign[i])) continue;
        else cnt++;
    }
    if(!cnt) cout << "YES\n";
    else cout << cnt << "\n";
    return 0;
}