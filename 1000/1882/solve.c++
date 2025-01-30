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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    vector<ll> mb(40001, 1);
    vector<ll> isprime(40001, 1);
    vector<vector<ll>> primes(40001);
    
    for(ll i=2; i<=40000; i++){
        if(isprime[i]){
            for(ll j=i+i; j<=40000; j+=i){ 
                isprime[j] = 0;
            }
            for(ll j=i; j<=40000; j+=i){
                mb[j] *= -1;
            }
            for(ll j=i*i; j<=40000; j+=i*i){
                mb[j] = 0;
            }
        }
    }
    for(ll i=1; i<=40000; i++){
        for(ll j=i; j<=40000; j+=i){
            if(mb[j/i]) primes[j].push_back(i);
        }
    }

    ll n, k; cin >> n >> k;
    double o1 = 0, o2 = 1;
    int cntt = 0;
    while(o1 + 0.000000000001 < o2){
        double md = (o1 + o2)/2.0;
        cntt++;
        ll cnt = 0;
        for(ll i=1; i<=n; i++){
            for(ll d:primes[i]){
                cnt += (int)(md * d) * mb[i/d];
            }
        }
        if(cnt < k){
            o1 = md;
        }
        else o2 = md;
    }

    //cout << o2 << "\n";

    for(int i=1; i<=n; i++){
        int i1 = int(o2*i);
        //cout << i1 << "\n";
        for(int j=max(0,i1-1); j<=min(i,i1+1); j++){
            if(__gcd(i, j) == 1){
                if(abs(double(j)/(double)i - o2) < 0.0000000001){
                    cout << j << " " << i << "\n"; return 0;
                }
            }
        }
    }

    return 0;
}