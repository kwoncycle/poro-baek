#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

struct SuffixArray{
    int n;
    vector<int> sa, rk, lcp;
    SuffixArray(){}
    SuffixArray(string &s) : n(s.size()), sa(n), rk(n+1, -1), lcp(n){
        for(int i=0; i<n; i++) sa[i] = i, rk[i] = s[i];
        for(int d=0; d<n; d=(d?d<<1:1)){
            vector<pii> g(n);
            vector<int> c(max(256, n+10));
            for(int i=0; i<n; i++){
                c[rk[i]]++; g[i] = {rk[i], rk[min(n, i+d)]};
            }
            auto p=c, t=sa;
            for(int i=1; i<p.size(); i++) p[i] += p[i-1];
            auto upd = [&](int x){t[p[rk[x]] - (c[rk[x]]--)] = x;};
            for(int i=n-d; i<n; i++) upd(i);
            for(int i=0; i<n; i++) if(sa[i] >= d) upd(sa[i]-d);
            swap(sa, t); rk[sa[0]]=0;
            for(int i=1; i<n; i++){
                rk[sa[i]] = rk[sa[i-1]] + (g[sa[i]] != g[sa[i-1]]);
            }
        }
        rk.pop_back();
        for(int i=0,h=0; i<n; i++, h=max(h-1,0)) if(rk[i]){
            while(max(i, sa[rk[i]-1])+h < n && s[i+h] == s[sa[rk[i]-1]+h]) h++;
            lcp[rk[i]] = h;
        }
    }
};

bool cmp(pll l, pll r){
    return (l.X*r.Y) < (l.Y*r.X);
}

template<typename T = int64_t, size_t sz = 17, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}

    void init(){
        fill(tree.begin(), tree.end(), 0);
    }

	void Update(int i, T val) {
        i++;
		--i |= 1 << sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(int l, int r) {
        l++; r++;
		T L = t, R = t; --l |= 1 << sz, --r |= 1 << sz;
		while (l <= r) {
			if (l & 1) L = f(L, tree[l++]);
			if (~r & 1) R = f(tree[r--], R);
			l >>= 1, r >>= 1;
		}
		return f(L, R);
	}
};

SuffixArray SA;

struct F {
	int operator()(int& a, int& b) {
        if(!a) return b;
        if(!b) return a;
		return SA.lcp[a] > SA.lcp[b] ? b : a;
	}
} f;

SegTree<int, 18, F> SG(0, f);

pll mx = {0,1};
set<int> st[200050];

int JG(int l, int r){
    if(l == r){
        st[l].insert(SA.sa[l]); 
        st[l].insert(-0x3f3f3f3f); 
        st[l].insert(0x3f3f3f3f);
        return l;
    }
    int i = SG.Query(l+1, r);
    set<int> newst;
    newst.insert(-0x3f3f3f3f);
    newst.insert(0x3f3f3f3f);
    
    if(l <= i-1){
        int i0 = JG(l, i-1);
        if(st[i0].size() > newst.size()){
            st[i0].swap(newst);
        }
        for(int o:st[i0]){
            if(abs(o) == 0x3f3f3f3f) continue;
            auto t1 = newst.upper_bound(o), t0 = t1; t0--;
            if(cmp(mx, {SA.lcp[i], o - (*t0)})) mx = {SA.lcp[i], o - (*t0)};
            if(cmp(mx, {SA.lcp[i], (*t1) - o})) mx = {SA.lcp[i], (*t1) - o};
        }
        for(int o:st[i0]) newst.insert(o);
    }
    if(i <= r){
        int i0 = JG(i, r);
        if(st[i0].size() > newst.size()){
            st[i0].swap(newst);
        }
        for(int o:st[i0]){
            if(abs(o) == 0x3f3f3f3f) continue;
            auto t1 = newst.upper_bound(o), t0 = t1; t0--;
            if(cmp(mx, {SA.lcp[i], o - (*t0)})) mx = {SA.lcp[i], o - (*t0)};
            if(cmp(mx, {SA.lcp[i], (*t1) - o})) mx = {SA.lcp[i], (*t1) - o};
        }
        for(int o:st[i0]) newst.insert(o);
    }
    newst.swap(st[r]);
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    int n = s.size();
    
    SA = SuffixArray(s);
    if(n > 26) mx = {1, 26};

    for(int i=0; i<n; i++){
        SG.Update(i, i);
    }
    JG(0, n-1);
    
    ll g = __gcd(mx.X, mx.Y);
    mx.X /= g; mx.Y /= g;
    cout << mx.X + mx.Y << "/" << mx.Y << "\n";
    return 0;
}