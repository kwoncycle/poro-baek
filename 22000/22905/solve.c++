#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define X first
#define Y second
#define all(x) (x).begin(), (x).end()

const ll MOD = 1000000007;

struct SuffixArray{
    int n;
    vector<int> sa, rk, lcp;
    SuffixArray(vector<int> &s) : n(s.size()), sa(n), rk(n+1, -1), lcp(n) {
        for(int i=0; i<n; i++) sa[i] = i, rk[i] = s[i];
        for(int d=0; d<n; d = d ? (d<<1) : 1){
            vector<pii> g(n);
            vector<int> c(n + 256);
            for(int i=0; i<n; i++){
                c[rk[i]]++, g[i] = {rk[i], rk[min(n, i+d)]};
            }
            auto p=c, t=sa;
            for(int i=1; i<p.size(); i++) p[i] += p[i-1];
            auto upd = [&](int x){t[p[rk[x]] - (c[rk[x]]--)] = x; };
            for(int i=n-d; i<n; i++) upd(i);
            for(int i=0; i<n; i++){
                if(sa[i] >= d) upd(sa[i] - d);
            }
            swap(sa, t); rk[sa[0]] = 0;
            for(int i=1; i<n; i++){
                rk[sa[i]] = rk[sa[i-1]] + (g[sa[i]] != g[sa[i-1]]);
            }
        }
        rk.pop_back();
        for(int i=0, h=0; i<n; i++, h=max(h-1, 0)){
            if(rk[i]){
                while(max(i, sa[rk[i]-1]) + h < n && s[i+h] == s[sa[rk[i]-1] + h]) h++;
                lcp[rk[i]] = h;
            }
        }
    }
};

struct Segtree{
    int n = 300005;
    ll tree[1200100], lazy[1200100];

    Segtree(){
        for(int i=0; i<1200100; i++) lazy[i] = -1;
    }
    
    void update(int node, int st, int ed, int l, int r, ll v){
        FL(node, st, ed);
        if(l <= st and ed <= r){
            lazy[node] = v;
            FL(node, st, ed);
            return;
        }
        if(ed < l or r < st) return;
        update(node*2, st, (st+ed)/2, l, r, v);
        update(node*2 + 1, (st+ed)/2 + 1, ed, l, r, v);
        tree[node] = (tree[node*2] + tree[node*2 + 1]) % MOD;
    }

    void update(int l, int r, ll v){
        update(1, 0, n-1, l, r, v);
    }

    ll query(int node, int st, int ed, int l, int r){
        FL(node, st, ed);
        if(l <= st and ed <= r){
            return tree[node];
        }
        if(ed < l or r < st) return 0;
        return query(node*2, st, (st+ed)/2, l, r) + query(node*2 + 1, (st+ed)/2 + 1, ed, l, r);
    }

    ll query(int l, int r){
        return (MOD + query(1, 0, n-1, l, r) % MOD) % MOD;
    }

    void FL(int node, int st, int ed){
        if(lazy[node] == -1) return;
        tree[node] = (lazy[node] * (ed - st + 1)) % MOD;
        if(st != ed){
            lazy[node*2] = lazy[node];
            lazy[node*2 + 1] = lazy[node];
        }
        lazy[node] = -1;
    }
} SG_Height;

struct Seg1{
    int n = 300005;
    ll tree[1200100], lazy[1200100];
    ll sz[300005];
    Seg1(){
        for(int i=0; i<1200100; i++) lazy[i] = -1;
    }
    void update(int node, int st, int ed, int l, int r, ll v){
        FL(node, st, ed);
        if(l <= st and ed <= r){
            lazy[node] = v;
            FL(node, st, ed);
            return;
        }
        if(ed < l or r < st) return;
        update(node*2, st, (st+ed)/2, l, r, v);
        update(node*2 + 1, (st+ed)/2 + 1, ed, l, r, v);
        tree[node] = (tree[node*2] + tree[node*2 + 1]) % MOD;
    }

    void update(int l, int r, ll v){
        update(1, 0, n-1, l, r, v);
    }

    ll query(int node, int st, int ed, int l, int r){
        FL(node, st, ed);
        if(l <= st and ed <= r){
            return tree[node];
        }
        if(ed < l or r < st) return 0;
        return query(node*2, st, (st+ed)/2, l, r) + query(node*2 + 1, (st+ed)/2 + 1, ed, l, r);
    }

    ll query(int l, int r){
        return (MOD + query(1, 0, n-1, l, r) % MOD) % MOD;
    }

    ll sm(int l, int r){
        return (sz[r] - (l-1>=0 ? sz[l-1] : 0)) % MOD;
    }

    void FL(int node, int st, int ed){
        if(lazy[node] == -1) return;
        tree[node] = (lazy[node]*sm(st, ed) - lazy[node]*(lazy[node] - 1)/2%MOD*(ed-st+1)) % MOD;
        if(st != ed){
            lazy[node*2] = lazy[node];
            lazy[node*2 + 1] = lazy[node];
        }
        lazy[node] = -1;
    }
} SG_val;

int n, q;

vector<int> v;
unordered_map<int, int> mp;
int order[300005];
vector<pll> query[300005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> q;
    v.resize(n);
    int id = 1;
    for(auto &i:v){
        cin >> i;
        if(mp.find(i) == mp.end()){
            mp[i] = id; id++;
        }
        i = mp[i];
    }
    SuffixArray SA(v); SA.lcp.push_back(0);
    for(int i=0; i<n; i++){
        order[SA.sa[i]] = i;
    }

    for(int i=0; i<q; i++){
        int l, r; cin >> l >> r;
        l--; r--;
        query[order[l]].push_back({r - l + 1, i});
    }

    for(int i=0; i<n; i++){
        SG_val.sz[i] = n - SA.sa[i];
        if(i) SG_val.sz[i] = (SG_val.sz[i] + SG_val.sz[i-1]) % MOD;
    }

    vector<ll> ans(q);

    for(int i=n-1; i>=0; i--){
        SG_val.update(i, i, n - SA.sa[i]);
        SG_Height.update(i, i, n - SA.sa[i]);
        if(SG_Height.query(i+1, i+1) > SA.lcp[i+1]){
            int st = i+1, ed = n;
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(SG_Height.query(md, md) > SA.lcp[i+1]) st = md;
                else ed = md;
            }
            SG_Height.update(i+1, st, SA.lcp[i+1]);
            SG_val.update(i+1, st, SA.lcp[i+1]);
        }

        for(auto &[t, ans_id]:query[i]){
            int st = i, ed = n; // height[st] >= t
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(SG_Height.query(md, md) >= t) st = md;
                else ed = md;
            }
            if(ed <= n-1){
                ans[ans_id] = (ans[ans_id] + SG_val.query(ed, n-1)) % MOD;
            }
            ans[ans_id] = (ans[ans_id] + t*SG_val.sm(i, st)%MOD - (ll)(t-1)*t/2%MOD*(st-i+1)) % MOD;
        }
    }

    memset(SG_val.lazy, 0, sizeof(SG_val.lazy));
    memset(SG_val.tree, 0, sizeof(SG_val.tree));
    memset(SG_Height.lazy, 0, sizeof(SG_Height.lazy));
    memset(SG_Height.tree, 0, sizeof(SG_Height.tree));

    for(int i=0; i<n; i++){
        SG_val.update(i, i, n - SA.sa[i]);
        SG_Height.update(i, i, n - SA.sa[i]);
        if(i-1>=0 and SG_Height.query(i-1, i-1) > SA.lcp[i]){
            int st = -1, ed = i-1;
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(SG_Height.query(md, md) > SA.lcp[i]) ed = md;
                else st = md;
            }
            SG_Height.update(ed, i-1, SA.lcp[i]);
            SG_val.update(ed, i-1, SA.lcp[i]);
        }
        // cout << SA.sa[i] << " turn\n";
        // for(int j=0; j<n; j++) cout << SG_Height.query(j, j) << " "; cout << " H\n";
        // cout << SA.lcp[i] << " lcp\n";

        for(auto &[t, ans_id]:query[i]){
            int st = -1, ed = i; // height[ed] >= t
            while(st + 1 < ed){
                int md = (st + ed) / 2;
                if(SG_Height.query(md, md) >= t) ed = md;
                else st = md;
            }
            if(st >= 0){
                ans[ans_id] = (ans[ans_id] + SG_val.query(0, st)) % MOD;
            }
            if(ed <= i-1) ans[ans_id] = (ans[ans_id] + t*SG_val.sm(ed, i-1) - (t-1)*t/2%MOD*(i-ed)) % MOD;
        }
    }

    for(ll i:ans){
        if(i < 0) i += MOD;
        cout << i << "\n";
    }

    return 0;
}