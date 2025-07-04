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
    SuffixArray(vector<int> &s) : n(s.size()), sa(n), rk(n+1, -1), lcp(n) {
        for(int i=0; i<n; i++) sa[i] = i, rk[i] = s[i];
        for(int d=0; d<n; d = d ? (d<<1) : 1){
            vector<pii> g(n);
            vector<int> c(n + 256);
            for(int i=0; i<n; i++){
                c[rk[i]]++, g[i] = {rk[i], rk[min(n, i+d)]};
            }
            auto p=c, t=sa;
            for(int i=1; i<p.size(); i++) p[i] += p[i-1];
            auto upd = [&](int x){t[p[rk[x]] - (c[rk[x]]--)] = x; };
            for(int i=n-d; i<n; i++) upd(i);
            for(int i=0; i<n; i++){
                if(sa[i] >= d) upd(sa[i] - d);
            }
            swap(sa, t); rk[sa[0]] = 0;
            for(int i=1; i<n; i++){
                rk[sa[i]] = rk[sa[i-1]] + (g[sa[i]] != g[sa[i-1]]);
            }
        }
        rk.pop_back();
        for(int i=0, h=0; i<n; i++, h=max(h-1, 0)){
            if(rk[i]){
                while(max(i, sa[rk[i]-1]) + h < n && s[i+h] == s[sa[rk[i]-1] + h]) h++;
                lcp[rk[i]] = h;
            }
        }
    }
};

int n, k;
string v[500005];
vector<int> s;
vector<int> where;
vector<int> U, safek, safek1; // min to go k, k+1

int cnt[1000005], endpoint[500005];

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
/*
SegTree<type, sz, F> ST(default, f)와 같이 선언해주면 노드의 자료형이 type이며 
노드의 기본 값이 default이고, 세그먼트 트리의 인덱스가 [1, 2^sz] 범위이고, 
두 노드를 합칠 때 f(node1, node2)를 이용하는 세그먼트 트리를 생성할 수 있습니다.*/
// USAGE: SegTree<int, 20, F> ST(1, f);
struct F {
	int operator()(int& a, int& b) {
		return min(a, b);
	}
} f;

SegTree<int, 20, F> SG(0x3f3f3f3f, f);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> k;
    for(int i=1; i<=n; i++){
        cin >> v[i];
        for(char c:v[i]){
            s.push_back((int)c);
            where.push_back(i);
        }
        s.push_back(i + 200);
        endpoint[i] = s.size() - 1;
        where.push_back(i);
    }

    int N = s.size();
    U.resize(N+3); safek.resize(N+3); safek1.resize(N+3);

    SuffixArray SA(s); SA.lcp.push_back(0);
    for(int i=0; i<N; i++){
        U[i] = SA.sa[i];
    }
    for(int i=0; i<N; i++){
        SG.Update(i, SA.lcp[i+1]);
    }
    int diff = 0;
    for(int i=0, j=0; i<N; i++){
        while(j < N and diff < k){
            if(!cnt[where[SA.sa[j]]]) diff++;
            cnt[where[SA.sa[j]]]++;
            j++;
        }
        if(diff == k) safek[i] = j-1;
        else safek[i] = N;
        cnt[where[SA.sa[i]]]--;
        if(!cnt[where[SA.sa[i]]]) diff--;
    }

    memset(cnt, 0, sizeof(cnt));
    diff = 0;
    for(int i=0, j=0; i<N; i++){
        while(j < N and diff < k + 1){
            if(!cnt[where[SA.sa[j]]]) diff++;
            cnt[where[SA.sa[j]]]++;
            j++;
        }
        if(diff == k + 1) safek1[i] = j-1;
        else safek1[i] = N;
        cnt[where[SA.sa[i]]]--;
        if(!cnt[where[SA.sa[i]]]) diff--;
    }

    ll ans = 0;
    ll share = 0;
    for(int i=0; i<N; i++){
        if(safek[i] == N) break;
        int i1 = safek[i];
        if(i == i1){
            ll u = endpoint[where[U[i]]] - U[i];
            ans += max(0ll, u - share);
            share = max(share, u);
            share = min(share, (ll)SA.lcp[i+1]);
        }
        else{
            ll u = SG.Query(i, i1-1);
            u = min(u, (ll)endpoint[where[U[i]]] - U[i]);
            ans += max(0ll, u - share);
            share = max(share, u);
            share = min(share, (ll)SA.lcp[i+1]);
        }
    }

    share = 0;
    for(int i=0; i<N; i++){
        if(safek1[i] == N) break;
        int i1 = safek1[i];
        if(i == i1){
            ll u = endpoint[where[U[i]]] - U[i];
            ans -= max(0ll, u - share);
            share = max(share, u);
            share = min(share, (ll)SA.lcp[i+1]);
        }
        else{
            ll u = SG.Query(i, i1-1);
            u = min(u, (ll)endpoint[where[U[i]]] - U[i]);
            ans -= max(0ll, u - share);
            share = max(share, u);
            share = min(share, (ll)SA.lcp[i+1]);
        }
    }

    cout << ans << "\n";

    // for(int i=0; i<N; i++){
    //     if(s[i] < 200) cout << (char)s[i];
    //     else cout << "#";
    // }
    // cout << "\n";

    // for(int i=0; i<N; i++) cout << U[i] << " "; cout << " U\n";
    // for(int i=0; i<N; i++) cout << where[U[i]] << " "; cout << " where\n";
    // for(int i=0; i<N; i++) cout << safek[i] << " "; cout << "safek\n";
    // for(int i=0; i<N; i++) cout << safek1[i] << " "; cout << "safek+1\n";
    // for(int i=0; i<N; i++) cout << SA.lcp[i] << " "; cout << "lcp\n";

    // for(int i:SA.lcp) cout << i << " "; cout << "\n";


    return 0;
}