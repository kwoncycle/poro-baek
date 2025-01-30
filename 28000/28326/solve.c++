#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller th
template<typename T = int64_t, size_t sz = 22, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}

    void init(){
        fill(tree.begin(), tree.end(), 0x3f3f3f3f3f);
    }

	void Update(ll i, T val) {
		--i |= 1 << sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(ll l, ll r) {
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
		return min(a, b);
	}
} f;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m; 
    cin >> n >> m;
    vector<array<ll, 3>> v(n);
    set<ll> v1;
    for(ll i=0; i<n; i++) cin >> v[i][0] >> v[i][1] >> v[i][2];
    for(ll i=0; i<n; i++){
        v1.insert(v[i][0]);
        v1.insert(v[i][1] - 1);
    }
    vector<pll> GJ(m);
    for(ll i=0; i<m; i++) {
        cin >> GJ[i].X >> GJ[i].Y;
        v1.insert(GJ[i].X);
        v1.insert(GJ[i].Y);
    }
    //sort(v1.begin(), v1.end());
    //v1.erase(unique(v1.begin(), v1.end()), v1.end());
    assert(v1.size() < 1000050);
    map<ll, ll> mp; //asdfasdfasdfasfasdfasdfasdfasfa 왜틀리노시발
    ll cnti = 0;
    for(ll i:v1){
        mp[i] = cnti++;
    }
    SegTree<ll, 22, F> tree(0x3f3f3f3f3fll, f);
    for(ll i=m-1; i>=0; i--){
        ll id1 = mp[GJ[i].X];
        tree.Update(id1+1, i);
        ll id2 = mp[GJ[i].Y];
        tree.Update(id2+1, i);
    }
    vector<ll> sm(m, 0);
    for(ll i=0; i<n; i++){
        ll id1 = mp[v[i][0]], id2 = mp[v[i][1]-1];
        ll w = tree.Query(id1+1, id2+1);
        if(w >= m) continue;
        if(v[i][0] <= GJ[w].X and GJ[w].X <= v[i][1] - 1 and v[i][0] <= GJ[w].Y and GJ[w].Y <= v[i][1] - 1){
            sm[w] += v[i][2];
        }
        assert((v[i][0] <= GJ[w].X and GJ[w].X <= v[i][1] - 1) or (v[i][0] <= GJ[w].Y and GJ[w].Y <= v[i][1] - 1));
    }
    for(ll i:sm) cout << i << "\n";
    return 0;
}