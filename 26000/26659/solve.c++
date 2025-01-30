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

struct S{
    int x1, x2, y, sz; char s;
    S(int x1, int x2, int y, char s):x1(x1),x2(x2),y(y),s(s){};
    S(){};
};


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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<S> v(n);
    for(int i=0; i<n; i++){
        cin >> v[i].x1 >> v[i].x2 >> v[i].y >> v[i].s;
        v[i].sz = v[i].x2 - v[i].x1 + 1;
    }
    vector<int> x_val, y_val;
    for(int i=0; i<n; i++){
        x_val.push_back(v[i].x1);
        x_val.push_back(v[i].x2);
        y_val.push_back(v[i].y);
    }
    sort(x_val.begin(), x_val.end());
    sort(y_val.begin(), y_val.end());
    x_val.erase(unique(x_val.begin(), x_val.end()), x_val.end());
    y_val.erase(unique(y_val.begin(), y_val.end()), y_val.end());

    map<int, int> mp_x, mp_y;
    int id_x = 0, id_y = 0;
    for(int i:x_val){
        if(mp_x.find(i) == mp_x.end()) mp_x[i] = id_x++;
    }
    for(int i:y_val){
        if(mp_y.find(i) == mp_y.end()) mp_y[i] = id_y++;
    }
    vector<array<int, 3>> order; // order[i] = {when, in/out, index}  0:out 1:in
    for(int i=0; i<n; i++){
        v[i].x1 = mp_x[v[i].x1];
        v[i].x2 = mp_x[v[i].x2];
        v[i].y = mp_y[v[i].y];
        v[i].y++;
        order.push_back({v[i].x1, 1, i});
        order.push_back({v[i].x2+1, 0, i});
    }
    SegTree<ll, 19, F> Tree_one(0, f);
    set<int> setS, setD;
    set<pair<int, char>> setC;
    setS.insert(0); setS.insert(300000);
    setD.insert(0); setD.insert(300000);
    setC.insert({0, 'A'});
    setC.insert({300000, 'B'});
    sort(order.begin(), order.end());
    int no = order.size();

    ll ans = 0, mxans = 0;
    for(int i=0; i<no; i++){
        int i1 = i;
        while(i1 < no and order[i][0] == order[i1][0]){
            // do something
            int id = order[i1][2];
            if(order[i1][1] == 1){
                if(v[id].s == 'S'){
                    if(setC.empty()) ans = v[id].sz;
                    else{
                        auto t1 = setC.lower_bound({v[id].y, 255});
                        auto t2 = t1; t2--;
                        if((*t1).Y != v[id].s and (*t2).Y != v[id].s){
                            auto t = setS.lower_bound(v[id].y);
                            int i2 = *t;
                            t--;
                            int i1 = *t;
                            ll m1 = Tree_one.Query(i1+1, v[id].y), m2 = Tree_one.Query(v[id].y+1, i2-1), m3 = Tree_one.Query(i1+1, i2-1);
                            ans += v[id].sz + m1 + m2 - m3;
                        }
                        else{
                            auto t = setD.lower_bound(v[id].y);
                            int i2 = *t;
                            t--;
                            int i1 = *t;
                            ll m1 = Tree_one.Query(i1+1, i2-1);
                            ll m2 = max(m1, (ll)v[id].sz);
                            ans += m2-m1;
                        }
                    }
                }
                else if(v[id].s == 'D'){
                    if(setC.empty()) ans = v[id].sz;
                    else{
                        auto t1 = setC.lower_bound({v[id].y, 255});
                        auto t2 = t1; t2--;
                        if((*t1).Y != v[id].s and (*t2).Y != v[id].s){
                            auto t = setD.lower_bound(v[id].y);
                            int i2 = *t;
                            t--;
                            int i1 = *t;
                            ll m1 = Tree_one.Query(i1+1, v[id].y), m2 = Tree_one.Query(v[id].y+1, i2-1), m3 = Tree_one.Query(i1+1, i2-1);
                            ans += v[id].sz + m1 + m2 - m3;
                        }
                        else{
                            auto t = setS.lower_bound(v[id].y);
                            int i2 = *t;
                            t--;
                            int i1 = *t;
                            ll m1 = Tree_one.Query(i1+1, i2-1);
                            ll m2 = max(m1, (ll)v[id].sz);
                            ans += m2-m1;
                        }
                    }
                }
                Tree_one.Update(v[id].y, v[id].sz);
                if(v[id].s == 'S') setS.insert(v[id].y), setC.insert({v[id].y, 'S'});
                else if(v[id].s == 'D') setD.insert(v[id].y), setC.insert({v[id].y, 'D'});
            }
            else if(order[i1][1] == 0){
                Tree_one.Update(v[id].y, 0);
                if(v[id].s == 'S') setS.erase(v[id].y), setC.erase({v[id].y, 'S'});
                else if(v[id].s == 'D') setD.erase(v[id].y), setC.erase({v[id].y, 'D'});
                if(v[id].s == 'S'){
                    if(setC.empty()) ans = v[id].sz;
                    else{
                        auto t1 = setC.lower_bound({v[id].y, 255});
                        auto t2 = t1; t2--;
                        if((*t1).Y != v[id].s and (*t2).Y != v[id].s){
                            auto t = setS.lower_bound(v[id].y);
                            int i2 = *t;
                            t--;
                            int i1 = *t;
                            ll m1 = Tree_one.Query(i1+1, v[id].y), m2 = Tree_one.Query(v[id].y+1, i2-1), m3 = Tree_one.Query(i1+1, i2-1);
                            ans -= v[id].sz + m1 + m2 - m3;
                        }
                        else{
                            auto t = setD.lower_bound(v[id].y);
                            int i2 = *t;
                            t--;
                            int i1 = *t;
                            ll m1 = Tree_one.Query(i1+1, i2-1);
                            ll m2 = max(m1, (ll)v[id].sz);
                            ans -= m2-m1;
                        }
                    }
                }
                else if(v[id].s == 'D'){
                    if(setC.empty()) ans = v[id].sz;
                    else{
                        auto t1 = setC.lower_bound({v[id].y, 255});
                        auto t2 = t1; t2--;
                        if((*t1).Y != v[id].s and (*t2).Y != v[id].s){
                            auto t = setD.lower_bound(v[id].y);
                            int i2 = *t;
                            t--;
                            int i1 = *t;
                            ll m1 = Tree_one.Query(i1+1, v[id].y), m2 = Tree_one.Query(v[id].y+1, i2-1), m3 = Tree_one.Query(i1+1, i2-1);
                            ans -= v[id].sz + m1 + m2 - m3;
                        }
                        else{
                            auto t = setS.lower_bound(v[id].y);
                            int i2 = *t;
                            t--;
                            int i1 = *t;
                            ll m1 = Tree_one.Query(i1+1, i2-1);
                            ll m2 = max(m1, (ll)v[id].sz);
                            ans -= m2-m1;
                        }
                    }
                }
            }
            mxans = max(ans, mxans);
            i1++;
        }
        i = i1-1;
    }
    cout << mxans << "\n";
    return 0;
}