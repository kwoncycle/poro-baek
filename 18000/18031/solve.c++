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
 
void make_segtree_max(ll node, ll start, ll end, vector<pll> &segtree, vector<pll> &arr){
	if(start==end){
		segtree[node] = arr[start];
		return;
	}
	ll mid = (start+end)/2;
	make_segtree_max(node*2, start, mid, segtree, arr);
	make_segtree_max(node*2+1, mid+1, end, segtree, arr);
	segtree[node] = max(segtree[node*2], segtree[node*2 + 1]);
	return;
}
 
pll querymax(ll node, ll start, ll end, ll l, ll r, vector<pll> &segtree, vector<pll> &arr){
	if(r<start or end<l) return {-99999999999999999ll, 0};
	if(l<=start and end<=r) return segtree[node];
	ll mid = (start+end)/2;
	return max(querymax(node*2, start, mid, l, r, segtree, arr), querymax(node*2+1, mid+1, end, l, r, segtree, arr));
}

void make_segtree_min(ll node, ll start, ll end, vector<pll> &segtree, vector<pll> &arr){
	if(start==end){
		segtree[node] = arr[start];
		return;
	}
	ll mid = (start+end)/2;
	make_segtree_min(node*2, start, mid, segtree, arr);
	make_segtree_min(node*2+1, mid+1, end, segtree, arr);
	segtree[node] = min(segtree[node*2], segtree[node*2 + 1]);
	return;
}
 
pll querymin(ll node, ll start, ll end, ll l, ll r, vector<pll> &segtree, vector<pll> &arr){
	if(r<start or end<l) return {99999999999999999ll, 0};
	if(l<=start and end<=r) return segtree[node];
	ll mid = (start+end)/2;
	return min(querymin(node*2, start, mid, l, r, segtree, arr), querymin(node*2+1, mid+1, end, l, r, segtree, arr));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll n, l, u; cin >> n >> l >> u;
    vector<ll> v(n);
    for(ll i=0; i<n; i++) cin >> v[i];
    vector<ll> next_target(2*n+2, 99999999999999999ll);
    set<pll> s1, s2;
    ll sm = 0;
    for(ll i=0; i<=n; i++){
        if(!s1.empty()){
            while(!s1.empty() and sm <= (*s1.rbegin()).X){
                pll r = *s1.rbegin(); ll y = r.Y;
                next_target[y] = min(next_target[y], 2*i);
                s1.erase(s1.find(r));
            }
        }
        if(!s2.empty()){
            while(!s2.empty() and sm >= (*s2.begin()).X){
                pll r = *s2.begin(); ll y = r.Y;
                next_target[y] = min(next_target[y], 2*i+1);
                s2.erase(s2.find(r));
            }
        }
        if(i == n) break;
        // down start: 0
        if(v[i] >= 0){
            s1.insert({sm, 2*i}); // lower than s1: (s1 >= sm): out
            s2.insert({sm+u-l, 2*i}); // upper than s2: out
        }

        if(v[i] <= 0){
            s2.insert({sm, 2*i+1});
            s1.insert({sm-u+l, 2*i+1});
        }
        sm += v[i];
    }

    for(ll i=0; i<=n-1; i++){
        if(v[i] >= 0) next_target[2*i+1] = 2*i+3;
        if(v[i] <= 0) next_target[2*i] = 2*i+2;
    }

    //for(int i=0; i<2*n+2; i++) cout << next_target[i]<< " "; cout << "\n";
    vector<vector<ll>> sparse(2*n+2, vector<ll>(22, 99999999999999999ll));
    for(ll i=0; i<2*n+2; i++) sparse[i][0] = next_target[i];
    for(ll j=1; j<22; j++){
        for(ll i=0; i<2*n+2; i++){
            if(sparse[i][j-1] != 99999999999999999ll) sparse[i][j] = sparse[sparse[i][j-1]][j-1];
        }
    }
    vector<pll> loc(n+1, {0, 0}), segtreemax(4*n+9), segtreemin(4*n+9);
    for(ll i=0; i<n; i++) loc[i+1] = {loc[i].X + v[i], i};
    make_segtree_max(1,0,n,segtreemax,loc);
    make_segtree_min(1,0,n,segtreemin,loc);

    ll qq; cin >> qq;
    while(qq--){
        ll b, e, x; cin >> b >> e >> x; b--; e--;
        pll mx = querymax(1,0,n,b+1,e+1,segtreemax,loc);
        pll mn = querymin(1,0,n,b+1,e+1,segtreemin,loc);
        if((mx.X - loc[b].X + x <= u) and (mn.X - loc[b].X + x >= l)){
            //cout << "hi0\n";
            cout << loc[e+1].X - loc[b].X + x << "\n"; continue;
        }
        ll st;
        if(mx.X - loc[b].X + x >= u){
            ll y = mx.Y;
            // y+1, top start 
            st = 2*(y+1)+1;
        }
        else if(mn.X - loc[b].X + x <= l){
            ll y = mn.Y;
            // y+1, down start
            st = 2*(y+1);
        }
        ll ans;
        while(true){
            ll index = 0;
            //cout << st/2 << " " << st%2 << " " << sparse[st][index] << "-> ";
            
            while(sparse[st][index] != 99999999999999999ll and sparse[st][index]/2 <= e) index++;
            index--;
            if(index < 0){
                //cout << st << " " << e << "\n";
                if(st % 2 == 0){
                    ans = loc[e+1].X - loc[st/2].X + l; 
                    //cout << "hi1\n";
                    break;
                }
                else{
                    ans = loc[e+1].X - loc[st/2].X + u; 
                    //cout << "hi2\n";
                    break;
                }
            }
            st = sparse[st][index];
        }
        if(ans < l) ans = l;
        if(ans > u) ans = u;
        cout << ans << "\n";
        if(false){
            cout << n << ' ' << l << " " << u << "\n";
            cout << b << " " << e << " " << x << "\n";
            for(ll i=b; i<=e; i++){
                cout << v[i] << " ";
                x += v[i]; if(x <= l) x=l; if(x >= u) x=u;
            }
            cout << "\nans: " << x << "\n";
        }
    }

    return 0;
}