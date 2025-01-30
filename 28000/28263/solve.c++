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
 
ll poww(ll a,ll x,ll m){
	if(x==1) return a%m;
	if(x==0) return 1;
	ll v = poww(a, x/2, m);
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
ll arr[93] = {10062361, 10187101, 10248701, 10375751, 10395001, 10672201, 10914751, 10956793, 11068597, 11620841, 11646251, 12224521, 12298441, 12577951, 12806641, 12913363, 13230001, 13582801, 14148751, 14261941, 14553001, 14822501, 15373051, 15592501, 15812281, 16170001, 16435189, 16770601, 17151751, 17431261, 17968501, 18007501, 18447661, 18676351, 19015921, 19209961, 19448101, 19602001, 20374201, 21829501, 24012451, 24596881, 24652783, 28523881, 28586251, 30561301, 32016601, 32609501, 32942251, 33205789, 33541201, 33617431, 36522641, 38348773, 38419921, 38740087, 40020751, 40994801, 41087971, 43044541, 43124401, 43578151, 44921251, 46957681, 47436841, 48024901, 48914251, 49005001, 50311801, 52707601, 55342981, 58697101, 59424751, 62254501, 62370001, 64566811, 66411577, 67234861, 69457501, 70436521, 71874001, 75467701, 76865251, 77480173, 78440671, 80349809, 81523751, 84892501, 85571641, 87846001, 88045651, 96049801, 98010001};

ll MOD = 1;
map<ll, ll> mp;

ll cnt = 0;
vector<ll> indexx(7);
void JG(int r, int id, int mx, int IM, ll IM1){
    //cout << r << " " << id << "\n";
    if(cnt >= IM1) return;
    if(id > mx){
        __int128 a = 1;
        ll u = 0;
        for(int i=1; i<=mx; i++){
            a *= arr[indexx[i]]; a %= MOD;
            u *= 100;
            u += indexx[i];
            //cout << (long long)indexx[i] << " ";
        }
        //cout << "\n";
        ll a1 = (ll)a;
        mp[a1] = u;
        //cout << (long long)a1 << " " << (long long)u << "\n";
        cnt++;
        return;
    }
    indexx[id] = r;
    for(int i=r+1; i<IM; i++){
        JG(i, id+1, mx, IM, IM1);
        if(id + 1 > mx) break;
    }
    indexx[id] = 0;
    return;
}

void JG1(int r, int id, int mx, int IM, ll IM1){
    if(cnt >= IM1) return;
    if(id > mx){
        __int128 a = 1;
        ll u = 0;
        for(int i=1; i<=mx; i++){
            a *= arr[indexx[i]]; a %= MOD;
            u *= 100;
            u += indexx[i];
        }
        a = (ll)a;
        a = modInverse(a, MOD);
        long long a1 = a;
        //cout << a << " " << u << "\n";
        if(mp.find(a) != mp.end()){
            cout << (long long)mp[a] << " " << (long long)u << "\n";
            cnt = 10000000ll;
            return;
        }
        return;
    }
    indexx[id] = r;
    for(int i=r+1; i<93; i++){
        JG1(i, id+1, mx, IM, IM1);
        if(id + 1 > mx) break;
    }
    indexx[id] = 0;
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    
    for(ll i=0; i<4; i++) MOD *= 2310;
    //for(int i=0; i<73; i++) arr[i]++;
    cout << (long long)MOD << "\n";
    JG(-1,0,6,47,10000000);
    cout << (long long)mp[10203040506ll] << "\n";
    //for(ll i:indexx) cout << i << " ";
    cnt = 0;
    JG1(47,0,5,47,1000000);
    int is[11]={3,9,29,32,41,44,48,59,60,62,79};
    for(int i:is){
        cout << (long long)arr[i] << " ";
    }
    //cout << cnt << "\n";
    return 0;
}