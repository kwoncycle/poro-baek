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
    SegTree(int n_input, vector<segtreetype> &arr_input){
        n = n_input;
        segtree = vector<segtreetype>(4*n+10, 0);
        arr = vector<segtreetype>(n);
        for(int i=0; i<n; i++){
            arr[i] = arr_input[i];
        }
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        init(2*node, start, (start + end)/2);
        init(2*node + 1, (start + end)/2 + 1, end);
        segtree[node] = segtree[2*node] + segtree[2*node+1];
    }
    void update(int target, segtreetype val){
        arr[target] = val;
        update_segtree(1, 0, n-1, target, val);        
    }
    void update_segtree(int node, int start, int end, int target, int val) {
        if(target < start or end < target) return;
        if(start == end){
            segtree[node] += val;
            return;
        }

        update_segtree(2*node, start, (start+end)/2, target, val);
        update_segtree(2*node + 1, (start+end)/2 + 1, end, target, val);
        segtree[node] = segtree[2*node] + segtree[2*node+1];
    }
 
    segtreetype query(int node, int start, int end, int left, int right) {
        if(right < start or end < left) return 0;
        if(left <= start and end <= right) return segtree[node];

        ll q1 = query(2*node, start, (start + end)/2, left, right);
        ll q2 = query(2*node + 1, (start + end)/2 + 1, end, left, right);
        return q1 + q2;
    }
};
// USAGE: SegTree segtree(n, arr);


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m; cin >> n >> m;
    vector<ll> arr(n, 0);
    SegTree seg(n, arr);
    ll cnt = 0;
    vector<pll> input(m);
    for(int i=0; i<m; i++) cin >> input[i].X >> input[i].Y;
    sort(input.begin(), input.end());
    for(pll inp:input){
        ll a = inp.X, b = inp.Y;
        a--; b--;
        ll t =  seg.query(1, 0, n-1, b+1, n-1);
        cnt += seg.query(1, 0, n-1, b+1, n-1);
        seg.update(b, 1);
    }
    cout << cnt << "\n";
    return 0;
}