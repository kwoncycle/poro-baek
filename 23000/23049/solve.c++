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
 
#define ll long long
#define pll pair<ll,ll>
#define X first
#define Y second

int main(){
    ll tt; cin >> tt;
    while(tt--){
        cout << "? 1 1" << endl;
        ll start; cin >> start;
        ll S = 500;
        map<ll,ll> mp;
        pll ans = {-1, -1};
        for(ll i=1; i<=S; i++){
            cout << "? " << start << " " << i*i << endl;
            ll l; cin >> l;
            if(mp.find(l) != mp.end()){
                ans = {i*i, mp[l]}; break;
            }
            mp[l] = i*i;
        }
        if(ans.X != -1) goto endgame;
        for(ll i=1; i<=S; i++){
            ll x = 1000000 + S - i*S*2;
            x = x*x;
            cout << "? " << start << " " << x << endl;
            ll t; cin >> t;
            if(mp.find(t) != mp.end()){
                ans = {x, mp[t]}; break;
            }
            if(t == start){
                ans = {0, x}; break;
            }
        }
        endgame:
        ll r = abs(ans.X - ans.Y);
        vector<pll> primes;
        ll o = 1;
        for(ll i=2; i<=1000000; i++){
            if(r%i == 0){
                primes.push_back({i,0});
                int t = primes.size() - 1;
                while(r%i == 0) {
                    r /= i; o *= i;
                    primes[t].Y++;
                }
            }
        }
        int t = primes.size();
        for(int i=0; i<t; i++){
            for(int j=0; j<primes[i].Y; j++){
                o /= primes[i].X;
                cout << "? " << start << " " << o << endl;
                ll g; cin >> g;
                if(g == start) continue;
                else{
                    o *= primes[i].X; break;
                }
            }
        }
        cout << "! " << o << endl;
        cin >> o;        
    }
    return 0;
}