#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

struct SegTree{
    ll n;
    vector<ll> tree, lazy, who;
    SegTree(ll _n) : n(_n){
        tree.resize(4*n + 5); lazy.resize(4*n + 5); who.resize(4*n + 5);
        init(1, 0, n-1);
    }

    void init(ll node, ll l, ll r){
        who[node] = l;
        if(l != r){
            init(node*2, l, (l+r)/2);
            init(node*2 + 1, (l+r)/2 + 1, r);
        }
    }

    void update(ll i1, ll i2, ll T){ // add i1~i2, T
        U(1, 0, n-1, i1, i2, T);
    }

    void U(ll node, ll l, ll r, ll i1, ll i2, ll T){
        flushlazy(node, l, r);
        if(i2 < l or r < i1) return;
        if(i1 <= l and r <= i2){
            lazy[node] = T; 
            flushlazy(node, l, r);
            return;
        }
        U(node*2, l, (l+r)/2, i1, i2, T);
        U(node*2 + 1, (l+r)/2 + 1, r, i1, i2, T);
        if(tree[node*2] < tree[node*2 + 1]) who[node] = who[node*2 + 1];
        else who[node] = who[node*2];
        tree[node] = max(tree[node*2], tree[node*2 + 1]);
    }

    pll query(ll i1, ll i2){
        return Q(1, 0, n-1, i1, i2);
    }

    pll Q(ll node, ll l, ll r, ll i1, ll i2){
        flushlazy(node, l, r);
        if(i2 < l or r < i1) return {-0x3f3f3f3f, -1};
        if(i1 <= l and r <= i2) return {tree[node], who[node]};
        pll q1 = Q(node*2, l, (l+r)/2, i1, i2);
        pll q2 = Q(node*2 + 1, (l+r)/2 + 1, r, i1, i2);
        return max(q1, q2);
    }

    void flushlazy(ll node, ll l, ll r){
        tree[node] += lazy[node];
        if(l != r){
            lazy[node*2] += lazy[node];
            lazy[node*2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
};

#define MX 200005

ll n;
vector<ll> graph[MX];
ll tp[MX];
ll depth[MX];
ll sparse[MX][25];
pii timeline[MX];
ll ett[MX];
ll ett_inv[MX];
SegTree SG(MX);
vector<array<ll, 3>> task[MX];

struct solve{
    ll clk = 0;
    solve(){
        cin >> n;
        for(ll i=0; i<n-1; i++){
            ll a,b; cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        depth[1] = 1;
        DFS(1, 0);
        for(ll i=1; i<=n; i++) sparse[i][0] = tp[i];
        for(ll d=1; d<25; d++){
            for(ll i=1; i<=n; i++){
                sparse[i][d] = sparse[sparse[i][d-1]][d-1];
            }
        }
        ll m; cin >> m;
        for(ll i=0; i<m; i++){
            ll i1, i2, val;
            cin >> i1 >> i2 >> val;
            assert(i1 != i2);
            if(ett_inv[i1] > ett_inv[i2]){
                swap(i1, i2);
            }
            ll l = LCA(i1, i2);
            if(l == i1){
                i1 = LCA1(i1, i2);
                addbox({1, timeline[i1].X - 1}, timeline[i2], val);
                addbox(timeline[i2], {timeline[i1].Y + 1, n}, val);
            }
            else{
                assert(i1 != l);
                addbox(timeline[i1], timeline[i2], val);
            }
        }
        ll ans = 0;
        pll ans_real = {1, 2};
        for(ll i=1; i<=n; i++){
            for(auto &[i1, i2, val]:task[i]){
                SG.update(i1, i2, val);
            }
            pll T = SG.query(1, n);
            assert(T.X == SG.query(T.Y, T.Y).X);
            if(ans < T.X){
                ans = T.X;
                ans_real = {ett[i], ett[T.Y]};
            }
        }
        if(m == 0) assert(ans == 0);
        cout << ans_real.X << " " << ans_real.Y << " " << ans << "\n";
    }

    void DFS(ll node, ll rt){
        clk++;
        timeline[node].X = clk; 
        ett_inv[node] = clk;
        ett[clk] = node;
        
        for(ll i:graph[node]){
            if(i != rt){
                tp[i] = node;
                depth[i] = depth[node] + 1;
                DFS(i, node);
            }
        }
        
        timeline[node].Y = clk;
    }

    ll LCA(ll l, ll r){
        if(depth[l] < depth[r]) swap(l, r);
        if(depth[l] > depth[r]){
            for(ll d=24; d>=0; d--){
                ll o = sparse[l][d];
                if(depth[o] >= depth[r]) l = o;
            }
        }
        if(l == r) return l;
        for(ll d=24; d>=0; d--){
            if(sparse[l][d] != sparse[r][d]){
                l = sparse[l][d];
                r = sparse[r][d];
            }
        }
        return tp[l];
    }

    ll LCA1(ll l, ll r){
        if(depth[l] < depth[r]) swap(l, r);
        if(depth[l] > depth[r]){
            for(ll d=24; d>=0; d--){
                ll o = sparse[l][d];
                if(depth[o] > depth[r]) l = o;
            }
        }
        return l;
    }

    void addbox(pii l, pii r, ll val){
        assert(l.Y < r.X);
        if(l.X > l.Y) return;
        if(r.X > r.Y) return;
        task[l.X].push_back({r.X, r.Y, val});
        task[l.Y+1].push_back({r.X, r.Y, -val});
    }
};




int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve s;
    return 0;
}