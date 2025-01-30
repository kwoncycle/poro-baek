// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
//#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define i128 __int128
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using complex_t = complex<double>;

ll mul(ll a, ll b, ll n){
	ll x = (i128)a*b%n;
	return x;
}

ll pow(ll p, ll t, ll n){
	if(t==0) return 1;
	ll x = 1;
	ll y = p%n;
	while(t){
		if(t&1) x = mul(x, y, n);
		y = mul(y, y, n);
		t >>= 1;
	}
	return x;
}

int isprime(ll n){
	if(n==1) return 1;
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
		ll y = pow(primes[i], t, n);
		if(y==1 or y==n-1) continue;
		int trueM = 0;
		for(int j=0; j<s; j++){
			if(y == n-1){
				trueM = 1;
				break;
			}
			y = pow(y, 2, n);
		}
		if(trueM) continue;
		return 0;
	}
	return 1;
}
ll gcd(ll a, ll b){
	if(a<b){
		ll c = a;
		a = b;
		b = c;
	}
	while(b){
		ll r = a%b;
		a = b;
		b = r;
	}
	return a;
}
ll pollard_rho(ll n){
	if(n%2==0) return 2;
	ll x = rand()%(n-2)+2;
	ll y = x;
	ll c = rand()%(n-1)+1;
	ll d = 1;
	while(d==1){
		x = (i128)(mul(x,x,n)+c)%n;
		y = (i128)(mul(y,y,n)+c)%n;
		y = (i128)(mul(y,y,n)+c)%n;
		if(x>y) d = gcd(x-y, n);
		else d = gcd(y-x, n);
	}
	if(d!=n) return d;
	else return pollard_rho(n);
}
vector<ll> givemeFactor(ll n){
	vector<ll> s, t;
	s.push_back(n);
	while(true){
		t.clear();
		for(ll p:s){
			if(isprime(p)){
				t.push_back(p); continue;
			}
			ll d = pollard_rho(p);
			t.push_back(d);
			t.push_back(p/d);
		}
		if(s.size()==t.size()) break;
		s.clear();
		for(ll p:t) s.push_back(p);
	}
	sort(t.begin(), t.end());
    vector<ll> tt;
    tt.push_back(t[0]);
    for(int i=1; i<(int)t.size(); i++){
        if(t[i] != t[i-1]) tt.push_back(t[i]);
    }
	return tt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tt; cin >> tt;
    while(tt--){
        ll n; cin >> n;
        if(n == 1){
            cout << "1\n"; continue;
        }
        vector<ll> prime = givemeFactor(n);
        //prime.erase(unique(prime.begin(),prime.end()),prime.end());
        vector<ll> vp(prime.size(), 0);
        ll nn = n;
        for(int i=0; i<(int)prime.size(); i++){
            while(nn % prime[i] == 0){
                nn /= prime[i];
                vp[i]++;
            }
        }
        ll cnt = 0;
        vector<ll> cntr((int)prime.size()+1, 0);
        ll u = 1;
        for(ll i:vp) u *= (i+1);
        while(u--){
            cntr[0]++;
            for(int i=0; i<(int)prime.size(); i++){
                if(cntr[i] > vp[i]){
                    cntr[i] = 0;
                    cntr[i+1]++;
                }
            }
            ll x = 1;
            for(int i=0; i<(int)prime.size(); i++){
                for(ll j=0; j<cntr[i]; j++) x *= prime[i];
            }
            x++;

            vector<ll> vx = givemeFactor(x);
            //vx.erase(unique(vx.begin(),vx.end()),vx.end());
            for(ll i:vx){
                x /= i;
                x *= i-1;
            }
            cnt += x;
        }
        cout << cnt << "\n";
    }
    return 0;
}