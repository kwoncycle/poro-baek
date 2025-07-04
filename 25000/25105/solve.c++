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

const ll done = 0x4612983914ll;

struct SegTree{
    int n;
    vector<ll> tree, lazy;
    SegTree(int _n):n(_n){
        lazy.resize(4*n+5, done);
        tree.resize(4*n+5, 0);
    }
    
    // set s~e = target
    void update(int i1, int i2, ll target){
        U(1, 0, n-1, i1, i2, target);
    }

    void U(int node, int s, int e, int i1, int i2, ll target){
        lazyU(node, s, e);
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] = target;
            lazyU(node, s, e);
            return;
        }
        U(node*2, s, (s + e)/2, i1, i2, target);
        U(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll query(int i1, int i2){
        return Q(1, 0, n-1, i1, i2);
    }

    ll Q(int node, int s, int e, int i1, int i2){
        lazyU(node, s, e);
        if(e < i1 or i2 < s) return 0;
        if(i1 <= s and e <= i2){
            return tree[node];
        }
        ll q1 = Q(node*2, s, (s+e)/2, i1, i2);
        ll q2 = Q(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return q1 + q2;
    }

    void lazyU(int node, int s, int e){
        if(lazy[node] == done) return;
        tree[node] = lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = done;
    }
} SG(200005);

ll A[200004], B[200004], Bsm[200004];
set<array<ll, 2>> st;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, qq; cin >> n >> qq;
    for(int i=1; i<=n; i++) cin >> A[i];
    for(int i=1; i<=n; i++) cin >> B[i];
    for(int i=1; i<=n; i++) Bsm[i] = Bsm[i-1] + B[i];
    for(int i=1; i<=n; i++){
        SG.update(i, i, A[i] - A[i-1]);
    }
    for(int i=0; i<=n+1; i++) st.insert({i,i});

    while(qq--){
        int q; cin >> q;
        ll l, r, x; cin >> l >> r;
        if(q == 1) {
            cin >> x;
            auto p1 = st.lower_bound({l, 0x3f3f3f3fll});
            p1--;
            array<ll, 2> q1 = {(*p1)[0], l-1}, q2 = {l, (*p1)[1]};
            st.erase(p1);
            if(q1[0] <= q1[1]) st.insert(q1);
            if(q2[0] <= q2[1]) st.insert(q2);

            p1 = st.lower_bound({r, 0x3f3f3f3fll}); p1--;
            q1 = {(*p1)[0], r}, q2 = {r+1, (*p1)[1]};
            st.erase(p1);
            if(q1[0] <= q1[1]) st.insert(q1);
            if(q2[0] <= q2[1]) st.insert(q2);

            SG.update(l, l, SG.query(l,l) + x);
            SG.update(r+1, r+1, SG.query(r+1, r+1) - x);
        }
        else{
            vector<array<ll,2>> v;
            while(true){
                auto nxt = st.lower_bound({l, -1});
                if((*nxt)[1] <= r) {
                    v.push_back({SG.query(0, (*nxt)[0]), Bsm[(*nxt)[1]] - Bsm[(*nxt)[0]-1]});
                    st.erase(nxt);
                }
                else break;
            }
            auto p1 = st.lower_bound({l, -1}); 
            p1--;
            if(r < (*p1)[0] or (*p1)[1] < l) ;
            else{
                array<ll,2> q1 = {(*p1)[0], l-1}, q2 = {r+1, (*p1)[1]};
                ll l1 = max(l, (*p1)[0]), r1 = min(r, (*p1)[1]);
                if(l1 <= r1){
                    v.push_back({SG.query(0, l1), Bsm[r1] - Bsm[l1-1]});
                }
                st.erase(p1);
                if(q1[0] <= q1[1]) st.insert(q1);
                if(q2[0] <= q2[1]) st.insert(q2);
            }
            p1 = st.lower_bound({l, -1});
            if(r < (*p1)[0] or (*p1)[1] < l) ;
            else{
                array<ll,2> q1 = {(*p1)[0], l-1}, q2 = {r+1, (*p1)[1]};
                ll l1 = max(l, (*p1)[0]), r1 = min(r, (*p1)[1]);
                if(l1 <= r1){
                    v.push_back({SG.query(0, l1), Bsm[r1] - Bsm[l1-1]});
                }
                st.erase(p1);
                if(q1[0] <= q1[1]) st.insert(q1);
                if(q2[0] <= q2[1]) st.insert(q2);
            }
            sort(all(v));
            ll sm = 0;
            for(auto &[_, j]:v) sm += j;
            ll sm1 = 0;
            for(auto &[i, j]:v){
                sm1 += j;
                if(sm1*2 >= sm){
                    x = i; break;
                }
            }
            cout << x << "\n";
            ll val = SG.query(0, r+1);
            if(l+1 <= r){
                SG.update(l+1, r, 0);
            }
            SG.update(l, l, x - SG.query(0, l-1));
            SG.update(r+1, r+1, val - SG.query(0, r));
            st.insert({l, r});
        }
        //for(int i=1; i<=n; i++) cout << SG.query(0, i) << " "; cout << "aa\n";
        //for(auto [i,j]:st) cout << i << "," << j << " "; cout << "bb\n";
    }

    return 0;
}