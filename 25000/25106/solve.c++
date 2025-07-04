#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

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

struct T{
    ll lmx, rmx, mx, sm;
    T operator + (const T r){
        T ans;
        ans.lmx = max(lmx, sm + r.lmx);
        ans.rmx = max(r.rmx, rmx + r.sm);
        ans.mx = max({mx, r.mx, rmx + r.lmx});
        ans.sm = sm + r.sm;
        return ans;
    }
};

struct Node{
    int l, r;
    T val;
    Node(int _l, int _r, T _val) : l(_l), r(_r), val(_val){}
};


struct PST{
    int n;
    vector<Node> tree;
    vector<int> timeline;
    PST(int _n) : n(_n){
        int nd = add();
        init(nd, 0, n-1);
        timeline.push_back(nd);
    }
    void init(int nd, int st, int ed){
        if(st == ed) return;
        tree[nd].l = add();
        tree[nd].r = add();
        init(tree[nd].l, st, (st+ed)/2);
        init(tree[nd].r, (st+ed)/2 + 1, ed);
    }

    int update(int idx, T val){
        int nd1 = timeline.back();
        int nd2 = add();
        U(nd1, nd2, 0, n-1, idx, val);
        timeline.push_back(nd2);
        return nd2;
    }

    void U(int nd1, int nd2, int st, int ed, int idx, T val){ // set arr[idx] = val;
        if(idx < st or ed < idx){
            tree[nd2] = tree[nd1];
            return;
        }
        if(st == ed){
            tree[nd2].val = val;
            return;
        }
        if(idx <= (st + ed)/2){
            tree[nd2].r = tree[nd1].r;
            tree[nd2].l = add();
            U(tree[nd1].l, tree[nd2].l, st, (st+ed)/2, idx, val);
        }
        else{
            tree[nd2].l = tree[nd1].l;
            tree[nd2].r = add();
            U(tree[nd1].r, tree[nd2].r, (st+ed)/2 + 1, ed, idx, val);
        }
        tree[nd2].val = tree[tree[nd2].l].val + tree[tree[nd2].r].val;
    }

    int add(){
        tree.push_back(Node(0, 0, {0,0,0,0}));
        return tree.size() - 1;
    }

    T query(int idx, int i0, int i1){
        return Q(idx, 0, n-1, i0, i1);
    }

    T Q(int nd, int st, int ed, int i0, int i1){
        if(i1 < st or ed < i0) return T{0,0,0,0};
        if(i0 <= st and ed <= i1) return tree[nd].val;
        return Q(tree[nd].l, st, (st+ed)/2, i0, i1) + Q(tree[nd].r, (st+ed)/2 + 1, ed, i0, i1);
    }
} SG(300050);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int k; cin >> k;
    vector<array<int, 3>> v(k);
    for(auto &[i,j,t]:v) {
        cin >> i >> j >> t;
    }
    sort(all(v));
    vector<int> state;
    int i1 = 0;
    int id = 0;
    for(int i=0; i<=n; i++){
        while(i1 < (int)v.size() and v[i1][0] <= i){
            ll val = SG.query(SG.timeline.back(), v[i1][1], v[i1][1]).sm;
            T goin = {max(0ll, val + v[i1][2]), max(0ll, val + v[i1][2]), max(0ll, val + v[i1][2]), val + v[i1][2]};
            id = SG.update(v[i1][1], goin);
            i1++;
        }
        state.push_back(id);
    }
    T U = SG.query(state[5], 3, 8);
    int qq; cin >> qq;
    vector<ll> ans(3+qq, 0);
    for(int i=0; i<qq; i++){
        ll h, x, y; cin >> h >> x >> y;
        h ^= ans[i]; x ^= ans[i+1]; y ^= ans[i+2];
        ans[i+3] = SG.query(state[h], x, y).mx;
        cout << ans[i+3] << "\n";
    }

    return 0;
}