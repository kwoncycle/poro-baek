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
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n
 
ll poww(ll a,ll x,ll m){
	if(x==1) return a%m;
	if(x==0) return 1;
	ll v = poww(a, x/2, m);
	v = v*v%m;
	if(x%2) v = v*a%m;
	return v;
}
// a^x (mod m)
 
ll modInverse(ll A, ll M){
    ll m0 = M;
    ll y = 0, x = 1;
    if (M == 1)
        return 0;
    while (A > 1) {
        ll q = A / M;
        ll t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

#define MOD 1000000007
vector<ll> fct(200005, 1), fctinv(200005, 1);


ll nCr(ll n, ll r){
    if(r < 0) return 0;
    if(n < 0) return 0;
    ll u = fct[n];
    u *= fctinv[r]; u %= MOD;
    u *= fctinv[n-r]; u %= MOD;
    return u;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    for(ll i=1; i<=200000; i++) fct[i] = fct[i-1] * i % 1000000007;
    fctinv[200000] = modInverse(fct[200000], MOD);
    for(ll i=200000; i>=1; i--) fctinv[i-1] = fctinv[i] * i % MOD;
    string s1, s2, s3; cin >> s1 >> s2 >> s3;
    vector<int> cnt(4, 0), cntable(4, 0);
    int n = s1.size();
    for(int i=0; i<n; i++){
        int a = s1[i]-'0', b = s2[i]-'0', c = s3[i]-'0';
        int d = 0;
        if((a+b)%10 != c and (a+b+1)%10 != c) {
            cout << 0 << "\n";
            return 0;
        }
        if((a+b+1)%10 == c) d += 1;
        if(a+b+d >= 10) d += 2;
        cnt[d]++;
        if(a !=0 and b!=0 and c!=0) cntable[d]++;
    }

    if(cnt[1] != cnt[2]){
        cout << 0 << "\n";
        return 0;
    }
    ll ans = 0;
    ll c1 = cnt[1], n0 = cnt[0], n1 = cnt[3];
    // 10 end
    if(c1){
        ll u1 = nCr(c1+n0-1, c1-1);
        ll u2 = nCr(c1+n1-1, c1-1);
        u1 *= u2; u1 %= MOD;
        u1 *= cntable[1]; u1 %= MOD;
        u1 *= fct[cnt[0]]; u1 %= MOD;
        u1 *= fct[cnt[1]]; u1 %= MOD;
        if(cnt[2]){
            u1 *= fct[cnt[2] - 1]; u1 %= MOD;
        }
        else u1 *= 0;
        u1 *= fct[cnt[3]]; u1 %= MOD;
        ans += u1;
    }
    //cout << ans << " ";
    // 00 end
    //cout << c1 << " " << n0 << ' ' << n1 << "\n";
    ll u1 = nCr(c1+n0-1, c1);
    ll u2 = nCr(c1+n1-1, c1-1);
    if(n1) {
        u1 *= u2; u1 %= MOD;
    }
    u1 *= cntable[0]; u1 %= MOD;
    //cout << u1 << " ";
    if(cnt[0]){
        u1 *= fct[cnt[0] - 1]; u1 %= MOD;
    }
    else u1 *= 0;
    u1 *= fct[cnt[1]]; u1 %= MOD;
    u1 *= fct[cnt[2]]; u1 %= MOD;
    u1 *= fct[cnt[3]]; u1 %= MOD;
    ans += u1;
    ans %= MOD;
    cout << ans << "\n";
    return 0;
}