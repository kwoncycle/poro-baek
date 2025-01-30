/* 
    NEW YCLOCK JUST BEAT YCLOCK HAHAHAHAHAHAHAHA
*/

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
pii operator * (pii l, ll r){return {l.X*r, l.Y*r};};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};
const pii O = {0,0};

pii out1(ll a, ll b){
    ll sa = a, sb = b;
    ll ax = 1, ay = 0, bx = 0, by = 1;
    if(a < 0){
        a*=-1; ax *= -1; ay *= -1;
    }
    if(b < 0){
        b*=-1; bx *= -1; by *= -1;
    }
    if(a>b){
        swap(a,b); swap(ax,bx); swap(ay,by);
    }
    while(a){
        bx -= (b/a)*ax;
        by -= (b/a)*ay;
        b = b%a;
        swap(a,b); swap(ax,bx); swap(ay,by);
    }
    assert(b == 1);
    bx %= sb;
    by = (1-bx*sa)/sb;
    return {bx, by};
}
#define MX 1024
bool isin(pii l){
    return -MX <= l.X and l.X <= MX-1 and -MX <= l.Y and l.Y <= MX-1;
}

pii reduce(pii l, pii r){
    ll o = l*r, o1 = r*r;
    o = o/o1;
    l = l - r*o;
    if(isin(l)) return l;
    if(isin(l + r)) return l + r;
    if(isin(l - r)) return l - r;
    return l;
}


#define JSZ 100
int mp[8328][8328];

pii v1[10196496];
int main(){
    memset(mp, -1, sizeof(mp));
    ll cntv1 = 0;
    {
        ll a = 0, b = 1, c = 1, d = MX*2-1;
        ll n = MX*2 - 1;
        v1[cntv1++] = {b, a};
        while(c <= n){
            ll k = (n + b) / d;
            ll nc = k*c - a, nd = k*d - b;
            a = c; b = d; c = nc; d = nd;
            v1[cntv1++] = {b, a};
        }
        ll u = cntv1 - 2;
        while(u) v1[cntv1++] = {v1[u].Y, v1[u--].X};
        u = cntv1;
        for(ll i=0; i<u; i++){
            v1[i + u] = {-v1[i].Y, v1[i].X}; 
        }
        for(ll i=u; i<2*u; i++){
            v1[i + u] = {-v1[i].Y, v1[i].X}; 
        }
        for(ll i=2*u; i<3*u; i++){
            v1[i + u] = {-v1[i].Y, v1[i].X}; 
        }
        rotate(v1, v1 + 2549124 + 1, v1 + 10196496);
    }
    
    vector<pii> v;
    for(ll i=0; i<10196496; i++){
        pii t = v1[i] + v1[i ? i-1 : 10196495];
        ll o = abs(__gcd(t.X, t.Y));
        t.X /= o; t.Y /= o;
        v.emplace_back(t.X, t.Y);
    }

    ll n = v.size();
    for(ll i=0; i<n; i++){
        mp[v1[i].X + 4120][v1[i].Y + 4120] = i;
    }
    
    int Q = 0;
    vector<pii> zmt;
    vector<int> zmt_idx, zmt_nxt;
    for(int i=0; i<JSZ; i++){
        int idx = (10196495/JSZ)*i;
        pii o1 = out1(v[idx].X, v[idx].Y);
        pii o = {o1.Y, -o1.X};
        if(v[idx]/o > 0) o = {-o.X, -o.Y};
        ll st = 0, ed = (abs(v[idx].X) + abs(v[idx].Y)) * 1024 + 1; // st > 0 ed = 0
        for(auto x:zmt){
            st = max(st, x/v[idx]);
        }
        if(true){
            pii ot1 = reduce(o*st, v[idx]), ot2 = ot1 + v[idx];
            cout << "? " << ot1.X << " " << ot1.Y << " " << ot2.X << " " << ot2.Y << endl;
            string s; cin >> s; Q++;
            if(s[0] - '0' == 1){
                continue;
            }
        }
        while(st + 1 < ed){
            ll md = (st+ed)/2;
            if(md == st) md++;
            pii ot1 = reduce(o*md, v[idx]), ot2 = ot1 + v[idx];
            cout << "? " << ot1.X << " " << ot1.Y << " " << ot2.X << " " << ot2.Y << endl;
            string s; cin >> s;
            Q++; if(Q >= 4096) {cout << "! 88848" << endl; string s; cin >> s; return 0;}
            if(s[0] - '0' == 0) ed = md;
            else if(s[0] - '0' == 1){
                st = md; break;
            }
            else st = md;
        }
        pii ot1 = reduce(o*st, v[idx]), ot2 = ot1 + v[idx];
        pii ot;
        for(ll j=-3; j<=3; j++){
            if(isin(ot1 + v[idx]*j)){
                ot = ot1 + v[idx]*j; break;
            }
        }
        zmt.push_back(ot);
        zmt_idx.push_back(idx);
    }
    
    for(int i=0; i<(int)zmt.size(); i++){
        pii ot = zmt[i];
        int idx = zmt_idx[i];
        pii n1 = zmt[(i+1)%(int)zmt.size()], n2 = zmt[(i+2)%(int)zmt.size()];
        ll u = abs(__gcd(ot.X, ot.Y));
        ll st = idx, ed = mp[-ot.X/u + 4120][-ot.Y/u + 4120];
        if(st >= ed) ed += n;
        for(auto j:zmt){
            if(ot == j) continue;
            pii u1 = j - ot;
            u = abs(__gcd(u1.X, u1.Y));
            u1.X /= u; u1.Y /= u;
            ll id = mp[u1.X + 4120][u1.Y + 4120];
            if(st >= id) id += n;
            ed = min(ed, id);
        }
        vector<int> idxs;
        for(int j=st; j<=ed; j++){
            pii p = ot + v1[j%n];
            if(isin(p)) {
                if(zmt.size() > 5){
                    if((n1-p)/(n2-n1) > 0 or n1 == p) idxs.push_back(j);
                }
                else idxs.push_back(j);
            }
        }
        st = -1, ed = idxs.size()-1; // st 1 ed > 1
        if(st < ed and ed and false) {
            ll md = idxs[ed - 1];
            pii oot1 = ot, oot2 = oot1 + v1[md%n];
            cout << "? " << oot1.X << " " << oot1.Y << " " << oot2.X << " " << oot2.Y << endl;
            string s; cin >> s;
            Q++; if(Q >= 4096) {cout << "! 88848" << endl; string s; cin >> s; return 0;}
            if(s[0] == '1'){
                st = ed - 1;
            }
            else if(s[0] == 'i'){
                ed = ed - 1;
                st = ed - 1;
            }
            else ed--;
        }
        while(st + 1 < ed){
            ll md1 = (st*3 + ed*2) / 5;
            if(st == md1) md1++;
            ll md = idxs[md1];
            pii oot1 = ot, oot2 = oot1 + v1[md%n];
            cout << "? " << oot1.X << " " << oot1.Y << " " << oot2.X << " " << oot2.Y << endl;
            string s; cin >> s;
            Q++; if(Q >= 4096) {cout << "! 88848" << endl; string s; cin >> s; return 0;}
            if(s[0] - '0' == 1) st = md1;
            else if(s[0] == 'i'){
                ed = md1; st = ed - 1; break;
            }
            else ed = md1;
        }
        zmt_nxt.push_back(idxs[ed]);
    }

    vector<vector<pii>> next_dots((int)zmt.size());
    for(int i=0; i<(int)zmt.size(); i++){
        pii nxt = zmt[(i + 1) % ((int)zmt.size())];
        int nxt_idx = zmt_nxt[(i + 1) % ((int)zmt.size())];
        int cur_idx = zmt_nxt[i];
        pii cur_p = zmt[i];
        int cntt = 0;
        while(true){
            if(v1[cur_idx]/(nxt - cur_p) == 0) break;
            int st = 1, ed = 2048 / max(abs(v1[cur_idx].X), abs(v1[cur_idx].Y)) + 2; // st >= 1, ed = 0
            int sz = ed;
            while(!isin(cur_p + v1[cur_idx]*(ed - 1))) ed--;
            if(true){
                ll md = st;
                pii ot1 = cur_p + v1[cur_idx] * md, ot2 = ot1 + v[(cur_idx + 1) % n];
                cout << "? " << ot1.X << " " << ot1.Y << " " << ot2.X << " " << ot2.Y << endl;
                string s; cin >> s;
                Q++; if(Q >= 4096) {cout << "! 88848" << endl; string s; cin >> s; return 0;}
                if(s[0] - '0' == 1){
                    st = md; ed = st + 1;
                }
                else st++;
            }
            while(st + 1 < ed){
                ll md = (st*7 + ed*2) / 9;
                if(md == st) md++;
                pii ot1 = cur_p + v1[cur_idx] * md, ot2 = ot1 + v[(cur_idx + 1) % n];
                cout << "? " << ot1.X << " " << ot1.Y << " " << ot2.X << " " << ot2.Y << endl;
                string s; cin >> s;
                Q++; if(Q >= 4096) {cout << "! 88848" << endl; string s; cin >> s; return 0;}
                if(s[0] - '0' == 0) ed = md;
                else if(s[0] - '0' == 1){
                    st = md; break;
                }
                else st = md;
            }
            cur_p = cur_p + v1[cur_idx] * st;
            next_dots[i].push_back(cur_p);
            vector<int> idxs;
            pii tmp = nxt - cur_p;
            ll u = abs(__gcd(tmp.X, tmp.Y));
            st = (cur_idx + 1) % n, ed = mp[tmp.X/u + 4120][tmp.Y/u + 4120];
            if(st > ed) ed += n;
            for(int j=st; j<=ed; j++){
                pii u1 = cur_p + v1[j%n];
                if((nxt - u1)/v1[nxt_idx] > 0 or nxt == u1) {
                    idxs.push_back(j);
                }
            }
            st = -1, ed = idxs.size()-1;
            while(st + 1 < ed){
                ll md1 = (st + ed) / 2;
                if(st == md1) md1++;
                ll md = idxs[md1];
                pii oot1 = cur_p, oot2 = oot1 + v1[md%n];
                cout << "? " << oot1.X << " " << oot1.Y << " " << oot2.X << " " << oot2.Y << endl;
                string s; cin >> s;
                Q++; if(Q >= 4096) {cout << "! 88848" << endl; string s; cin >> s; return 0;}
                if(s[0] - '0' == 1) st = md1;
                else if(s[0] == 'i'){
                    ed = md1; st = ed - 1; break;
                }
                else ed = md1;
            }
            cur_idx = idxs[ed] % n;
        }
    }

    vector<pii> conv;
    for(int i=0; i<(int)zmt.size(); i++){
        conv.push_back(zmt[i]);
        for(auto j:next_dots[i]) conv.push_back(j);
    }
    ll Area = 0;
    n = conv.size();
    for(ll i=0; i<n; i++){
        Area += conv[i]/conv[(i+1)%n];
    }
    long double A = Area; A /= 2.0;
    cout << fixed << setprecision(5) <<  "! " << A << endl; 
    string s; cin >> s;
    return 0;
}