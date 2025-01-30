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

struct SegTree_min{
public:   
    int n;
    vector<int> arr, segtree, lazy;
    SegTree_min(int n_input, vector<int> &input_arr){
        n = n_input;
        arr.resize(n);
        for(int i=0; i<n; i++) arr[i] = input_arr[i];
        lazy = vector<int>(4*n+5, 0x3f3f3f3f);
        segtree = vector<int>(4*n+5, 0x3f3f3f3f);
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
    void update_range(int i1, int i2, int target){
        if(i1 > i2) return;
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(int node, int s, int e, int i1, int i2, int target){
        segtree[node] = min(segtree[node], lazy[node]);
        if(e != s){
            lazy[node * 2] = min(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = min(lazy[node * 2 + 1], lazy[node]);
        }
        lazy[node] = 0x3f3f3f3f;
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] = min(lazy[node], target);
            segtree[node] = min(segtree[node], lazy[node]);
            if(e != s){
                lazy[node * 2] = min(lazy[node * 2], lazy[node]);
                lazy[node * 2 + 1] = min(lazy[node * 2 + 1], lazy[node]);
            }
            lazy[node] = 0x3f3f3f3f;
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
    }

    void update_one(int node, int s, int e, int i1, int target){
        segtree[node] = min(segtree[node], lazy[node]);
        if(e != s){
            lazy[node * 2] = min(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = min(lazy[node * 2 + 1], lazy[node]);
        }
        lazy[node] = 0x3f3f3f3f;
        if(e < i1 or i1 < s) return;
        if(i1 <= s and e <= i1){
            segtree[node] = target;
            lazy[node] = 0x3f3f3f3f;
            return;
        }
        update_one(node*2, s, (s + e)/2, i1, target);
        update_one(node*2 + 1, (s + e)/2 + 1, e, i1, target);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
    }

    int query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    int query_segtree(int node, int s, int e, int i1, int i2){
        segtree[node] = min(segtree[node], lazy[node]);
        if(e != s){
            lazy[node * 2] = min(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = min(lazy[node * 2 + 1], lazy[node]);
        }
        lazy[node] = 0x3f3f3f3f;
        if(e < i1 or i2 < s) return 0x3f3f3f3f;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        int q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        int q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return min(q1, q2);
    }
};


struct SegTree_max{
public:   
    int n;
    vector<int> arr, segtree, lazy;
    SegTree_max(int n_input, vector<int> &input_arr){
        n = n_input;
        arr.resize(n);
        for(int i=0; i<n; i++) arr[i] = input_arr[i];
        lazy = vector<int>(4*n+5, -0x3f3f3f3f);
        segtree = vector<int>(4*n+5, -0x3f3f3f3f);
        init(1, 0, n-1);
    }
    void init(int node, int s, int e){
        if(s == e){
            segtree[node] = arr[s];
            return;
        }
        init(node * 2, s, (s + e)/2);
        init(node * 2 + 1, (s + e)/2 + 1, e);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
        return;
    }
    // add s~e += target
    void update_range(int i1, int i2, int target){
        if(i1 > i2) return;
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(int node, int s, int e, int i1, int i2, int target){
        segtree[node] = max(segtree[node], lazy[node]);
        if(e != s){
            lazy[node * 2] = max(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
        }
        lazy[node] = -0x3f3f3f3f;
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] = max(lazy[node], target);
            segtree[node] = max(segtree[node], lazy[node]);
            if(e != s){
                lazy[node * 2] = max(lazy[node * 2], lazy[node]);
                lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
            }
            lazy[node] = -0x3f3f3f3f;
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }

    void update_one(int node, int s, int e, int i1, int target){
        segtree[node] = max(segtree[node], lazy[node]);
        if(e != s){
            lazy[node * 2] = max(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
        }
        lazy[node] = -0x3f3f3f3f;
        if(e < i1 or i1 < s) return;
        if(i1 <= s and e <= i1){
            segtree[node] = target;
            lazy[node] = -0x3f3f3f3f;
            return;
        }
        update_one(node*2, s, (s + e)/2, i1, target);
        update_one(node*2 + 1, (s + e)/2 + 1, e, i1, target);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }

    int query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    int query_segtree(int node, int s, int e, int i1, int i2){
        segtree[node] = max(segtree[node], lazy[node]);
        if(e != s){
            lazy[node * 2] = max(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
        }
        lazy[node] = -0x3f3f3f3f;
        if(e < i1 or i2 < s) return -0x3f3f3f3f;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        int q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        int q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return max(q1, q2);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, m, s; cin >> n >> m >> s;
    vector<pii> v(m);
    for(int i=0; i<m; i++) cin >> v[i].X >> v[i].Y;
    sort(v.begin(), v.end(), greater<pii>());
    vector<int> arr_min(n+1), arr_max(n+1);
    for(int i=1; i<=s; i++) arr_min[i] = s;
    for(int i=s+1; i<=n; i++) arr_min[i] = s+n;

    for(int i=1; i<s; i++) arr_max[i] = s - n;
    for(int i=s; i<=n; i++) arr_max[i] = s;
    
    SegTree_max Tmax(n+1, arr_max);
    SegTree_min Tmin(n+1, arr_min);

    for(int i=0; i<m; i++){
        int u1 = v[i].Y; int u2 = u1+1;
        if(u2 > n) u2 -= n;
        //min 56,66 -> 55,67
        int o1 = Tmin.query(u1, u1), o2 = Tmin.query(u2, u2);
        //u2-> o1-u1+u2
        //u1-> o2-u2+u1
        Tmin.update_one(1, 0, n, u1, o2-u2+u1);
        Tmin.update_one(1, 0, n, u2, o1-u1+u2);
        Tmin.update_range(1, u1, o2-u2+u1);
        Tmin.update_range(1, u2, o1-u1+u2);
        Tmin.update_range(u1+1, n, o2-u2+u1+n);
        Tmin.update_range(u2+1, n, o1-u1+u2+n);
        int o = u1;
        o++; if(o>n) o -= n;
        int t1 = Tmin.query(o, o);
        Tmin.update_range(1, o, t1);
        Tmin.update_range(o+1, n, t1+n);
        
        o = u2;
        o++; if(o>n) o -= n;
        t1 = Tmin.query(o, o);
        Tmin.update_range(1, o, t1);
        Tmin.update_range(o+1, n, t1+n);

        o1 = Tmax.query(u1, u1), o2 = Tmax.query(u2, u2);
        // 5-1,66 -> 55,60
        Tmax.update_one(1, 0, n, u1, o2-u2+u1);
        Tmax.update_one(1, 0, n, u2, o1-u1+u2);
        Tmax.update_range(u2, n, o1-u1+u2);
        Tmax.update_range(u1, n, o2-u2+u1);
        Tmax.update_range(1, u2-1, o1-u1+u2-n);
        Tmax.update_range(1, u1-1, o2-u2+u1-n);
        o = u1;
        o--; if(o == 0) o = n;
        {
            int t1 = Tmax.query(o, o);
            Tmax.update_range(o, n, t1);
            Tmax.update_range(1, o-1, t1-n);
        }
        o = u2; 
        o--; if(o == 0) o = n;
        {
            int t1 = Tmax.query(o, o);
            Tmax.update_range(o, n, t1);
            Tmax.update_range(1, o-1, t1-n);
        }
        //for(int i1=1; i1<=n; i1++) cout << Tmin.query(i1,i1)-i1 << " "; cout << "\n";
        //for(int i1=1; i1<=n; i1++) cout << i1-Tmax.query(i1,i1) << " "; cout << "\n";
    }
    
    for(int i=1; i<=n; i++){
        cout << min(Tmin.query(i,i)-i, i-Tmax.query(i,i)) << "\n";
    }
    return 0;
}