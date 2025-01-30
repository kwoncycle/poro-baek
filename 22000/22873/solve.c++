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


// THIS IS LAZY
class SegTree{
public:   
    int n;
    vector<ll> segtree, lazy;


    SegTree(int n_input){
        n = n_input;
        lazy = vector<ll>(4*n+5, 0);
        segtree = vector<ll>(4*n+5, 0);
    }

    // add s~e += target
    void update_range(int i1, int i2, ll target){
        update_segtree(1, 0, n-1, i1, i2, target);
    }

    void update_segtree(int node, int s, int e, int i1, int i2, ll target){
        segtree[node] += lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return;
        if(i1 <= s and e <= i2){
            lazy[node] += target;
            segtree[node] += lazy[node] * (e - s + 1);
            if(e != s){
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
            return;
        }
        update_segtree(node*2, s, (s + e)/2, i1, i2, target);
        update_segtree(node*2 + 1, (s + e)/2 + 1, e, i1, i2, target);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }

    ll query(int i1, int i2){
        return query_segtree(1, 0, n-1, i1, i2);
    }

    ll query_segtree(int node, int s, int e, int i1, int i2){
        segtree[node] += lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        if(e < i1 or i2 < s) return 0;
        if(i1 <= s and e <= i2){
            return segtree[node];
        }
        ll q1 = query_segtree(node*2, s, (s+e)/2, i1, i2);
        ll q2 = query_segtree(node*2 + 1, (s+e)/2 + 1, e, i1, i2);
        return q1 + q2;
    }

    ll find0(int node, int s, int e, int ed){ // find i s.t i~ed is all val
        segtree[node] += lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        int md = (s + e) / 2;
        if(s == e){
            return segtree[node] == 0 ? s : -1;
        }
        if(e == ed){
            if(segtree[node] == 0) return s;
            else{
                ll i1 = find0(node*2 + 1, md + 1, e, ed);
                if(i1 == md+1) {
                    ll i2 = find0(node*2, s, md, md);
                    return i2 == -1 ? i1 : i2;
                }
                else return i1;
            }
        }
        
        if(md < ed){
            ll i1 = find0(node*2 + 1, md + 1, e, ed);
            if(i1 == md + 1) {
                ll i2 = find0(node*2, s, md, md);
                return i2 == -1 ? i1 : i2;
            }
            else {
                return i1;
            }
        }
        else{
            return find0(node*2, s, md, ed);
        }
    }

    ll find9(int node, int s, int e, int ed){ // find i s.t i~ed is all val
        segtree[node] += lazy[node] * (e - s + 1);
        if(e != s){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
        int md = (s + e) / 2;
        if(s == e){
            return segtree[node] == 9 ? s : -1;
        }
        if(e == ed){
            if(segtree[node] == 9 * (e - s + 1)) return s;
            else{
                ll i1 = find9(node*2 + 1, md + 1, e, ed);
                if(i1 == md+1) {
                    ll i2 = find9(node*2, s, md, md);
                    return i2 == -1 ? i1 : i2;
                }
                else return i1;
            }
        }
        
        if(md < ed){
            ll i1 = find9(node*2 + 1, md + 1, e, ed);
            if(i1 == md + 1) {
                ll i2 = find9(node*2, s, md, md);
                return i2 == -1 ? i1 : i2;
            }
            else {
                return i1;
            }
        }
        else{
            return find9(node*2, s, md, ed);
        }
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n, qq; cin >> n >> qq;
    string as, bs; cin >> as >> bs;
    n++;
    as = "0" + as, bs = "0" + bs;
    vector<int> a(n), b(n);
    for(int i=0; i<n; i++) a[i] = as[i]-'0', b[i] = bs[i]-'0';
    vector<int> c(n);

    for(int i=n-1; i>=1; i--){
        c[i] += (a[i] + b[i]);
        c[i-1] += c[i]/10;
        c[i] %= 10;
    }
    
    SegTree tree(n);
    for(int i=0; i<n; i++){
        tree.update_range(i, i, c[i]);
    }

    while(qq--){
        //for(int i=0; i<n; i++) cout << tree.query(i, i); cout << "\n";
        char q; cin >> q;
        if(q == 'A'){
            int i, d; cin >> i >> d;
            i = n-i;
            if(a[i] == d) {
                cout << "0\n"; continue;
            }
            if(a[i] < d){
                int delta = d - a[i];
                a[i] = d;
                int o = tree.query(i, i);
                if(o + delta >= 10){
                    tree.update_range(i, i, delta - 10);
                    int id1 = tree.find9(1, 0, n-1, i-1);
                    if(id1 == -1){
                        tree.update_range(i-1, i-1, 1);
                        cout << "2\n"; continue;
                    }
                    else{
                        tree.update_range(id1, i-1, -9);
                        tree.update_range(id1-1, id1-1, 1);
                        cout << i - id1 + 1 + 1 << "\n"; continue;
                    }
                }
                else{
                    tree.update_range(i, i, delta);
                    cout << "1\n"; continue;
                }
            }
            else{
                int delta = a[i] - d;
                a[i] = d;
                int o = tree.query(i, i);
                if(o < delta){
                    tree.update_range(i, i, 10 - delta);
                    int id1 = tree.find0(1, 0, n-1, i-1);
                    if(id1 == -1){
                        tree.update_range(i-1, i-1, -1);
                        cout << "2\n"; continue;
                    }
                    else{
                        tree.update_range(id1, i-1, 9);
                        tree.update_range(id1-1, id1-1, -1);
                        cout << i - id1 + 1 + 1 << "\n"; continue;
                    }
                }
                else{
                    tree.update_range(i, i, -delta);
                    cout << "1\n";
                }
            }
        }
        else if(q == 'B'){
            int i, d; cin >> i >> d;
            i = n-i;
            if(b[i] == d) {
                cout << "0\n"; continue;
            }
            if(b[i] < d){
                int delta = d - b[i];
                b[i] = d;
                int o = tree.query(i, i);
                if(o + delta >= 10){
                    tree.update_range(i, i, delta - 10);
                    int id1 = tree.find9(1, 0, n-1, i-1);
                    if(id1 == -1){
                        tree.update_range(i-1, i-1, 1);
                        cout << "2\n"; continue;
                    }
                    else{
                        tree.update_range(id1, i-1, -9);
                        tree.update_range(id1-1, id1-1, 1);
                        cout << i - id1 + 1 + 1 << "\n"; continue;
                    }
                }
                else{
                    tree.update_range(i, i, delta);
                    cout << "1\n"; continue;
                }
            }
            else{
                int delta = b[i] - d;
                b[i] = d;
                int o = tree.query(i, i);
                if(o < delta){
                    tree.update_range(i, i, 10 - delta);
                    int id1 = tree.find0(1, 0, n-1, i-1);
                    if(id1 == -1){
                        tree.update_range(i-1, i-1, -1);
                        cout << "2\n"; continue;
                    }
                    else{
                        tree.update_range(id1, i-1, 9);
                        tree.update_range(id1-1, id1-1, -1);
                        cout << i - id1 + 1 + 1 << "\n"; continue;
                    }
                }
                else{
                    tree.update_range(i, i, -delta);
                    cout << "1\n";
                }
            }
        }
    }
    
    return 0;
}