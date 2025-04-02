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

// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

template<typename T = int64_t, size_t sz = 19, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}

    void init(){
        fill(tree.begin(), tree.end(), 0);
    }

	void Update(int i, T val) {
		--i |= 1 << sz; tree[i] += val;
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

SegTree<ll, 19, F> sg(0, f);
vector<int> vals = {-2, -1};
int cntl(ll o){
    int u = CNT_UPPER(vals, o);
    return sg.Query(1, u-1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    set<int> st;
    int n; cin >> n;
    vector<int> v(n);
    for(auto &i:v) {
        cin >> i; st.insert(i);
    }
    int qq; cin >> qq;
    vector<array<int, 3>> query(qq);
    for(auto &[i,j,k]: query) {
        cin >> i >> j >> k;
        if(i == 1) st.insert(k);
    }

    
    for(auto i:st) vals.push_back(i);
    for(auto i:v){
        int u = CNT_LOWER(vals, i);
        sg.Update(u, 1);
    }

    for(auto [q,id,x]:query){
        id--;
        if(q == 1){
            int u = CNT_LOWER(vals, v[id]);
            sg.Update(u, -1);
            v[id] = x;
            u = CNT_LOWER(vals, v[id]);
            sg.Update(u, 1);
        }
        else{
            
        }
    }

    return 0;
}