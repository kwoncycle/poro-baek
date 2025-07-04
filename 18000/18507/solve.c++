#include <bits/stdc++.h>
#include <math.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

vector<__int128> powv[22];
vector<long double> dv;
void filldata(){
    for(ll i=0; i<=1000000; i++){
        powv[1].push_back(i);
        for(ll d=2; d<=20; d++){
            if(powv[d-1][i] * i <= 1000000){
                powv[d].push_back(powv[d-1][i] * i);
            }
            else break;
        }
    }
    for(ll d=1; d<=20; d++) powv[d].push_back(0x3f3f3f3f3f3f3f3fll);
    dv.push_back(-0x3f3f3f3f3f3f3f3fll);
    for(ll i=1; i<=1000000; i++){
        dv.push_back(log10l((long double)i));
    }
    dv.push_back(0x3f3f3f3f3f3fll);
}


ll pow_n(ll a, ll n){ // return a^1/n, only positive
    assert(a >= 0);
    if(n == 1) return a;
    if(a <= 1) return a;
    if(n > 20) return -1;
    ll i = CNT_LOWER(powv[n], a);
    if(powv[n][i] == a) return i;
    else return -1;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    filldata();

    ll n, m; cin >> n >> m;
    if(n % 2 == 0){
        ll ans = 1; // (0, 0)
        for(ll q=1; q<=m; q++){
            if(q % (n-1) == 0){
                ll U = q / (n-1);
                ll o = pow_n(U, n);
                if(o != -1){
                    assert(U%o == 0);
                    if(abs(U/o) <= m) {
                        ans += 2;
                    }
                }
            }
        }
        cout << ans << "\n"; return 0;
    }
    else{
        ll ans = (m + 1) * (2*m + 1);
        for(ll p=-1; p>=-m; p--){
            if((-p) % n == 0){
                ll U = (-p) / n;
                ll o = pow_n(U, n-1);
                if(o != -1){
                    ll tp = (__int128)(n-1) * (U) * (o);
                    //tp+1 .. m
                    if(tp + 1 <= m){
                        //cout << p << " " << tp << "\n";
                        ans += 2*(m - tp);
                    }
                    continue;
                }
            }
            long double D1 = (long double)(n-1) * pow((long double)(-p)/n, (long double)1 + (long double)1/(long double)(n-1));
            // if(D1 > m) continue;
            // ll i1 = int(D1);
            // while(i1 <= D1) i1++;
            // if(i1 <= m) ans += 2*(m-i1+1);
            // continue;
            long double D = log10l(n-1) + (long double)n/(long double)(n-1)*log10l((long double)(-p)/(long double)n);
            //D += (long double)1e-8;
            ll i = CNT_UPPER(dv, D);
            if(i <= m){
                ans += 2*(m-i+1);
            }
        }

        // ll ans1 = 0;
        // for(ll c=-m; c<=m; c++){
        //     if(4*c*c*c + 27*m*m <= 0) continue;
        //     if(4*c*c*c > 0){
        //         ans1 += 2*m + 1; continue;
        //     }
        //     for(ll d=-m; d<=m; d++){
        //         if(27*d*d + 4*c*c*c > 0) ans1++;
        //     }
        // }
        // cout << ans1 << "\n";
        cout << ans << "\n"; return 0;
    }
    return 0;
}