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

ll arr2[1][1] = {{211}};
ll bbb2[1] = {240};
ll arr3[2][2] = {{211,2758},{197,2771}};
ll bbb3[2] = {240,3360};
ll arr4[4][4] = {{211,5516,2562,33488},{197,5347,2575,33644},{183,5150,2771,33644},{184,5176,2588,33801}};
ll bbb4[4] = {240,6720,3360,43680};
ll arr5[11][11] = {{211,5516,2758,5124,66976,2366,61880,2758,33306,33488,373464},{197,5346,2576,4968,64922,2393,62543,2575,33644,31278,377208},{197,5152,2771,5150,67288,2379,62192,2576,31122,33644,375180},{183,4968,2575,5164,64909,2575,64922,2393,31278,31265,377208},{184,4994,2588,4993,65223,2406,62856,2406,31434,31422,378948},{169,4786,2379,5150,62556,2771,67288,2392,31265,31265,377208},{170,4811,2392,4994,62856,2588,65235,2405,31422,31422,378948},{197,5150,2576,4786,62556,2392,62530,2771,33644,33644,377208},{183,5176,2394,4812,62868,2405,62844,2588,33801,31434,378948},{184,4812,2588,4810,62844,2405,62844,2588,31434,33801,378948},{171,4836,2405,4836,63158,2418,63158,2418,31579,31579,380699}};
ll bbb5[11] = {240,6720,3360,6720,87360,3360,87360,3360,43680,43680,524160};
ll arr6[32][32] = {{211,5516,5124,5516,66976,5516,66612,4732,2562,61880,61880,66976,33488,746928,2184,57148,5124,61880,61880,28574,690144,66976,2562,33488,61880,746928,33488,746928,28574,345072,345072,3819816},{197,5347,4954,5151,64922,5151,64766,4590,2393,60177,60008,62556,31278,726180,2210,57785,4968,62361,60190,28899,697476,64922,2575,33644,62374,752388,31278,726180,28899,348660,348816,3857568},{183,4954,5164,4968,62543,4772,62374,4968,2393,60190,64909,60164,31265,725868,2393,60190,4785,62543,60164,31265,725868,59995,2575,31096,64922,723996,28899,697476,31278,348972,377208,3857568},{197,5151,4968,5347,64922,5151,64766,4772,2575,62374,62361,64922,33644,752388,2210,57798,4786,60177,60177,28886,697320,62556,2393,31278,60177,726180,31278,726180,28899,348816,348660,3857568},{184,4994,4811,4994,63026,4812,62868,4629,2405,60646,60477,60647,31422,731376,2236,58437,4641,60634,58436,29212,704712,60647,2405,31422,60646,731376,29225,704856,29225,352428,352428,3895848},{197,5151,4772,5151,62556,5347,64766,4589,2393,60177,59995,64922,31278,726180,2210,57785,4968,60190,62361,28899,697476,64922,2393,31278,60177,726180,33644,752388,28886,348660,348660,3857568},{183,4982,4798,4982,62868,4982,62739,4615,2406,60490,60308,62868,31434,729636,2222,58086,4812,60490,60490,29043,700800,62868,2406,31434,60490,729636,31434,729636,29043,350400,350400,3875124},{169,4590,4968,4772,60177,4589,59995,5346,2575,64740,64922,60164,31278,726024,2575,64740,4603,60177,60164,31278,726024,57798,2393,28912,62543,697632,28886,697320,33644,375180,377208,3857568},{183,4786,4786,5150,62530,4786,62556,5150,2771,67288,62556,62530,33644,754416,2392,62530,4448,58136,58136,29068,701376,58136,2224,29068,58136,701376,29068,701376,31265,377208,350688,3878160},{170,4629,4630,4798,60646,4629,60490,4980,2588,65235,60502,60646,31434,731508,2405,62844,4472,58437,58437,29224,704856,58424,2236,29212,58437,704712,29212,704712,31422,378948,352428,3895848},{170,4616,4993,4797,60477,4615,60308,4994,2406,60502,65223,60465,31422,729348,2406,60502,4628,60477,60465,31422,729348,58111,2406,29068,62856,701088,29043,700800,31434,350688,378948,3875124},{184,4812,4628,4994,60647,4994,62868,4628,2405,60646,60465,63026,31422,731376,2236,58437,4641,58436,60634,29212,704712,60647,2236,29225,58424,704856,31422,731376,29212,352428,352284,3895848},{184,4812,4810,5176,62844,4812,62868,4812,2588,62868,62844,62844,33801,757896,2236,58448,4472,58424,58424,29200,704568,58450,2236,29225,58424,704856,29225,704856,29224,352560,352284,3895848},{171,4655,4653,4823,60948,4655,60803,4654,2418,60959,60779,60948,31579,734867,2248,58738,4496,58726,58726,29357,708070,58738,2248,29369,58726,708203,29369,708203,29369,354168,354035,3913646},{156,4420,4786,4420,58136,4420,57772,5150,2392,62530,62556,58136,29068,701376,2771,67288,4784,62530,62530,33644,754416,58136,2224,29068,58136,701376,29068,701376,31265,377208,350688,3878160},{157,4445,4630,4446,58437,4445,58086,4980,2405,62844,60502,58437,29224,704856,2588,65235,4641,60646,60646,31434,731508,58424,2236,29212,58437,704712,29212,704712,31422,378948,352428,3895848},{183,4968,4785,4786,60333,4968,62556,4603,2224,58136,60164,60333,29068,701376,2392,60333,4995,62712,62712,31265,727896,62712,2392,31265,60333,727896,31265,727896,29068,350688,350688,3878160},{170,4797,4811,4629,60634,4630,60490,4629,2236,58437,60477,58436,29212,704712,2405,60646,4824,63026,60646,31422,731376,60646,2405,31422,60646,731376,29224,704844,29225,352428,352428,3895848},{170,4630,4628,4629,58436,4797,60490,4628,2236,58437,60465,60634,29212,704712,2405,60646,4824,60646,63026,31422,731376,60646,2236,29224,58424,704844,31422,731376,29212,352428,352284,3895848},{157,4446,4810,4444,58424,4446,58086,4812,2236,58448,62844,58424,29200,704568,2588,62868,4810,62844,62844,33801,757896,58448,2236,29225,58424,704856,29225,704856,29224,352560,352284,3895848},{158,4471,4653,4470,58726,4471,58400,4654,2248,58738,60779,58726,29357,708070,2418,60959,4666,60948,60948,31579,734867,58737,2248,29369,58726,708203,29369,708203,29369,354168,354035,3913646},{184,4994,4615,4812,60647,4994,62868,4446,2236,58424,58111,60647,29225,704856,2236,58424,4824,60646,60646,29224,704844,63026,2405,31422,60646,731376,31422,731376,29212,352284,352428,3895848},{183,5150,5150,4786,62530,4786,62556,4786,2224,58136,62556,58136,29068,701376,2224,58136,4784,62530,58136,29068,701376,62530,2771,33644,67288,754416,29068,701376,31265,350688,377208,3878160},{184,5176,4784,4812,62844,4812,62868,4448,2236,58424,58136,58450,29225,704856,2236,58424,4810,62844,58448,29225,704856,62844,2588,33801,62868,757896,29225,704856,29224,352284,352560,3895848},{170,4798,4994,4629,60646,4629,60490,4811,2236,58437,62856,58424,29212,704712,2236,58437,4641,60646,58424,29212,704712,60646,2588,31434,65235,731508,29212,704712,31422,352428,378948,3895848},{171,4823,4641,4655,60948,4655,60803,4472,2248,58726,58424,58738,29369,708203,2248,58726,4666,60948,58737,29369,708203,60948,2418,31579,60959,734867,29369,708203,29369,354035,354168,3913646},{184,4812,4446,4812,58450,5176,62868,4444,2236,58424,58086,62844,29225,704856,2236,58424,4810,58448,62844,29225,704856,62844,2236,29225,58424,704856,33801,757896,29200,352284,352284,3895848},{171,4655,4471,4655,58738,4823,60803,4470,2248,58726,58400,60948,29369,708203,2248,58726,4666,58737,60948,29369,708203,60948,2248,29369,58726,708203,31579,734867,29357,354035,354035,3913646},{157,4446,4812,4446,58450,4444,58086,5176,2405,62844,62868,58424,29224,704856,2405,62844,4472,58450,58424,29224,704856,58424,2405,29224,62844,704856,29200,704568,33801,378948,378948,3895848},{158,4470,4474,4472,58738,4470,58400,4810,2418,63158,58448,58738,29380,708336,2418,63158,4496,58738,58738,29380,708336,58714,2248,29357,58738,708070,29357,708070,31579,380699,354168,3913646},{158,4472,4836,4470,58738,4470,58400,4836,2248,58738,63158,58714,29357,708070,2248,58738,4496,58738,58714,29357,708070,58738,2418,29380,63158,708336,29357,708070,31579,354168,380699,3913646},{159,4496,4496,4496,59028,4496,58714,4496,2260,59028,58714,59028,29514,711572,2260,59028,4520,59028,59028,29514,711572,59028,2260,29514,59028,711572,29514,711572,29514,355786,355786,3931555}};
ll bbb6[32] = {240,6720,6720,6720,87360,6720,87360,6720,3360,87360,87360,87360,43680,1048320,3360,87360,6720,87360,87360,43680,1048320,87360,3360,43680,87360,1048320,43680,1048320,43680,524160,524160,5765760};

vector<vector<vector<vector<ll>>>> MT6(6, vector<vector<vector<ll>>>(1025, vector<vector<ll>>(32, vector<ll>(32, 0))));

#define MOD 1000000007ll

vector<vector<ll>> MT_mul(vector<vector<ll>>& M1, vector<vector<ll>>& M2){
    int n = M1.size();
    vector<vector<ll>> v(n, vector<ll>(n, 0));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                v[i][j] += M1[i][k]*M2[k][j]%MOD;
                v[i][j] %= MOD;
            }
        }
    }
    return v;
}

vector<vector<ll>> MT_pow(vector<vector<ll>>& M1, ll e){
    ll n = M1.size();
    vector<vector<ll>> ans(n, vector<ll>(n, 0)), zzm(n, vector<ll>(n, 0));
    for(int i=0; i<n; i++) ans[i][i] = 1;
    for(int i=0; i<n; i++) zzm[i][i] = 1;
    zzm = MT_mul(M1, zzm);
    while(e){
        if(e&1) ans = MT_mul(zzm, ans);
        e /= 2;
        zzm = MT_mul(zzm, zzm);
    }
    return ans;
}

vector<vector<ll>> MT_pow_6(vector<vector<ll>>& M1, ll e){
    ll n = M1.size();
    vector<vector<ll>> ans(n, vector<ll>(n, 0)), zzm(n, vector<ll>(n, 0));
    for(int i=0; i<n; i++) ans[i][i] = 1;
    for(int i=0; i<n; i++) zzm[i][i] = 1;
    vector<int> ev;
    while(e){
        ev.push_back(e&1023); e /= 1024;
    }
    for(int i=0; i<(int)ev.size(); i++){
        ans = MT_mul(MT6[i][ev[i]], ans);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    vector<vector<vector<ll>>> MTRIX(7);
    int sz = 1;
    MTRIX[2] = vector<vector<ll>>(sz, vector<ll>(sz, 0));
    sz = 2;
    MTRIX[3] = vector<vector<ll>>(sz, vector<ll>(sz, 0));
    sz = 4;
    MTRIX[4] = vector<vector<ll>>(sz, vector<ll>(sz, 0));
    sz = 11;
    MTRIX[5] = vector<vector<ll>>(sz, vector<ll>(sz, 0));
    sz = 32;
    MTRIX[6] = vector<vector<ll>>(sz, vector<ll>(sz, 0));

    sz = 1;
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++) MTRIX[2][i][j] = arr2[j][i];
    }
    sz = 2;
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++) MTRIX[3][i][j] = arr3[j][i];
    }
    sz = 4;
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++) MTRIX[4][i][j] = arr4[j][i];
    }
    sz = 11;
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++) MTRIX[5][i][j] = arr5[j][i];
    }
    sz = 32;
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++) MTRIX[6][i][j] = arr6[j][i];
    }
    
    for(int i=0; i<32; i++){
        MT6[0][0][i][i] = 1;
        for(int j=0; j<32; j++) {
            MT6[0][1][i][j] = MTRIX[6][i][j];
        }
    }
    for(int x=0; x<6; x++){
        for(int i=0; i<32; i++){
            MT6[x][0][i][i] = 1;
        }
        if(x > 0){
            MT6[x][1] = MT6[x-1][1024];
        }
        for(int i=2; i<=1024; i++){
            MT6[x][i] = MT_mul(MT6[x][1], MT6[x][i-1]);
        }
    }


    vector<vector<ll>> FI(7);
    sz = 1;
    FI[2] = vector<ll>(sz,0);
    for(int i=0; i<sz; i++){
        FI[2][i] = bbb2[i];
    }
    sz = 2;
    FI[3] = vector<ll>(sz,0);
    for(int i=0; i<sz; i++){
        FI[3][i] = bbb3[i];
    }
    sz = 4;
    FI[4] = vector<ll>(sz,0);
    for(int i=0; i<sz; i++){
        FI[4][i] = bbb4[i];
    }
    sz = 11;
    FI[5] = vector<ll>(sz,0);
    for(int i=0; i<sz; i++){
        FI[5][i] = bbb5[i];
    }
    sz = 32;
    FI[6] = vector<ll>(sz,0);
    for(int i=0; i<sz; i++){
        FI[6][i] = bbb6[i];
    }
    
    int qq; cin >> qq;

    while(qq--){
        ll h, w; cin >> h >> w;
        if(h>w){
            h ^= w; w ^= h; h ^= w;
        }
        if(h == 1){
            ll ans = 16 * poww(15, w-1, MOD) % MOD;
            cout << ans << "\n";
        }
        else{
            vector<vector<ll>> M1;
            if(h != 6) M1 = MT_pow(MTRIX[h], w-1);
            else M1 = MT_pow_6(MTRIX[h], w-1);
            ll ans = 0;
            int sz = MTRIX[h].size();
            /*
            for(int i=0; i<sz; i++){
                for(int j=0; j<sz; j++) cout << M1[i][j] << " "; cout << "\n";
            }
            cout << "=====================\n";
            for(int i=0; i<sz; i++){
                for(int j=0; j<sz; j++) cout << MTRIX[6][i][j] << " "; cout << "\n";
            }*/

            for(int i=0; i<sz; i++){
                for(int j=0; j<sz; j++){
                    ans += M1[i][j]*FI[h][j]%MOD;
                    ans %= MOD;
                }
            }
            cout << ans << "\n";
        }
    }
    return 0;
}