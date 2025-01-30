#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

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

#define MOD 5000000

struct F {
	ll operator()(ll& a, ll& b) {
		return (a + b) % MOD;
	}
} f;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];

    vector<SegTree<ll, 17, F>> tree(k+1, SegTree<ll, 17, F>(0, f));
    for(int i=0; i<n; i++){
        for(int j=k; j>=1; j--){
            if(j == 1) tree[j].Update(a[i], tree[j].Query(a[i], a[i]) + 1);
            else{
                ll sm = tree[j-1].Query(1, a[i]-1);
                tree[j].Update(a[i], (tree[j].Query(a[i], a[i]) + sm) % MOD);
            }
        }
    }

    ll ans = tree[k].Query(1, 100000);
    cout << ans << "\n";
    return 0;
}