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

/*
이왜DP?
DP맞네

*/

vector<int> l2t3(ll x){
    vector<int> v(10);
    for(int i=0; i<10; i++){
        v[i] = x%3; x/=3;
    }
    return v;
}


int n2len(ll n){
    if(n == 1000000000000000000ll) return 19;
    ll length = 1, r = 1;
    while(r*10 <= n){
        r *= 10; length++;
    }
    return length;
}


vector<int> n2v(ll n){
    int r = min(19, n2len(n));
    vector<int> v(r);
    for(int i=0; i<r; i++){
        v[r-1-i] = n%10; n/=10;
    }
    return v;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, k; cin >> n >> k;
    ll length = n2len(n);

    if(length < k){
        cout << "10";
        for(int i=2; i<k; i++) cout << i;
        cout << "\n"; return 0;
    }

    while(true){
        //cout << n << " ";
        int r = min(19, n2len(n));
        int o = -1;
        vector<int> v = n2v(n); 
        for(int i=r; i>=1; i--){
            vector<int> chk(10, 0);
            int cnt = 0;
            for(int j=0; j<i; j++) chk[v[j]] = 1;
            for(int j=0; j<10; j++) cnt += chk[j];
            if(cnt == k) {
                o = i; break;
            }
        }
        if(o >= 0){
            vector<int> chk(10, 0);
            for(int j=0; j<o; j++) chk[v[j]] = 1;
            if(o == r){
                cout << n << "\n"; return 0;
            }
            int flag = 0;
            for(int i=v[o]+1; i<10; i++){
                if(chk[i]){
                    flag = 1;
                    ll t = 1;
                    for(int j=o+2; j<=r; j++) t *= 10;
                    n /= t; n++; n *= t;
                    break;
                }
            }
            if(flag) continue;
            else{
                ll t = 1;
                for(int j=o+1; j<=r; j++) t *= 10;
                n /= t; n++; n *= t;
            }
        }
        else{
            for(int i=r-2; i>=-1; i--){
                if(v[i+1] == 9) continue;
                v[i+1]++;
                for(int j=i+2; j<r; j++) v[j] = 0;
                vector<int> chk(10, 0);
                for(int j=0; j<r; j++) chk[v[j]] += 1;
                int cnt = 0;
                for(int j=0; j<10; j++) if(chk[j]) cnt++;
                if(cnt == k){
                    for(int i:v) cout << i; cout << "\n"; return 0;
                }

                chk = vector<int>(10, 0);
                for(int j=0; j<=i+1; j++) chk[v[j]] += 1;
                cnt = 0;
                for(int j=0; j<10; j++) if(chk[j]) cnt++;
                if(cnt + r-i-2 >= k){
                    vector<int> tmp;
                    for(int j=0; j<10; j++) if(!chk[j]) tmp.push_back(j);
                    for(int j=0; j<k-cnt; j++){
                        chk[tmp[j]] = 1;
                    }
                    for(int j=0; j<10; j++){
                        if(chk[j]){
                            for(int t=i+2; t<r; t++) v[t] = j; break;
                        }
                    }
                    for(int j=0; j<k-cnt; j++){
                        v[r-(k-cnt)+j] = tmp[j]; chk[tmp[j]] = 1;
                    }
                    for(int i:v) cout << i; cout << "\n"; return 0;
                }
                chk = vector<int>(10, 0);
                for(int j=0; j<=i; j++) chk[v[j]] += 1;
                while(v[i+1] < 10 and chk[v[i+1]]) v[i+1]++;
                if(v[i+1] == 10){
                    v[i+1] = 9; continue;
                }
                chk = vector<int>(10, 0);
                for(int j=0; j<=i+1; j++) chk[v[j]] += 1;
                cnt = 0;
                for(int j=0; j<10; j++) if(chk[j]) cnt++;
                if(cnt + r-i-2 >= k){
                    vector<int> tmp;
                    for(int j=0; j<10; j++) if(!chk[j]) tmp.push_back(j);
                    for(int j=0; j<10; j++){
                        if(chk[j]){
                            for(int t=i+2; t<r; t++) v[t] = j; break;
                        }
                    }
                    for(int j=0; j<k-cnt; j++){
                        v[r-(k-cnt)+j] = tmp[j]; chk[tmp[j]] = 1;
                    }
                    for(int i:v) cout << i; cout << "\n"; return 0;
                }
            }
            n = 1;
            for(int i=0; i<r; i++) n *= 10;
        }
    }

    
    return 0;
}