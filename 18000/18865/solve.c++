#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
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

array<ll, 3> operator + (array<ll, 3> l, array<ll, 3> r){
    return {l[0]+r[0], l[1]+r[1], l[2]+r[2]};
}

array<ll, 3> operator * (array<ll, 3> l, ll r){
    return {l[0]*r, l[1]*r, l[2]*r};
}

// THIS IS LAZY
class SegTree{
public:   
    int n;
    vector<array<ll,3>> arr, segtree, lazy;


    SegTree(int n_input){
        n = n_input;
        arr.resize(n);
        //for(int i=0; i<n; i++) arr[i] = input_arr[i];
        lazy = vector<array<ll,3>>(4*n+5);
        segtree = vector<array<ll,3>>(4*n+5);
        //init(1, 0, n-1);
    }
    void init(int node, int s, int e){
        if(s == e){
            segtree[node] = arr[s];
            return;
        }
        init(node * 2, s, (s + e)/2);
        init(node * 2 + 1, (s + e)/2 + 1, e);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
        return;
    }
    // add s~e += target
    void update_range(int i1, int i2, array<ll,3> target){
        if(i1 > i2) return;
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(int node, int s, int e, int i1, int i2, array<ll,3> target){
        segtree[node] = segtree[node] + (lazy[node] * (e - s + 1));
        if(e != s){
            lazy[node * 2] = lazy[node * 2] + lazy[node];
            lazy[node * 2 + 1] = lazy[node * 2 + 1] + lazy[node];
        }
        lazy[node] = {0,0,0};
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] = lazy[node] + target;
            segtree[node] = segtree[node] + (lazy[node] * (e - s + 1));
            if(e != s){
                lazy[node * 2] = lazy[node * 2] + lazy[node];
                lazy[node * 2 + 1] = lazy[node * 2 + 1] + lazy[node];
            }
            lazy[node] = {0,0,0};
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }

    array<ll,3> query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    array<ll,3> query_segtree(int node, int s, int e, int i1, int i2){
        segtree[node] = segtree[node] + (lazy[node] * (e - s + 1));
        if(e != s){
            lazy[node * 2] = lazy[node * 2] + lazy[node];
            lazy[node * 2 + 1] = lazy[node * 2 + 1] + lazy[node];
        }
        lazy[node] = {0,0,0};
        if(e < i1 or i2 < s) return {0, 0, 0};
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        array<ll,3> q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        array<ll,3> q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return q1 + q2;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int swaped = 0;
    ll x, y, dx, dy;
    cin >> x >> y >> dx >> dy;
    x -= dx; y -= dy;
    if(abs(x) < abs(y)) {swap(x,y), swap(dx, dy), swaped = 1;}

    SegTree tree2(1000000);//, tree1(1000000), tree0(1000000);
    x = -x; y = -y;
    int qq; cin >> qq;
    while(qq--){
        int q; cin >> q;
        if(q == 1){
            ll nx, ny; cin >> nx >> ny;
            nx -= dx; nx -= dy;
            if(swaped) swap(nx, ny);
            
            ll t = nx + ny;
            tree2.update_range(t, t+y, {1, -2*t, t*t});

            tree2.update_range(t+y+1, t+x, {0, 2*y, -y*y-2*y*t});
            //tree0.update_range(t+y+1, t+x, -y*y-2*y*t);

            tree2.update_range(t+x+1, t+x+y, {-1, 2*(t+x+y), -(t+x+y)*(t+x+y)+2*x*y});
            //tree1.update_range(t+x+1, t+x+y, 2*(t+x+y));
            //tree0.update_range(t+x+1, t+x+y, -(t+x+y)*(t+x+y)+2*x*y);

            tree2.update_range(t+x+y+1, 999999, {0, 0, 2*x*y});
        }
        else{
            ll V;
            cin >> V;
            //cout << tree2.query(V, V) << " " << tree1.query(V, V) << " " << tree0.query(V, V) << "\n";
            array<ll, 3> o = tree2.query(V, V);
            ll ans = V*V*o[0] + V*o[1] + o[2];
            cout << ans << "\n";
        }
    }
    return 0;
}