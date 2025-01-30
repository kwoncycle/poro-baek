#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define ld long double
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]
const ld eps = 1e-12;
pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};
ll dist(pll a,pll b) { return (b-a)*(b-a); }
ll ccw(pll a,pll b,pll c) { return (b-a)/(c-a); }
bool onsegment(pll a,pll b,pll p) { return ccw(a,b,p) == 0 && (a-p)*(b-p) <= 0; }
ll sign(ld x) { return abs(x)<eps?0:(x<0?-1:1); }


pii lr(pii p, vector<pii> &v){
    ll nv = v.size(), i1 = 0;
    pii ans;
    if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
    if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) > 0){
        for(ll T = (1<<20); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p) / (v[(id+1)%nv]-v[id]) >= 0 and (v[i1] - p) / (v[id] - p) >= 0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.X = i1;
        if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
        for(ll T = (1<<16); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p) / (v[(id+1)%nv]-v[id]) < 0 and (v[i1] - p) / (v[id] - p) < 0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.Y = i1;
        return ans;
    }
    else{
        for(ll T = (1<<20); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p) / (v[(id+1)%nv]-v[id]) < 0 and (v[i1] - p) / (v[id] - p) < 0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.Y = i1;
        if((v[i1]-p)/(v[(i1+1)%nv]-v[i1]) == 0) i1 = (i1+1) % nv;
        for(ll T = (1<<16); T >= 1; T >>= 1){
            if(T >= nv) continue;
            ll id = (i1 + T) % nv;
            if((v[id]-p) / (v[(id+1)%nv]-v[id]) >= 0 and (v[i1] - p) / (v[id] - p) >= 0) i1 = id;
        }
        i1 = (i1 + 1) % nv;
        ans.X = i1;
        return ans;
    }
}


ll findut(pii p,vector<pii>&A){ //L,L 찾기, ccw
    ll l=0,r=A.size()-1,m,b,a,n=A.size();
    while(l<r) {
        m=(l+r+1)/2;
        b=(m-1+n)%n; a=(m+1)%n; //b->m->a
        if(ccw(p,A[0],A[n-1])<=0){ // 앞 R
            if(ccw(p,A[m],A[b])<=0&&ccw(p,A[m],A[a])>=0&&ccw(p,A[0],A[m])<0) r=m-1;
            else l=m;
        }
        else {
            if(ccw(p,A[m],A[b])<=0||(ccw(p,A[m],A[b])>0&&ccw(p,A[m],A[a])<0&&ccw(p,A[0],A[m])>0)) r=m-1;
            else l=m;
        }
    }
    return l;
}

ll findlt(pii p,vector<pii>&A) {
    ll l=0,r=A.size()-1,m,b,a,n=A.size();
    while(l<r) {
        m=(l+r+1)/2;
        b=(m-1+n)%n; a=(m+1)%n; //b->m->a
        if(ccw(p,A[0],A[n-1])>0){ // 앞 L
            if(ccw(p,A[m],A[b])>0&&ccw(p,A[m],A[a])<0&&ccw(p,A[0],A[m])>0)
                r=m-1;
            else l=m;
        }
        else {
            if(ccw(p,A[m],A[b])>0||(ccw(p,A[m],A[b])<=0&&ccw(p,A[m],A[a])>=0&&ccw(p,A[0],A[m])<0))
                r=m-1;
            else l=m;
        }
    }
    return l;
}

bool inHull(const vector<pii>& H, pll p, bool strict = true) {
    int a = 1, b = H.size() - 1, r = !strict;
    if (H.size() < 3) return r && onsegment(H[0], H.back(), p);
    if (ccw(H[0], H[a], H[b]) > 0) swap(a, b);
    if (sign(ccw(H[0], H[a], p)) >= r || sign(ccw(H[0], H[b], p)) <= -r) return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        (ccw(H[0], H[c], p) > 0 ? b : a) = c;
    }
    return sign(ccw(H[a],H[b],p)) < r;
}

void fillv(int l, int r, vector<int> &v){
    int n = v.size()-1;
    if(l <= r){
        v[l]++; v[r+1]--; return;
    }
    else{
        fillv(l, n-1, v); fillv(0, r, v);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    vector<int> vt(n+1, 0);
    int m; cin >> m;

    while(m--){
        pii p; cin >> p.X >> p.Y;
        if(inHull(v, p)) continue;
        auto [l, r] = lr(p, v);
        if(l == r) continue;
        int l1 = findlt(p, v);
        int r1 = findut(p, v);
        assert(l1==l and r1==r);
        fillv((l+1)%n, r, vt);
    }

    for(int i=1; i<n; i++){
        vt[i] = vt[i-1] + vt[i];
    }
    int cnt = 0;
    for(int i=0; i<n; i++){
        if(!vt[i]) cnt++;
    }
    cout << cnt << "\n";
    return 0;
}