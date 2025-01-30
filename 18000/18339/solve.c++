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

#define MNMX -0x3f3f3f3f3f3f3f

struct SegTree{
    ll n;
    vector<array<ll, 2>> tree;
    SegTree(ll _n){
        n = _n;
        tree.resize(4*n+5);
    }

    void update(ll node, ll st, ll ed, ll idx, array<ll, 2> val){
        if(idx < st or ed < idx) return;
        if(st == ed and st == idx){
            tree[node] = val;
            return;
        }
        update(node*2, st, (st + ed)/2, idx, val);
        update(node*2 + 1, (st + ed)/2 + 1, ed, idx, val);
        tree[node] = max(tree[node*2], tree[node*2 + 1]);
    }

    array<ll, 2> query(ll node, ll st, ll ed, ll l, ll r){
        if(r < st or ed < l) return {MNMX, MNMX};
        if(l <= st and ed <= r) return tree[node];
        array<ll, 2> q1 = query(node*2, st, (st + ed)/2, l, r);
        array<ll, 2> q2 = query(node*2 + 1, (st + ed)/2 + 1, ed, l, r);
        return max(q1, q2);
    }
};



vector<pii> v(100005);
int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr); cout.tie(nullptr);
    ll n, s; cin >> n >> s;
    for(ll i=1; i<=n; i++) cin >> v[i].X >> v[i].Y;
    v[0] = {MNMX, MNMX};
    v[n+1] = {MNMX, MNMX};
    SegTree S1(n+4), S2(n+4);
    // S1: hj - xj, (xi <= xj)
    // S2: hj + xj, (xi > xj)
    for(ll i=1; i<=n; i++){
        S1.update(1, 0, n+3, i, {v[i].Y - v[i].X, -i});
        S2.update(1, 0, n+3, i, {v[i].Y + v[i].X, i});
    }

    ll ans = 0;
    ll cur = v[s].X, cur_id = s;
    vector<int> check(n+1, 1);
    for(ll i=1; i<=n-1; i++){
        S1.update(1, 0, n+3, cur_id, {MNMX, MNMX});
        S2.update(1, 0, n+3, cur_id, {MNMX, MNMX});
        check[cur_id] = 0;
        ll id1 = 0, id2 = n+1;
        if(cur_id-1 >= 1) id1 = S2.query(1, 0, n+3, 1, cur_id-1)[1];
        if(cur_id+1 <= n) id2 = -S1.query(1, 0, n+3, cur_id+1, n)[1];
        //assert(id1 < id2);
        assert(cur_id != 0 and cur_id != n+1);
        if(abs(id1) == -MNMX) id1 = 0;
        if(abs(id2) == -MNMX) id2 = n+1;
        assert(!(id1 == 0 and id2 == n+1));
        assert(id1 < cur_id and cur_id < id2);
        ll next_id;
        if(id1 == 0) next_id = id2;
        else if(id2 == n+1) next_id = id1;
        else{
            if((v[id1].Y - abs(v[id1].X - v[cur_id].X)) == (v[id2].Y - abs(v[id2].X - v[cur_id].X))){
                if(abs(v[id1].X - v[cur_id].X) <= abs(v[id2].X - v[cur_id].X)) next_id = id1;
                else next_id = id2;
            }
            else{
                next_id = (v[id1].Y - abs(v[id1].X - v[cur_id].X) > v[id2].Y - abs(v[id2].X - v[cur_id].X)) ? id1 : id2;
            }
        }
        ll next_cur = v[next_id].X;
        ans += abs(next_cur - cur);
        cur = next_cur;
        cur_id = next_id;
        assert(check[cur_id]);
    }

    cout << ans << "\n";
    return 0;
}