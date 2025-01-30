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

#include <quadmath.h>
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

void fft(vector<complex_t>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
    static vector<complex_t> rt(2, 1); // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i=k;i<k+k;i++) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vector<int> rev(n);
    for (int i=0;i<n;i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for (int i=0;i<n;i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2){
        for (int i = 0; i < n; i += 2 * k) for (int j=0;j<k;j++) {
            // complex_t z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
            auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];                /// exclude-line
            complex_t z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
    }
}

template <typename T>vector<T> conv(const vector<T>& a, const vector<T>& b) {
    if (a.empty() || b.empty()) return {};
    vector<T> res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<complex_t> in(n), out(n);
    copy(all(a), begin(in));
    for (int i=0;i<sz(b);i++) in[i].imag(b[i]);
    fft(in);
    for (complex_t& x: in) x *= x;
    for (int i=0;i<n;i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for (int i=0;i<sz(res);i++){
        res[i] = static_cast<T>(imag(out[i]) / (4 * n) + (is_integral_v<T> ? (imag(out[i]) > 0 ? 0.5 : -0.5) : 0));
    }
    return res;
}



typedef struct p3{
	int a; int b; int c;
}p3;

bool cmp3(p3 p, p3 q){
	if(p.a==q.a){
		if(p.b == q.b){
			return p.c < q.c;
		}
		return p.b < q.b;
	}
	return p.a < q.a;
}
 
void make_segtree(int node, int start, int end, vector<int> &segtree, vector<int> &arr){
	if(start==end){
		segtree[node] = arr[start];
		return;
	}
	int mid = (start+end)/2;
	make_segtree(node*2, start, mid, segtree, arr);
	make_segtree(node*2+1, mid+1, end, segtree, arr);
	segtree[node] = segtree[node*2] + segtree[node*2 + 1];
	return;
}
 
void update(int node, int start, int end, int x, int val, vector<int> &segtree, vector<int> &arr){
	if(x<start or end<x) return;
	if(start == end){
		segtree[node] = val; return;
	}
	int mid = (start+end)/2;
	update(2*node,start,mid,x,val,segtree,arr);
	update(2*node+1,mid+1,end,x,val,segtree,arr);
	segtree[node] = segtree[node*2] + segtree[node*2+1];
}
 
int query(int node, int start, int end, int l, int r, vector<int> &segtree, vector<int> &arr){
	if(r<start or end<l) return 0;
	if(l<=start and end<=r) return segtree[node];
	int mid = (start+end)/2;
	return query(node*2, start, mid, l, r, segtree, arr) + query(node*2+1, mid+1, end, l, r, segtree, arr);
}
 
class djs
{
    int n;
    vector<int> par;
 
public:
    djs(int n) : n(n) {
        par.resize(n);
        for(int i=0; i<n; i++) par[i] = i;
    }
 
    int find(int v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
 
    bool Union(int x, int y) {
        int px = find(x);
        int py = find(y);
 
        if(px == py) return false;
 
        par[px] = py;
        return true;
    }
};
// Usage: djs DJS(n)
 
ll pow(ll a,ll x,ll m){
	if(x==1) return a%m;
	if(x==0) return 1;
	ll v = pow(a, x/2, m);
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
 
void BFS(int r, vector<int> &visited, vector<int> &dist, vector<int> &under, vector<vector<pii>> &GRAPH){
	visited[r] = 1;
	int sm = 1;
	for(pii p: GRAPH[r]){
		if(visited[p.first]) continue;
		dist[p.first] = dist[r] + p.second;
		BFS(p.first, visited, dist, under, GRAPH);
		sm += under[p.first];
	}	
}

vector<pll> point;

pll dif(pll p2, pll p1){
    return {p1.X - p2.X, p1.Y - p2.Y};
}

bool cmp(pii p1, pii p2){
    int x1 = p1.X, x2 = p2.X, y1 = p1.Y;
    pll xx = dif(point[x1], point[y1]);
    ll a = xx.X, b = xx.Y;
    if(point[x1].X*a + point[x1].Y*b == point[x2].X*a + point[x2].Y*b){
        return point[x1].X*b - point[x1].Y*a < point[x2].X*b - point[x2].Y*a;
    }
    return point[x1].X*a + point[x1].Y*b < point[x2].X*a + point[x2].Y*b;
}

#define DEBUG 0

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    point = vector<pll>(n);
    for(int i=0; i<n; i++) cin >> point[i].X >> point[i].Y;
    map<pair<pll, int>, vector<pii>> mp;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            pll p1 = point[i], p2 = point[j];
            int swaped = 0;
            if(p1.X > p2.X){
                pll tmp = p1; p1 = p2; p2 = tmp; swaped = 1;
            }
            if(p1.X == p2.X){
                if(p1.Y > p2.Y){
                    pll tmp = p1; p1 = p2; p2 = tmp; swaped = 1;
                }
            }
            int ii = i, jj = j;
            if(swaped){
                ii = j; jj = i;
            }
            pll xx = dif(p1, p2);
            ll a = xx.X, b = xx.Y;

            if(mp.find({xx, p1.X*a + p1.Y*b}) == mp.end()) mp[{xx, p1.X*a + p1.Y*b}] = vector<pii>(1, {ii, jj});
            else mp[{xx, p1.X*a + p1.Y*b}].push_back({ii, jj});
        }
    }

    __int128 mxL = 0;
    for(auto i=mp.begin(); i != mp.end(); ++i){
        sort(mp[i->X].begin(), mp[i->X].end(), cmp);
        if(mp[i->X].size() == 1) continue;
        pii p1 = mp[i->X][0], p2 = *mp[i->X].rbegin();

        pll d1 = point[p1.X], d2 = point[p1.Y], d3 = point[p2.X], d4 = point[p2.Y];
        __int128 L1 = (__int128)((d1.X-d2.X)*(d1.X-d2.X)+(d1.Y-d2.Y)*(d1.Y-d2.Y));
        __int128 L2 = (__int128)((d1.X-d3.X)*(d1.X-d3.X)+(d1.Y-d3.Y)*(d1.Y-d3.Y));
        __int128 LL = L1 * L2;
        mxL = max(mxL, LL);
    }

    if((ll)mxL == 0){
        cout << 0 << "\n"; return 0;
    }

    ll ans = 1;
    while((__int128)ans * (__int128)ans * (__int128)4 < mxL){
        ans *= 2ll;
    }
    
    ll tp = ans;
    while((__int128)ans * (__int128)ans < mxL){
        if( (__int128)(ans + tp)*(__int128)(ans + tp) <= mxL) ans += tp;
        tp /= 2ll;
        if(tp == 0) break;
    }

    cout << ans << "\n"; // sqrt 해야함
    return 0;
}