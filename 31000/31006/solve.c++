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


class SegTree
{
    int n;
    vector<ll> segtree, arr;
 
public:
    SegTree(int n_input, vector<ll>& arr_input){
        n = n_input;
        segtree = vector<ll>(4*n+10, 0);
        arr = vector<ll>(n);
        for(int i=0; i<n; i++) arr[i] = arr_input[i];
        init(1, 0, n-1);
    }

    void init(int node, int start, int end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        init(node*2, start, (start + end)/2);
        init(node*2 + 1, (start + end)/2 + 1, end);

        // CHANGE THIS AS WELL
        segtree[node] = segtree[node*2] + segtree[node*2 + 1];
    }
    void update(int target, ll val){
        arr[target] += val;
        update_segtree(1, 0, n-1, target, val);
    }
    void update_segtree(int node, int start, int end, int target, ll val) {
        if(target < start or end < target) return;
        if(start == end){
            segtree[node] += val;
            return;
        }

        update_segtree(2*node, start, (start + end)/2, target, val);
        update_segtree(2*node + 1, (start + end)/2 + 1, end, target, val);
        
        // CHANGE AS NEEDED
        segtree[node] = segtree[node*2] + segtree[node*2 + 1];
        return;
    }
 
    ll query(int node, int start, int end, int left, int right) {
        if(right < start or end < left) return 0;
        if(left <= start and end <= right) return segtree[node];

        ll q1 = query(node*2, start, (start + end)/2, left, right);
        ll q2 = query(node*2 + 1, (start + end)/2 + 1, end, left, right);

        // CHANGE AS NEEDED
        return q1 + q2;
    }
};

#define MOD 1000000007

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pii> v(n);
    for(int i=0; i<n; i++) cin >> v[i].X >> v[i].Y;
    sort(v.begin(), v.end(), [&](pii l, pii r){ return l.Y < r.Y; });
    map<int, int> mp;
    int id = 0;
    for(int i=0; i<n; i++){
        int o = v[i].Y;
        if(mp.find(o) == mp.end()) mp[o] = id++;
    }
    sort(v.begin(), v.end());
    vector<ll> ax(id), ay(id), cx(id), cy(id), an(id), cn(id);
    for(int i=0; i<n; i++){
        int o = mp[v[i].Y];
        cx[o] += v[i].X;
        cy[o] += v[i].Y;
        cn[o] ++;
    }
    SegTree A_x(id, ax), A_y(id, ay), C_x(id, cx), C_y(id, cy), A_n(id, an), C_n(id, cn);

    ll ttl = 0;

    for(int i=0; i<n; i++){
        int i1 = i;
        while(i1 < n and v[i].X == v[i1].X){
            int o = mp[v[i1].Y];
            C_x.update(o, -v[i1].X);
            C_y.update(o, -v[i1].Y);
            C_n.update(o, -1);
            i1++;
        }
        i1 = i;
        while(i1 < n and v[i].X == v[i1].X){
            int o = mp[v[i1].Y];
            if(o+1 <= id-1){
                ll smcx = C_x.query(1, 0, id-1, o+1, id-1) % MOD;
                ll smcy = C_y.query(1, 0, id-1, o+1, id-1) % MOD;
                ll smax = A_x.query(1, 0, id-1, o+1, id-1) % MOD;
                ll smay = A_y.query(1, 0, id-1, o+1, id-1) % MOD;
                ll smcn = C_n.query(1, 0, id-1, o+1, id-1) % MOD;
                ll sman = A_n.query(1, 0, id-1, o+1, id-1) % MOD;

                //cout << smcx << " " << smcy << " " << smax << " " << smay << " " << smcn << " " << sman << "\n";

                ll u = (smcx*smay%MOD) - (smcy*smax%MOD) - smcn*v[i1].X%MOD*smay%MOD + sman*v[i1].X%MOD*smcy%MOD - sman*v[i1].Y%MOD*smcx%MOD + smcn*v[i1].Y%MOD*smax%MOD;
                u %= MOD;
                ttl += u;
                ttl %= MOD;
            }
            i1++;
        }
        i1 = i;
        while(i1 < n and v[i].X == v[i1].X){
            int o = mp[v[i1].Y];
            A_x.update(o, v[i1].X);
            A_y.update(o, v[i1].Y);
            A_n.update(o, 1);
            i1++;
        }

        i = i1-1;
    }

    ttl %= MOD;
    if(ttl < 0) ttl += MOD;
    cout << ttl << "\n";
    return 0;
}