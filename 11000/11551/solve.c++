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


// THIS IS LAZY
class SegTree{
public:   
    int n;
    vector<ll> arr, segtree, lazy;


    SegTree(int n_input, vector<ll> &input_arr){
        n = n_input;
        arr.resize(n);
        for(int i=0; i<n; i++) arr[i] = input_arr[i];
        lazy = vector<ll>(4*n+5, 0x3f3f3f3f3f3f3fll);
        segtree = vector<ll>(4*n+5, 0x3f3f3f3f3f3f3fll);
        init(1, 0, n-1);
    }
    void init(int node, int s, int e){
        if(s == e){
            segtree[node] = arr[s];
            return;
        }
        init(node * 2, s, (s + e)/2);
        init(node * 2 + 1, (s + e)/2 + 1, e);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
        return;
    }
    // add s~e += target
    void update_range(int i1, int i2, ll target){
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(int node, int s, int e, int i1, int i2, ll target){
        segtree[node] = min(segtree[node], lazy[node]);
        if(e != s){
            lazy[node * 2] = min(lazy[node], lazy[node * 2]);
            lazy[node * 2 + 1] = min(lazy[node], lazy[node * 2 + 1]);
        }
        lazy[node] = 0x3f3f3f3f3f3f3fll;
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] = min(lazy[node], target);
            segtree[node] = min(segtree[node], lazy[node]);
            if(e != s){
                lazy[node * 2] = min(lazy[node], lazy[node * 2]);
                lazy[node * 2 + 1] = min(lazy[node], lazy[node * 2 + 1]);
            }
            lazy[node] = 0x3f3f3f3f3f3f3fll;
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
    }

    ll query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    ll query_segtree(int node, int s, int e, int i1, int i2){
        segtree[node] = min(segtree[node], lazy[node]);
        if(e != s){
            lazy[node * 2] = min(lazy[node], lazy[node * 2]);
            lazy[node * 2 + 1] = min(lazy[node], lazy[node * 2 + 1]);
        }
        lazy[node] = 0x3f3f3f3f3f3f3fll;
        if(e < i1 or i2 < s) return 0x3f3f3f3f3f3f3fll;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        ll q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        ll q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return min(q1, q2);
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<ll> v(n+1);
    for(int i=1; i<=n; i++) cin >> v[i];
    vector<ll> pre(n+1);
    for(int i=1; i<=n; i++) pre[i] = pre[i-1] + v[i];
    vector<array<ll, 3>> s(m);
    for(int i=0; i<m; i++) cin >> s[i][0] >> s[i][1] >> s[i][2];
    sort(s.begin(), s.end());
    vector<ll> arr(n+1, 0x3f3f3f3f3f3f3fll); arr[0] = 0;
    SegTree sg(n+1, arr);
    for(int i=0; i<m; i++){
        int st = s[i][0], ed = n;
        if(pre[n] - pre[st-1] <= s[i][1]){
            st = n;
        }
        else if(pre[st] - pre[st-1] > s[i][1]){
            st = st - 1;
        }
        else{
            while(st + 1 < ed){
                int md = (st + ed)/2;
                if(pre[md] - pre[s[i][0]-1] <= s[i][1]) st = md;
                else ed = md;
            }
        }
        ll o = sg.query(s[i][0]-1, s[i][0]-1);
        sg.update_range(s[i][0]-1, st, o + s[i][2]);
    }
    ll o = sg.query(n, n);
    if(o > 0x3f3f3f3f3f3f) o = -1;
    cout << o << "\n";
    return 0;
}