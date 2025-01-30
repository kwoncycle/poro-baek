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
		return max(a, b);
	}
} f;

ll n, m; 
SegTree<ll, 11, F> sg(0, f);
vector<ll> harr;
vector<array<ll, 4>> v;

ll find_mx(int l, int r){
    sg.init();
    for(int i=0; i<n; i++){
        ll mx = sg.Query(0+1, v[i][1]+1);
        if(l <= v[i][3] and v[i][3] <= r) mx += v[i][2];
        sg.Update(v[i][1]+1, mx);
    }
    return sg.Query(0+1, 2002+1);
} 


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;

    v.resize(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<4; j++) cin >> v[i][j];
    }
    
    
    sort(v.begin(), v.end(), [&](array<ll,4> l, array<ll,4> r){
        return l[0] == r[0] ? l[1] < r[1] : l[0] < r[0];
    });

    vector<int> vx, vy;
    for(int i=0; i<n; i++) vx.push_back(v[i][0]), vy.push_back(v[i][1]);
    sort(vx.begin(), vx.end()); sort(vy.begin(), vy.end());
    int id_x = 0, id_y = 0;
    map<int, int> mx, my;
    for(int i=0; i<n; i++){
        if(mx.find(vx[i]) == mx.end()) mx[vx[i]] = id_x++;
        if(my.find(vy[i]) == my.end()) my[vy[i]] = id_y++;
        
    }
    for(int i=0; i<n; i++){
        v[i][0] = mx[v[i][0]];
        v[i][1] = my[v[i][1]];
    }

    for(int i=0; i<n; i++) harr.push_back(v[i][3]);
    sort(harr.begin(), harr.end());
    harr.erase(unique(harr.begin(), harr.end()), harr.end());

    {
        ll i1 = harr[0], i2 = harr.back();
        if(find_mx(i1, i2) < m){
            cout << "-1\n"; return 0;
        }
    }

    ll mn = 0x3f3f3f3f3f3f3fll;
    int nh = harr.size();
    for(int i1=0, i2=0; i1<nh; i1++){
        while(i2 < nh and find_mx(harr[i1], harr[i2]) < m) i2++;
        if(i2 < nh){
            mn = min(harr[i2] - harr[i1], mn);
        }
    }
    cout << mn << "\n";
    return 0;
}