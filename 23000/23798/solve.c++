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


// THIS IS LAZY
class SegTree1{
public:   
    int n;
    vector<ll> segtree, lazy;


    SegTree1(int n_input){
        n = n_input;
        lazy = vector<ll>(4*n+5, 0);
        segtree = vector<ll>(4*n+5, 0);
    }

    // add s~e += target
    void update_range(int i1, int i2, ll target){
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(int node, int s, int e, int i1, int i2, ll target){
        segtree[node] += lazy[node];
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] += target;
            segtree[node] += lazy[node];
            if(e != s){
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
    }

    ll query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    ll query_segtree(int node, int s, int e, int i1, int i2){
        segtree[node] += lazy[node];
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return 0x3f3f3f3f;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        ll q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        ll q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return min(q1, q2);
    }
};


/*
SegTree<type, sz, F> ST(default, f)와 같이 선언해주면 노드의 자료형이 type이며 
노드의 기본 값이 default이고, 세그먼트 트리의 인덱스가 [1, 2^sz] 범위이고, 
두 노드를 합칠 때 f(node1, node2)를 이용하는 세그먼트 트리를 생성할 수 있습니다.*/
// USAGE: SegTree<int, 20, F> ST(1, f);


const ll MOD = 1000000007;

ll fct[1000001], fctinv[1000001];

ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return ans;
}


ll C(ll a, ll b){
    if(b < 0) return 0;
    return fct[a]*fctinv[b]%MOD*fctinv[a-b]%MOD;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    fct[0] = 1;
    for(int i=1; i<=1000000; i++){
        fct[i] = fct[i-1]*i%MOD;
    }

    fctinv[1000000] = poww(fct[1000000], MOD - 2);
    for(int i=1000000; i>=1; i--){
        fctinv[i-1] = fctinv[i] * i % MOD;
    }

    int n; cin >> n;
    string s; cin >> s;

    SegTree<ll, 20, F> tree(0, f);
    SegTree1 sg1(n), sg2(n);
    for(int i=0; i<n; i++){
        tree.Update(i+1, s[i]=='(' ? 1 : -1);
    }

    for(int i=0; i<n; i++){
        sg1.update_range(i, n-1, s[i]=='(' ? 1 : -1);
        sg2.update_range(0, i, s[i]=='(' ? -1 : 1);
    }


    int qq; cin >> qq;
    while(qq--){
        int q; cin >> q;
        if(q == 1){
            int k; cin >> k;
            s[k-1] = '(' + ')' - s[k-1];
            tree.Update(k, s[k-1]=='(' ? 1 : -1);
            sg1.update_range(k-1, n-1, s[k-1]=='(' ? 2 : -2);
            sg2.update_range(0, k-1, s[k-1]=='(' ? -2 : 2);
        }
        else{
            int l, r; cin >> l >> r;
            l--; r--;
            int sm1=0, sm2=0;
            if(l-1 >= 0) sm1 = tree.Query(0 + 1, l-1 + 1);
            if(r+1 < n) sm2 = tree.Query(r+1 + 1, n-1 + 1);
            if(l-1 >= 0){
                if(sg1.query(0, l-1) < 0){
                    cout << "0\n"; continue;
                }
            }
            if(r+1 < n){
                if(sg2.query(r+1, n-1) < 0){
                    cout << "0\n"; continue;
                }
            }
            if(sm1 < 0 or sm2 > 0) cout << "0\n";
            else{
                sm2 = -sm2;
                // a+b = r-l+1, a-b = sm2-sm1;
                int a = (sm2-sm1 + r-l+1)/2;
                int b = (r-l+1 - (sm2-sm1))/2;
                int x = max(b-sm1, 0);
                if(a < 0 or b < 0){
                    cout << "0\n"; continue;
                }
                ll ans = C(a+b, a) - C(a+b, x-1);
                ans %= MOD; if(ans < 0) ans += MOD;
                cout << ans << "\n";
            }
        }
    }
    return 0;
}