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

#define MOD 805299619
vector<ll> epow(2000005,1), epowinv(2000005, 1);

ll stringhash(vector<ll> &hashh, ll l, ll r){
    if(l > r) return 0;
    if(l == 0) return hashh[r];
    else{
        ll x = hashh[r] - hashh[l-1];
        x *= epowinv[l]; x %= MOD;
        if(x < 0) x += MOD;
        return x;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    for(int i=1; i<=2000001; i++){
        epow[i] = epow[i-1] * 138 % MOD;
    }
    epowinv[2000001] = modInverse(epow[2000001], MOD);
    for(int i=2000000; i>=0; i--){
        epowinv[i] = epowinv[i+1] * 138 % MOD;
    }
    if(epowinv[0] != 1) return 0;
    int N; cin >> N;
    vector<int> v[50], DP[50];
    vector<ll> hashh[50];
    string sv[50];
    for(int di=0; di<N; di++){
        string s; cin >> s; int n = s.size();
        sv[di] = s;
        n = 2*n+1;
        v[di] = vector<int>(n, 0), DP[di] = vector<int>(n, 0);
        for(int i=0; i<n/2; i++){
            v[di][2*i+1] = s[i]-'a' + 1;
        }
        int mx = 0, mxi = 0;
        for(int i=1; i<=n; i++){
            if(mx >= i){
                int index = mxi*2-i;
                if(index >= 0) DP[di][i] = min(DP[di][index], index - (mxi - DP[di][mxi]));
            }
            for(int j=DP[di][i]; j<=i; j++){
                if(i+j < n){
                    if(v[di][i+j] == v[di][i-j]) DP[di][i]=j;
                    else break;
                }
                else break;
            }
            if(mx <= DP[di][i] + i){
                mx = DP[di][i] + i; mxi = i;
            }
        }
        //n = s.size();
        hashh[di] = vector<ll>(n, 0);
        hashh[di][0] = v[di][0];
        ll e = 1;
        for(ll i=1; i<n; i++){
            e *= 138; e %= MOD;
            hashh[di][i] = (hashh[di][i-1] + e*(v[di][i]))%MOD;
        }
    }

    vector<vector<int>> isin(50, vector<int>(26, 0));
    for(int i=0; i<N; i++){
        for(char j:sv[i]) isin[i][j-'a'] = 1;
    }
    int truth = 0;
    for(int i=0; i<26; i++){
        int t = 1;
        for(int j=0; j<N; j++) if(isin[j][i] == 0) t = 0;
        if(t) truth = 1;
    }
    if(!truth){
        cout << "0\n"; return 0;
    }
    ll start = 0, end = 1000101, mx = 0;
    while(start + 1 < end){
        ll l1 = (start + end)/2; ll l = 2*l1;
        //if(l <= 5) cout << l << "\n";
        map<ll, ll> mp;
        for(int i=0; i<N; i++){
            int n = DP[i].size();
            if(l % 2 == 1){
                for(int j=1; j<n; j+=2){
                    if(DP[i][j] >= l - 1){
                        ll h = stringhash(hashh[i], j - l + 1, j + l - 1);
                        if(mp.find(h) == mp.end()) mp[h] = 0;
                        mp[h] |= (1ll << (ll)i);
                    }
                }
            }
            else{
                for(int j=0; j<n; j+=2){
                    if(DP[i][j] >= l - 1){
                        ll h = stringhash(hashh[i], j - l + 1, j + l - 1);
                        if(mp.find(h) == mp.end()) mp[h] = 0;
                        mp[h] |= (1ll << (ll)i);
                    }
                }
            }
        }
        int truth = 0;
        ll r = (1ll << N) - 1;
        for(auto it = mp.begin(); it != mp.end(); it++){
            if(it->second == r){
                truth = 1; break;
            }
        }
        if(truth) start = l1;
        else end = l1;
    }
    mx = max(2*start, mx);
    start = 1, end = 1000101;
    while(start + 1 < end){
        ll l1 = (start + end)/2; ll l = 2*l1 - 1;
        //cout << l << " ";
        //if(l <= 5) cout << l << "\n";
        map<ll, ll> mp;
        for(int i=0; i<N; i++){
            int n = DP[i].size();
            if(l % 2 == 1){
                for(int j=1; j<n; j+=2){
                    if(DP[i][j] >= l - 1){
                        ll h = stringhash(hashh[i], j - l + 1, j + l - 1);
                        if(mp.find(h) == mp.end()) mp[h] = 0;
                        mp[h] |= (1ll << (ll)i);
                    }
                }
            }
            else{
                for(int j=0; j<n; j+=2){
                    if(DP[i][j] >= l - 1){
                        ll h = stringhash(hashh[i], j - l + 1, j + l - 1);
                        if(mp.find(h) == mp.end()) mp[h] = 0;
                        mp[h] |= (1ll << (ll)i);
                    }
                }
            }
        }
        int truth = 0;
        ll r = (1ll << N) - 1;
        for(auto it = mp.begin(); it != mp.end(); it++){
            if(it->second == r){
                truth = 1; break;
            }
        }
        if(truth) start = l1;
        else end = l1;
    }
    mx = max(2*start-1, mx);
    cout << mx << "\n";
    return 0;
}