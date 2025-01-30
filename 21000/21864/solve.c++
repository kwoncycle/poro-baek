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
using namespace std;
 
#define i128 __int128
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
i128 p = 1000000000000000031;
ll arr[3][1<<20+1] = {};
ll poww(ll x){
	ll v = 1;
    int i = 0;
    while(x){
        v *= arr[i][x&0b11111111111111111111];
	v %= p;
	i++;
        x>>=20;
    }
	return v;
}
// a^x (mod m)


int main(){
    arr[0][0] = 1;
    for(int i=1; i<(1<<20); i++){
        arr[0][i] = arr[0][i-1] * 42 % p;
    }
    arr[1][1] = arr[0][(1<<20)-1]*42%p;
    arr[1][0] = 1;
    for(int i=2; i<(1<<20); i++){
    	arr[1][i] = arr[1][i-1] * arr[1][1] % p;
    }
    arr[2][1] = arr[1][(1<<20)-1]*arr[1][1]%p;
    arr[2][0] = 1;
    for(int i=2; i<(1<<20); i++){
        arr[2][i] = arr[2][i-1] * arr[2][1] % p;
    }
    ll u = 836174947389522544ll;
    i128 a0 = 108600338365753046;
    int x; cin >> x;
    for(int i = 2000000; i > x; i--){
        a0 = poww(a0);
    }
    cout << (long long)a0 << "\n";
    return 0;
}