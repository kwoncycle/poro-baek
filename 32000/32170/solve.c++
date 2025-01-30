#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;


#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define X first
#define Y second
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
#define all(x) (x).begin(), (x).end()

typedef tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;
// CNT_LOWER: number of element in v smaller than n
// CNT_UPPER: number of element in v smaller or same than n

#define LINE array<pii, 2>
// LINE: l[0] + kl[1]

pii operator + (pii l, pii r){return {l.X+r.X, l.Y+r.Y};};
pii operator - (pii l, pii r){return {l.X-r.X, l.Y-r.Y};};
ll operator * (pii l, pii r){return (ll)l.X*r.X + (ll)l.Y*r.Y;};
ll operator / (pii l, pii r){return (ll)l.X*r.Y - (ll)l.Y*r.X;};

#define MOD 1000000007

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define pli pair<ll,int>
#define X first
#define Y second
#define GETVECTOR(n) for(int i=0; i< (n); i++) scanf("%d ",&inp[i]);
#define CNT_LOWER(v,n) (int)(lower_bound((v).begin(),(v).end(),(n))-(v).begin())
#define CNT_UPPER(v,n) (int)(upper_bound((v).begin(),(v).end(),(n))-(v).begin())
 

// THIS IS LAZY
class SegTree{
public:   
    int n;
    vector<int> segtree;

    SegTree(int n_input){
        n = n_input;
        segtree = vector<int>(4*n+5, 0);

    }

    // add s~e += target
    void update_range(int i1, int target){
        update_segtree(1, 0, n-1, i1, target);
    }

    void update_segtree(int node, int s, int e, int i1, int target){
        if(e < i1 or i1 < s) return;
        if(i1 <= s and e <= i1){
            segtree[node] += target;
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, target);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }

    ll query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    ll query_segtree(int node, int s, int e, int i1, int i2){
        if(e < i1 or i2 < s) return 0;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        ll q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        ll q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return q1 + q2;
    }

    int kth(int node, int s, int e, int k){
        if(s == e) return s;
        int left = segtree[node*2], right = segtree[node*2 + 1];
        int m = (s + e) / 2;
        if(left >= k) return kth(node*2, s, m, k);
        else return kth(node*2 + 1, m+1, e, k-left);
    }
};


ll poww(ll a, ll e){
    ll ans = 1;
    while(e){
        if(e&1) ans = ans * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return ans;
}

struct solve{
    int n;
    vector<int> a;
    solve(){
        cin >> n;
        a.resize(n);
        int mx = 0;
        for(int &i:a){
            cin >> i;
            mx = max(mx, (int)i);
        }
        int q; cin >> q;
        vector<pll> query(q);
        for(auto &[i, j] : query) cin >> i >> j;

        SegTree sg(9400000);
        vector<int> V;
        for(int i=0; i<n; i++){
            int a1 = a[i];
            while(a1 <= 1e9) V.push_back(a1), a1 *= 2;
        }
        sort(all(V));
        V.erase(unique(V.begin(), V.end()), V.end());
        map<int, int> mp;
        for(int i=0; i<(int)V.size(); i++){
            mp[V[i]] = i;
        }


        vector<int> qid(q);
        for(int i=0; i<q; i++) qid[i] = i;
        sort(all(qid), [&](int l, int r){
            return query[l] < query[r];
        });
        vector<ll> query_ans(q);
        vector<int> ans;
        int water = 0, id = 0;
        priority_queue<int, vector<int>, greater<int>> st;
        for(int i=0; i<n; i++){
            sg.update_range(mp[a[i]], 1);
            st.push(a[i]);
        }
        while(true){
            int val = st.top(); st.pop();
            sg.update_range(mp[val], -1);
            if(val > mx) break;
            ans.push_back(val);
            val <<= 1;
            st.push(val);
            sg.update_range(mp[val], 1);
            water += 1;
            while(id < q and query[qid[id]].X == water){
                query_ans[qid[id]] = V[sg.kth(1,0,9400000-1,query[qid[id]].Y)] % MOD;

                //query_ans[qid[id]] = (*st.find_by_order(query[qid[id]].Y-1)) % MOD;
                id += 1;
            }
        }

        for(int i=id; i<q; i++){
            int o = query[qid[i]].X + query[qid[i]].Y - 1;
            if(o < (int)ans.size()){
                query_ans[qid[i]] = ans[o] % MOD;
            }
            else{
                int t = ans.size();
                t = t / n * n + n + o%n;
                while(t >= ans.size()) t -= n;
                query_ans[qid[i]] = ans[t] % MOD * poww(2, (o-t)/n) % MOD;
            }
        }

        for(ll i:query_ans) cout << i << "\n";
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve s;
    return 0;
}