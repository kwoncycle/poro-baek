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

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

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
		return a + b;
	}
} f;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<ll> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    set<ll> st;
    map<ll, int> mp;
    for(int i=0; i<n; i++) st.insert(v[i]);
    int id = 1;
    for(auto i:st){
        mp[i] = id; id++;
    }

    SegTree<ll, 19, F> sg(0, f), sg1(0, f);
    for(int i=0; i<n; i++){
        v[i] = mp[v[i]];
        sg1.Update(v[i], sg1.Query(v[i], v[i]) + 1);
    }

    ll ans = 0;

    for(int i=0; i<n; i++){
        sg1.Update(v[i], sg1.Query(v[i], v[i]) - 1);
        ll o1 = sg.Query(1, v[i]-1), o2 = sg1.Query(1, v[i]-1);
        sg.Update(v[i], sg.Query(v[i], v[i]) + 1);
        ans += o1*o2;
    }

    cout << ans << "\n";

    return 0;
}