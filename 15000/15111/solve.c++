#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pll operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pll operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};


#define A4 array<int,4>


struct D{
    vector<pll> v;
    D(){
        v.push_back({0, 0});
    }
    ll f(ll i, ll x){
        return v[i].Y - 2*x*v[i].X + x*x;
    }
    ll find(ll x){
        int st = 0, ed = v.size()-1;
        if(st == ed) return f(st, x);
        if(f(st, x) <= f(st+1, x)) return f(st, x);
        if(f(ed-1, x) >= f(ed, x)) return f(ed, x);
        while(st + 1 < ed){
            int md = (st + ed) >> 1;
            if(f(md, x) >= f(md + 1, x)) st = md;
            else ed = md;
        }
        return f(ed, x);
    }
    void push(ll x, ll val){ // a에서 val x
        pll t = {x, val + x*x};
        while(v.size() >= 2){
            int n = v.size();
            if((v[n-1]-v[n-2])/(t - v[n-1]) < 0) v.pop_back();
            else break;
        }
        v.push_back(t);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<A4> v(m);
    for(int i=0; i<m; i++){
        for(int j=0; j<4; j++) cin >> v[i][j];
        v[i][0]--; v[i][1]--;
    }

    sort(v.begin(), v.end(), [&](A4 l, A4 r){
        return l[2] == r[2] ? (l[3] < r[3]) : (l[2] < r[2]);
    });

    vector<D> vd(n);
    ll mn = 0x3f3f3f3f3f3f3f3fll;
    for(int i=0; i<m; i++){
        ll x = vd[v[i][0]].find(v[i][2]);
        vd[v[i][1]].push(v[i][3], x);
        cout << v[i][1] << " " << v[i][3] << "," << x << "\n";
        if(v[i][1] == n-1) mn = min(mn, x);
    }

    cout << mn << "\n";
    return 0;
}