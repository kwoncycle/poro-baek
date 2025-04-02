#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

template<typename T = int64_t, size_t sz = 17, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}

    void init(){
        fill(tree.begin(), tree.end(), 0);
    }

	void Update(int i, T val) {
		--i |= 1 << sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(int l, int r) {
		T L = t, R = t; --l |= 1 << sz, --r |= 1 << sz;
		while (l <= r) {
			if (l & 1) L = f(L, tree[l++]);
			if (~r & 1) R = f(tree[r--], R);
			l >>= 1, r >>= 1;
		}
		return f(L, R);
	}
};

struct F {
	ll operator()(ll& a, ll& b) {
		return a+b;
	}
} f;

/*
SegTree<type, sz, F> ST(default, f)와 같이 선언해주면 노드의 자료형이 type이며 
노드의 기본 값이 default이고, 세그먼트 트리의 인덱스가 [1, 2^sz] 범위이고, 
두 노드를 합칠 때 f(node1, node2)를 이용하는 세그먼트 트리를 생성할 수 있습니다.*/
// USAGE: SegTree<int, 20, F> ST(1, f);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int x, y; cin >> x >> y;
    int n, m; cin >> n >> m;
    vector<pii> v1(n), v2(m);
    for(auto &[i,j]:v1) cin >> i >> j;
    for(auto &[i,j]:v2) cin >> i >> j;

    sort(all(v1));
    sort(all(v2));

    vector<pii> u1, u2;
    for(int i=0; i<n; i++) u1.push_back({v1[i].Y, i+1});
    for(int i=0; i<m; i++) u2.push_back({v2[i].Y, i+1});

    sort(all(u1));
    sort(all(u2));

    ll ans = (ll)(n+1)*(m+1);

    SegTree<ll, 20, F> S1(0, f), S2(0, f);

    for(int i=0; i<n; i++){
        ans += S1.Query(u1[i].Y, n+5);
        S1.Update(u1[i].Y, 1);
    }
    for(int i=0; i<m; i++){
        ans += S2.Query(u2[i].Y, m+5);
        S2.Update(u2[i].Y, 1);
    }

    cout << ans << "\n";

    return 0;
}