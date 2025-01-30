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
ll n, l, r;
pll rto;
pll egcd(ll n1, ll n2){
    pll x1={1,0}, x2={0,1};
    if(n1 > n2){
        swap(n1, n2); swap(x1, x2);
    }

    while(n1){
        ll k = n2 / n1;
        x2.X -= k*x1.X;
        x2.Y -= k*x1.Y;
        n2 %= n1;
        swap(n1, n2);
        swap(x1, x2);
    }

    assert(n2 == 1);
    return x2;
}

pll get_rat(ll t){
    pll o = {rto.X * (t), rto.Y * (t)};
    o.X %= r;
    if(o.X < 0) o.X += r;
    assert((t-o.X*l)%r == 0);
    o.Y = (t - o.X*l)/r;
    return o;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> l >> r;
    vector<ll> v(n);
    for(ll i=0; i<n; i++) cin >> v[i];

    ll gd = __gcd(l, r);
    for(ll i=0; i<n; i++){
        if(v[i] % gd){
            cout << "-1\n"; return 0;
        }
        v[i] /= gd;
    }

    l /= gd; r /= gd;
    rto = egcd(l, r);
    
    vector<pll> cnt(n);
    if(v[0]%l){
        cout << "-1\n"; return 0;
    }
    if(v[n-1]%r){
        cout << "-1\n"; return 0;
    }
    cnt[0] = {v[0]/l, 0};
    cnt[n-1] = {0, v[n-1]/r};
    for(ll i=1; i<n-1; i++){
        cnt[i] = get_rat(v[i]);
        if(cnt[i].Y < 0){
            cout << "-1\n"; return 0;
        }
    }

    if(n == 2){
        if(cnt[0].X != cnt[1].Y) cout << "-1\n";
        else{
            cout << "1\n";
            cout << "0 1 " << cnt[0].X << "\n";
        }
        return 0;
    }

    ll v0 = 0, v1 = cnt[n-1].Y;
    for(ll i=n-2; i>=0; i--){
        if(cnt[i].X > v1){
            cout << "-1\n"; return 0;
        }
        v1 += cnt[i].Y; v1 -= cnt[i].X;
    }
    // v1: cnt(l) + v1 = cnt(r)
    if(v1 % ((r+l)) != 0){
        cout << "-1\n"; return 0;
    }

    for(ll i=1; i<n-1; i++){
        ll t1 = cnt[i].Y/l;
        ll t2 = v1 / ((r+l));
        if(t1 < t2){
            cnt[i].X += r*t1;
            cnt[i].Y -= l*t1;
            v1 -= t1*(r+l);
        }
        else{
            cnt[i].X += r*t2;
            cnt[i].Y -= l*t2;
            v1 -= t2*(r+l);
            break;
        }
    }

    if(v1 > 0){
        cout << "-1\n"; return 0;
    }

    vector<array<ll, 3>> ans;
    for(ll i1=0, i2=0; i1<n; i1++){
        while(cnt[i1].X > 0){
            while(i2<n and cnt[i2].Y <= 0) i2++;
            ll t = min(cnt[i1].X, cnt[i2].Y);
            if(t){
                ans.push_back({i1, i2, t});
            }
            cnt[i1].X -= t;
            cnt[i2].Y -= t;
        }
    }

    cout << ans.size() << "\n";
    for(auto [x,y,z]: ans) cout << x << " " << y << " " << z << "\n";
    return 0;
}