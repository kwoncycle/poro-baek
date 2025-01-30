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

ll poww(ll a, ll e, ll MOD){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return ans;
}


int isprime(ll n){
	if(n<=1) return 1;
	ll primes[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
	for(int i=0; i<12; i++){
		if(n==primes[i]) return 1;
		else if(n%primes[i]==0) return 0;
	}
	ll t = n-1;
	ll s = 0;
	while(t%2==0){
		t>>=1;
		s++;
	}
	for(int i=0; i<12; i++){
		ll y = poww(primes[i], t, n);
		if(y==1 or y==n-1) continue;
		int trueM = 0;
		for(int j=0; j<s; j++){
			if(y == n-1){
				trueM = 1;
				break;
			}
			y = poww(y, 2, n);
		}
		if(trueM) continue;
		return 0;
	}
	return 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<int> prime(1010010, 0), primes;
    for(int i=2; i<=1010000; i++){
        if(prime[i] == 0){
            prime[i] = 1;
            primes.push_back(i);
            for(int j=i*2; j<=1010000; j+=i) prime[j] = 1;
        }
    }

    for(int tc=1; true; tc++){
        ll a, b, l, u;
        cin >> a;
        if(a == 0) break;
        cin >> b >> l >> u;

        cout << "Case " << tc << ": ";

        //if(b < 2){
        //    if(a == 1 and l < 2) l = 2;
        //    if(a > 1 and l < 1) l = 1;
        //    if(l > u){
        //        cout << "0\n"; continue;
        //    }
        //}
        /*
        if(tc > 100){
            vector<vector<int>> v(3);
            for(int j=123; j<=12398; j++) v[j].push_back(1557);
            break;
        }*/
        u -= l;
        b += a*l;
        l = 0;

        if(__gcd(a, b) != 1){
            int cnt = 0;
            for(int i=0; i<=min(1ll, u); i++){
                if(isprime(a*i+b)) cnt++;
            }
            cout << cnt << "\n";
            continue;
        }

        vector<int> check(u+1, 1);
        ll x = a*u + b;
        for(ll p:primes){
            if(a % p == 0) continue;
            ll o = (ll)(p - b%p) * poww(a, p-2, p) % p;
            if(p*p > x + 8) break;
            if(o == 0 and b == 0) o += p;
            if(a * o + b == p) o += p;
            for(ll j=o; j<=u; j+=p){
                check[j] = 0;
            }
        }
        int cnt = 0;
        for(ll i=0; i<=u; i++){
            if(a*i+b == 0 or a*i+b == 1) cnt--;
            if(check[i]){
                cnt++;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}