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

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using complex_t = complex<double>;

#define pdi pair<double, int>

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    vector<pair<pair<double, double>, double>> v(n);
    for(int i=0; i<n; i++){
        cin >> v[i].X.X >> v[i].X.Y >> v[i].Y;
    }
    vector<vector<pair<int, double>>> graph(n+1);
    for(int i=0; i<m; i++){
        int a, b; cin >> a >> b; a--; b--;
        double d = (double)2.0 * sqrt(sqrt((v[a].X.X - v[b].X.X)*(v[a].X.X - v[b].X.X) + (v[a].Y - v[b].Y)*(v[a].Y - v[b].Y) + (v[a].X.Y - v[b].X.Y)*(v[a].X.Y - v[b].X.Y)));
        graph[a].push_back({b, d});
        graph[b].push_back({a, d});
    }
    
    vector<double> dist(n, 1e100);
    dist[0] = 0;
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    pq.push({0, 0});
    while(!pq.empty()){
        pdi x = pq.top(); pq.pop();
        if(dist[x.Y] < x.X) continue;
        dist[x.Y] = x.X;
        for(auto y:graph[x.Y]){
            pq.push({y.Y + dist[x.Y], y.X});
        }
    }
    
    while(q--){
        int c; double t;
        cin >> c >> t;
        c--;
        if(dist[c] > t){
            cout << "impossible\n"; continue;
        }
        double T = dist[c];
        double b1 = t/T;
        double x = b1 - sqrt(b1*b1-1);
        cout << fixed << setprecision(12) << x*dist[c] << "\n";
    }
    
    return 0;
}