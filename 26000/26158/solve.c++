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
	int operator()(int& a, int& b) {
		return min(a, b);
	}
} f;

/*
SegTree<type, sz, F> ST(default, f)와 같이 선언해주면 노드의 자료형이 type이며 
노드의 기본 값이 default이고, 세그먼트 트리의 인덱스가 [1, 2^sz] 범위이고, 
두 노드를 합칠 때 f(node1, node2)를 이용하는 세그먼트 트리를 생성할 수 있습니다.*/
// USAGE: SegTree<int, 20, F> ST(1, f);



queue<int> q[500005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    SegTree<int, 19, F> tree(0x3f3f3f3f, f);
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    set<int> st_p;
    for(int i:v) st_p.insert(i);
    int id = 0;
    map<int, int> mp;
    for(int i:st_p) mp[i] = id, id++;
    for(int i=0; i<n; i++) v[i] = mp[v[i]];

    for(int i=0; i<k; i++){
        q[v[i]].push(i);
        if(q[v[i]].size() == 1) tree.Update(v[i]+1, i);
    }

    int ans = 0;
    int id1 = k;
    while(true){
        int di = tree.Query(1, 500004);
        if(di != 0x3f3f3f3f){
            ans++;
        }
        else break;
        int d = v[di];
        //cout << di << " " << d << "\n";
        q[d].pop();
        if(q[d].size() == 0) tree.Update(d+1, 0x3f3f3f3f);
        else tree.Update(d+1, q[d].front());

        if(id1 < n){
            q[v[id1]].push(id1);
            if(q[v[id1]].size() == 1) tree.Update(v[id1]+1, id1); id1++;
        }

        while(true){
            int ni = tree.Query(d+1 +1, 500004); 
            if(ni != 0x3f3f3f3f){
                int nd = v[ni];
                //cout << ni << " " << nd << "\n";
                q[nd].pop();
                if(q[nd].size() == 0) tree.Update(nd+1, 0x3f3f3f3f);
                else tree.Update(nd+1, q[nd].front());
                if(id1 < n){
                    q[v[id1]].push(id1);
                    if(q[v[id1]].size() == 1) tree.Update(v[id1]+1, id1); id1++;
                }
                d = nd;
            }
            else break;
        }
    }
    cout << ans << "\n";
    return 0;
}