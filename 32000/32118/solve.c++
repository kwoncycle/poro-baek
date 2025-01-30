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

bool cross(LINE l1, LINE l2){
    if(l1[1]/l2[1] == 0){
        if(l1[1] == pii(0ll,0ll)){
            if((l2[0]-l1[0])/(l2[0]+l2[1]-l1[0]) == 0 and (l2[0]-l1[0])*(l2[0]+l2[1]-l1[0]) <= 0) return true;
            return false;
        }
        if(l2[1] == pii(0ll,0ll)){
            if((l1[0]-l2[0])/(l1[0]+l1[1]-l2[0]) == 0 and (l1[0]-l2[0])*(l1[0]+l1[1]-l2[0]) <= 0) return true;
            return false;
        }
        if((l1[0]-l2[0])/l1[1]) return false;
        ll a = (l1[0])*l1[1], b = (l1[0]+l1[1])*l1[1], c = (l2[0])*l1[1], d = (l2[0]+l2[1])*l1[1];
        if(a>b) swap(a,b); if(c>d) swap(c, d);
        if(b<c or d<a) return false;
        return true;
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

bool isin(vector<ll> &vp, vector<ll> &vm, vector<pii> &v, pii p){
    if(p == pii(0, 0)) return true;
    ll t1;
    if(p > pii(0, 0)){
        if(p/v[vp.back()] < 0){
            t1 = vp.back();
        }
        else if(p/v[vp[0]] >= 0){
            t1 = vm.back();
        }
        else{
            ll ed = 0, st = vp.size()-1;
            while(ed + 1 < st){
                ll md = (st + ed) >> 1;
                if(p/v[vp[md]] < 0) ed = md;
                else st = md;
            }
            t1 = vp[ed];
        }
    }
    else{
        if(p/v[vm.back()] < 0){
            t1 = vm.back();
        }
        else if(p/v[vm[0]] >= 0){
            t1 = vp.back();
        }
        else{
            ll ed = 0, st = vm.size()-1;
            while(ed + 1 < st){
                ll md = (st + ed) >> 1;
                if(p/v[vm[md]] < 0) ed = md;
                else st = md;
            }
            t1 = vm[ed];
        }
    }

    //cout << t1 << "a\n";
    ll n = v.size();
    pii O = {0,0};
    for(ll i=-6; i<=6; i++){
        ll i1 = (n+(t1+i)%n)%n, i2 = (i1+1)%n;
        pii p1 = v[i1], p2 = v[i2];
        if(cross({p1, p2-p1}, {p, p-p})) {
            //cout << p1.X << " " << p1.Y << " " << p2.X << " " << p2.Y << " " << p.X << " " << p.Y << "\n";
            return true;
        }
    }
    for(ll i=-6; i<=6; i++){
        ll i1 = (n+(t1+i)%n)%n, i2 = (i1+1)%n;
        pii p1 = v[i1], p2 = v[i2];
        if(cross({p1, p2-p1}, {p, O-p})) {
            //cout << p1.X << " " << p1.Y << " " << p2.X << " " << p2.Y << " " << p.X << " " << p.Y << "\n";
            return false;
        }
    }
    return true;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, q; cin >> n >> q;
    vector<pii> v(n), prison(q);
    for(ll i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    for(ll i=0; i<q; i++) cin >> prison[i].X >> prison[i].Y;

    ll id = 0;
    while(v[id] > pii(0,0)){
        id = (id+1) % n;
    }
    while(v[id] < pii(0,0)){
        id = (id+1) % n;
    }
    vector<ll> vp, vm;
    for(ll i=0; i<n; i++){
        if(v[(id+i)%n] > pii(0, 0)) vp.push_back((id+i)%n);
        else vm.push_back((id+i)%n);
    }

    vector<ll> pin(q, 0);

    for(ll i=0; i<q; i++){
        if(!i){
            ll b = isin(vp, vm, v, prison[i]);
            pin[i] = b;
        }
        else{
            if(pin[i-1]) prison[i] = prison[i] + prison[i] - prison[i-1];
            else{
                pii o = prison[i] + prison[i-1];
                o.X -= o.X%2;
                o.Y -= o.Y%2;
                prison[i] = {o.X/2, o.Y/2};
                
            }
            ll b = isin(vp, vm, v, prison[i]);
            pin[i] = b;
        }
    }

    for(ll i:pin) cout << i << "\n";
    
    return 0;
}