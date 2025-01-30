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
		return min(a, b);
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
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(int i=0; i<n; i++){
        cin >> v[i]; v[i]--;
    }
    vector<string> T(k);
    for(int i=0; i<k; i++) cin >> T[i];
    for(int i=0; i<k; i++){
        if(i != v[i]) T[i][i] = '1';
    }
    vector<vector<int>> nxt(n, vector<int>(k, -1)), bef(n, vector<int>(k, -1));
    for(int i=0; i<n; i++){
        for(int j=0; j<k; j++){
            bef[i][j] = i-1>=0 ? bef[i-1][j] : -1;
            if(i-1 >= 0) bef[i][v[i-1]] = i-1;
        }
    }

    for(int i=n-1; i>=0; i--){
        for(int j=0; j<k; j++){
            nxt[i][j] = i+1<n ? nxt[i+1][j] : -1;
            if(i+1 < n) nxt[i][v[i+1]] = i+1;
        }
    }

    vector<ll> val(n, 0x3f3f3f3f3f3f3f);
    val[0] = 0;

    for(int u=0; u<=2*k; u++){
        for(int i=0; i<n; i++){
            for(int j=0; j<k; j++){
                if(T[j][v[i]] == '1'){
                    //cout << i << " -> " << j << "\n";
                    if(bef[i][j] >= 0){
                        int o = bef[i][j];//cout << o << "\n";
                        val[i] = min(val[i], val[o] + abs(i - o));
                    }
                    if(nxt[i][j] >= 0){
                        int o = nxt[i][j];//cout << o << "\n";
                        val[i] = min(val[i], val[o] + abs(i - o));
                    }
                }
            }
        }

        //for(int i=0; i<n; i++) cout << val[i] << " "; cout << "a\n";
    }
    if(val[n-1] > 0x3f3f3f3f3f3f) cout << "-1\n";
    else cout << val[n-1] << "\n";
    return 0;
}