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

int v[200005], reach[200005];

struct SegTree{
    int n = 200003;
    ll tree[200003*4+4], lazy[200003*4+4];
    void update(int node, int st, int ed, int l, int r, int val){
        FL(node, st, ed);
        if(l <= st and ed <= r){
            lazy[node] = val;
            FL(node, st, ed);
            return;
        }
        if(r < st or ed < l) return;
        update(node*2, st, (st+ed)/2, l, r, val);
        update(node*2+1, (st+ed)/2+1, ed, l, r, val);
        tree[node] = tree[node*2] + tree[node*2 + 1];
    }

    void update(int l, int r, int val){
        update(1, 0, n-1, l, r, val);
    }

    ll query(int node, int st, int ed, int l, int r){
        FL(node, st, ed);
        if(r < st or ed < l) return 0;
        if(l <= st and ed <= r) return tree[node];
        return query(node*2, st, (st+ed)/2, l, r) + query(node*2 + 1, (st+ed)/2 + 1, ed, l, r);
    }

    ll query(int l, int r){
        return query(1, 0, n-1, l, r);
    }

    void FL(int node, int st, int ed){
        if(lazy[node] == 0) return;
        tree[node] = lazy[node] * (ed - st + 1);
        if(st != ed){
            lazy[node*2] = lazy[node];
            lazy[node*2 + 1] = lazy[node];
        }
        lazy[node] = 0;
    }
} SG;

const ll MOD = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    for(int i=1; i<=n; i++) {
        cin >> v[i];
    }
    vector<pii> G;
    for(int i=1; i<=n; i++){
        G.push_back({v[i], i});
    }
    sort(all(G)); reverse(all(G));
    set<int> st;
    st.insert(0); st.insert(n+1);
    
    for(int i=0; i<n; i++){
        auto t = st.lower_bound(G[i].Y); t--;
        reach[G[i].Y] = (*t);
        st.insert(G[i].Y);
    }

    ll ans = 0;
    vector<pii> gcdv;
    for(int i=1; i<=n; i++){
        gcdv.push_back({i, v[i]});
        vector<pii> ngcd;
        for(auto &[id, g]:gcdv){
            g = gcd(g, v[i]);
            while(!ngcd.empty() and ngcd.back().Y == g) ngcd.pop_back();
            ngcd.push_back({id, g});
        }
        gcdv = ngcd;
        SG.update(reach[i]+1, i, v[i]);
        for(int j=-1; j<(int)gcdv.size()-1; j++){
            ans = (ans + SG.query((j>=0 ? (gcdv[j].X + 1) : 1), gcdv[j+1].X) % MOD * gcdv[j+1].Y) % MOD;
        }
    }
    cout << ans << "\n";
}