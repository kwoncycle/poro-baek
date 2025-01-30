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
 
#define ll __int128
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

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using complex_t = complex<double>;
#define ll __int128
ll pair2int(ll x, ll y, ll m, ll n){
    return x*n+y;
}

pll int2pair(ll XX, ll m, ll n){
    return {XX/n, XX%n};
}
#define DEBUG 0
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    while(true){
        long long a1, m1, b1, n1; cin >> a1 >> m1 >> b1 >> n1;
        ll a=a1, m=m1, b=b1, n=n1;
        if(!(a|b|m|n)) break;
        vector<vector<ll>> v((int)m*n+1, vector<ll>((int)m*n, 0));
        for(ll i=0; i<=m*n; i++){
            if(i == 0) v[i][0]++;
            else{
                for(ll j=0; j<=i; j++){
                    //am j bn i-j
                    ll j1 = j, j2 = i-j;
                    ll index = pair2int(j1 % m, j2 % n, m, n);
                    ll t = 1;
                    for(ll x=i; x>i-j; x--) t *= x;
                    for(ll x=1; x<=j; x++) t /= x;
                    for(ll x=0; x<j1/m; x++) t *= a;
                    for(ll x=0; x<j2/n; x++) t *= b;
                    v[i][index] += t;
                }
            }
        }
        if(DEBUG)
        for(ll i=0; i<=n*m; i++){
            for(ll j=0; j<n*m; j++) cout << (long long)v[i][j] << " "; cout << "\n";
        }

        for(ll i=0; i<m*n; i++){
            if(v[i][i] == 0){
                for(ll j=i+1; j<m*n; j++){
                    if(v[i][j]){
                        for(ll k=0; k<=m*n; k++){
                            v[k][i] += v[k][j];
                        }
                        break;
                    }
                }
            }
            for(ll j=i+1; j<m*n; j++){
                ll t1 = v[i][i], t2 = v[i][j];
                ll x = t1 / __gcd(t1, t2);
                for(ll k=0; k<=m*n; k++){
                    v[k][j] *= x;
                    v[k][j] -= (t2/__gcd(t1, t2))*v[k][i];
                }
            }
            for(ll j=i; j<m*n; j++){
                ll G = v[0][j];
                for(ll k=1; k<=m*n; k++){
                    G = __gcd(G, v[k][j]);
                }
                for(ll k=0; k<=m*n; k++) v[k][j] /= G;
            }
        }
        if(DEBUG)
        for(ll i=0; i<=n*m; i++){
            for(ll j=0; j<n*m; j++) cout << (long long)v[i][j] << " "; cout << "\n";
        }

        vector<ll> ans((int)n*m+1, 0);
        for(ll i=n*m-1; i>=0; i--){
            for(ll j=i+1; j<n*m; j++){
                v[n*m][i] -= v[j][i]*ans[j];
                v[j][i] = 0;
            }
            if(DEBUG)
            if(v[n*m][i] % v[i][i] != 0){
                cout << "GAL\n"; return 0;
            }
            ans[i] = v[n*m][i] / v[i][i];
        }
        if(DEBUG)
        for(ll i=0; i<=n*m; i++){
            for(ll j=0; j<n*m; j++) cout << (long long)v[i][j] << " "; cout << "\n";
        }

        ans[n*m] = -1;
        for(ll i=n*m; i>=0; i--) cout << (long long)-ans[i] << " "; cout << "\n";
        v.clear();
        ans.clear();
    }
    return 0;
}