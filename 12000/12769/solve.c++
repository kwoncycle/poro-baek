
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};
ll n, m;

ll findb(ll t){
    ll st = 0, ed = n+1; // t0 + t1x + .. + ti x^i = n find it. n < f(ed)
    while(st + 1 < ed){ 
        ll md = (st + ed) / 2;
        __int128 cur = 0;
        __int128 t1 = t, o = 1;
        while(t1){
            cur += (t1%10) * o;
            t1 /= 10;
            o *= md;
            if(cur > n) break;
            if(t1){
                if(o + cur > n){
                    cur = n+1; break;
                }
            }
        }
        if(cur > n) ed = md;
        else st = md;
    }

    __int128 cur = 0, o = 1;
    while(t){
        cur += (t%10) * o;
        t /= 10;
        o *= st;
        if(cur > n) break;
    }
    if(cur == n) return st;
    else return -1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    for(ll i=m; i<=100000; i++){
        if(findb(i) != -1){
            cout << findb(i) << "\n"; return 0;
        }
    }

    for(ll b=100000; b>=2; b--){
        ll n1 = n, cur = 0, o = 1;
        ll truth = 1;
        while(n1){
            if(n1 % b >= 10){
                truth = 0; break;
            }
            cur += (n1%b)*o;
            n1 /= b;
            o *= 10;
        }
        if(cur >= m and truth){
            cout << b << "\n"; return 0;
        }
    }
    return 0;
}