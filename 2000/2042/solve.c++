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



#define segtreetype long long
class SegTree
{
    int n;
    vector<segtreetype> segtree, arr;
 
public:
    SegTree(int n_input, vector<segtreetype>& arr_input){
        n = n_input;
        segtree = vector<segtreetype>(4*n+10, 0);
        arr = vector<segtreetype>(n);
        for(int i=0; i<n; i++) arr[i] = arr_input[i];
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        init(node*2, start, (start + end)/2);
        init(node*2 + 1, (start + end)/2 + 1, end);

        // CHANGE THIS AS WELL
        segtree[node] = segtree[node*2] + segtree[node*2 + 1];
    }
    void update(int target, segtreetype val){
        arr[target] = val;
        update_segtree(1, 0, n-1, target, val);
    }
    void update_segtree(int node, int start, int end, int target, segtreetype val) {
        if(target < start or end < target) return;
        if(start == end){
            segtree[node] = val;
            return;
        }

        update_segtree(2*node, start, (start + end)/2, target, val);
        update_segtree(2*node + 1, (start + end)/2 + 1, end, target, val);
        
        // CHANGE AS NEEDED
        segtree[node] = segtree[node*2] + segtree[node*2 + 1];
        return;
    }
 
    segtreetype query(int node, int start, int end, int left, int right) {
        if(right < start or end < left) return 0;
        if(left <= start and end <= right) return segtree[node];

        segtreetype q1 = query(node*2, start, (start + end)/2, left, right);
        segtreetype q2 = query(node*2 + 1, (start + end)/2 + 1, end, left, right);

        // CHANGE AS NEEDED
        return q1 + q2;
    }
};
// USAGE: SegTree segtree(n, arr);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m, k; cin >> n >> m >> k;
    m += k;
    vector<ll> v(n);
    for(int i=0; i<n; i++) cin >> v[i];

    SegTree seg(n, v);
    while(m--){
        ll a, b, c; cin >> a >> b >> c;
        b--;
        if(a == 2) c--;
        if(a == 1) seg.update(b, c);
        else{
            cout << seg.query(1, 0, n-1, b, c) << "\n";
        }
    }
    return 0;
}