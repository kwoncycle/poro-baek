#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

struct F {
	int operator()(int& a, int& b) {
		return max(a, b);
	}
} f1;

template<typename T = int, size_t sz = 9, typename F = F>
struct SegTree {
	T tree[1027]; T t=0; F f=f1;
	SegTree() : t(0) {}
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



/*
SegTree<type, sz, F> ST(default, f)와 같이 선언해주면 노드의 자료형이 type이며 
노드의 기본 값이 default이고, 세그먼트 트리의 인덱스가 [1, 2^sz] 범위이고, 
두 노드를 합칠 때 f(node1, node2)를 이용하는 세그먼트 트리를 생성할 수 있습니다.*/
// USAGE: SegTree<int, 20, F> ST(1, f);


int V[501][501];
SegTree<int, 9, F> sg1[501], sg2[501];//(501, SegTree<int, 9, F>(0, f)), sg2(501, SegTree<int, 9, F>(0, f));

inline int find_mx(int x, int y, int dx, int dy){
    if(dx == 1) return sg1[x].Query(y, y+dy-1);
    else return sg2[y].Query(x, x+dx-1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) cin >> V[i][j];
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++) sg1[i].Update(j, V[i][j]);
    }

    for(int j=1; j<=m; j++){
        for(int i=1; i<=n; i++) sg2[j].Update(i, V[i][j]);
    }

    vector<pii> dir = {{-1,0},{1,0},{0,-1},{0,1}};
    int qq; cin >> qq;
    vector<int> cntt(100005, 0);
    vector<int> tmp(5005);
    while(qq--){
        int x, y, r, c, k, d;
        cin >> x >> y >> r >> c >> k >> d;
        d--;
        if(d == 0){
            x += k-1;
            d = 1;
        }
        if(d == 2){
            y += k-1;
            d = 3;
        }

        if(d == 1){
            pii cur = {x,y};
            priority_queue<pii> pq;
            for(int i=0; i<r; i++){
                int o = find_mx(x+i, y, 1, c);
                tmp[cur.X+i] = o;
                pq.push({o, cur.X+i});
            }
            ll ans = 0;
            for(int i=0; i<k; i++){
                ans ^= (pq.top().X);
                while(!pq.empty() and pq.top().Y >= cur.X + r - 1 - i) pq.pop();
                int o = find_mx(cur.X-i-1, cur.Y, 1, c);
                pq.push({o, cur.X-i-1});
            }
            cout << ans << "\n";
        }
        else{
            pii cur = {x,y};
            priority_queue<pii> pq;
            for(int i=0; i<c; i++){
                int o = find_mx(cur.X, cur.Y+i, r, 1);
                tmp[cur.Y+i] = o;
                pq.push({o, cur.Y+i});
            }
            ll ans = 0;
            for(int i=0; i<k; i++){
                ans ^= (pq.top().X);
                while(!pq.empty() and pq.top().Y >= cur.Y + c - 1 - i) pq.pop();
                int o = find_mx(cur.X, cur.Y-i-1, r, 1);
                pq.push({o, cur.Y - i - 1});
            }
            cout << ans << "\n";
        }
    }
    
    return 0;
}