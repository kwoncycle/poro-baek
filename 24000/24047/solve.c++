#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<ll,ll>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (ll)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (ll)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

struct SegTree{
    ll n;
    vector<ll> tree;
    SegTree(ll _n){
        n = _n;
        tree.resize(4*n+5);
    }

    void update(ll node, ll st, ll ed, ll idx, ll val){
        if(idx < st or ed < idx) return;
        if(st == ed and st == idx){
            tree[node] += val;
            return;
        }
        update(node*2, st, (st + ed)/2, idx, val);
        update(node*2 + 1, (st + ed)/2 + 1, ed, idx, val);
        tree[node] = (tree[node*2] + tree[node*2 + 1]);
    }

    ll query(ll node, ll st, ll ed, ll l, ll r){
        if(r < st or ed < l) return 0;
        if(l <= st and ed <= r) return tree[node];
        ll q1 = query(node*2, st, (st + ed)/2, l, r);
        ll q2 = query(node*2 + 1, (st + ed)/2 + 1, ed, l, r);
        return (q1 + q2);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, k; cin >> n >> k;
    vector<ll> v(n), v_inv(n);
    map<ll, ll> mp;
    for(ll i=0; i<n; i++) {
        cin >> v[i];
        mp[v[i]] = 0;
        v_inv[i] = v[i];
    }
    sort(v_inv.begin(), v_inv.end());
    ll cnt = 1;
    for(auto [i, _]:mp){
        mp[i] = cnt; cnt++;
    }

    for(ll i=0; i<n; i++){
        v[i] = mp[v[i]];
    }
    vector<ll> lw(n);
    SegTree Tree(n+1);
    vector<ll> cnt0(n+3), cnt1(n+3);
    for(ll i=0; i<n; i++){
        ll cnt = Tree.query(1, 0, n, 1, v[i]);
        cnt = i-cnt;
        lw[i] = cnt;
        cnt0[cnt+1]--;
        cnt0[1]++;
        Tree.update(1, 0, n, v[i], 1);
    }
    for(ll i=1; i<=n+1; i++) cnt0[i] = cnt0[i-1] + cnt0[i], cnt1[i] = cnt0[i];
    for(ll i=1; i<=n+1; i++) cnt1[i] = cnt1[i-1] + cnt1[i];
    if(cnt1[n-1] < k){
        cout << "-1\n";
        return 0;
    }
    if(cnt1[n-1] == k){
        for(ll i:v_inv) cout << i << " "; cout << "\n"; return 0;
    }
    ll id = 0;
    
    while(cnt1[id + 1] < k) id++;
    //cout << id << "\n";
    k -= cnt1[id];
    vector<ll> ans(n, -1);
    vector<ll> tmp;
    for(ll i=0; i<n; i++){
        if(lw[i] >= id) ans[i - id] = v[i];
        else tmp.push_back(v[i]);
    }
    sort(tmp.begin(), tmp.end(), greater<ll>());
    for(ll i=0; i<n; i++){
        if(ans[i] == -1){
            ans[i] = tmp.back(); tmp.pop_back();
        }
    }

    for(ll i=0; i<n-1; i++){
        if(ans[i] > ans[i+1]){
            swap(ans[i], ans[i+1]);
            k--;
            if(!k) break;
        }
    }

    //for(ll i=0; i<n; i++) cout << ans[i] << " "; cout << "a\n";
    for(ll i=0; i<n; i++) cout << v_inv[ans[i]-1] << " ";
    return 0;
}