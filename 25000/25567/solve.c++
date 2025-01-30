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

#define DEBUG 0

class djs
{
    ll n;
    vector<ll> par;
 
public:
    djs(ll n) : n(n) {
        par.resize(n);
        for(ll i=0; i<n; i++) par[i] = i;
    }
 
    ll find(ll v) {
        if(par[v] == v) return v;
        else return par[v] = find(par[v]);
    }
 
    bool Union(ll x, ll y) {
        ll px = find(x);
        ll py = find(y);
 
        if(px == py) return false;
 
        par[px] = py;
        return true;
    }
};
// Usage: djs DJS(n)
 
struct SegTree{
    ll n;
    vector<ll> arr, segtree;
    SegTree(ll ni, vector<ll>&arr1){
        arr.resize(ni);
        for(ll i=0; i<ni; i++) arr[i] = arr1[i];
        segtree = vector<ll>(4*ni+6, 0);
        n = ni;
        init(1, 0, n-1);
    }

    void init(ll node, ll start, ll end){
        if(start == end){
            segtree[node] = arr[start];
            return;
        }
        ll mid = (start + end)/2;
        init(node*2, start, mid);
        init(node*2+1, mid+1, end);
        segtree[node] = segtree[node*2] + segtree[node*2+1];
    }

    ll query(ll node, ll start, ll end, ll i1, ll i2){
        if(i2 < start or end < i1){
            return 0;
        }
        if(i1 <= start and end <= i2){
            return segtree[node];
        }
        ll mid = (start + end)/2;
        ll q1 = query(node*2, start, mid, i1, i2);
        ll q2 = query(node*2+1, mid+1, end, i1, i2);
        return q1 + q2;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n; cin >> n;
    vector<deque<ll>> v(n);
    vector<ll> located(200001, -1);
    djs DJS(200001);
    for(ll i=0; i<n; i++){
        ll t; cin >> t;
        while(t--){
            ll a; cin >> a;
            v[i].push_back(a);
            located[a] = i;
            DJS.Union(v[i][0], a);
        }
    }

    ll qq; cin >> qq;
    vector<array<ll ,3>> query(qq);
    for(ll i=0; i<qq; i++){
        cin >> query[i][0] >> query[i][1] >> query[i][2];
    }

    for(ll i=0; i<qq; i++){
        if(query[i][0] == 1){
            ll a = query[i][1], b = query[i][2];
            ll v_na = located[a], v_nb = located[b];
            if(v_na == v_nb) continue;
            ll s1 = v[v_na].size(), s2 = v[v_nb].size();
            if(s1 < s2){
                for(ll j=s1-1; j>=0; j--){
                    located[v[v_na][j]] = v_nb;
                    v[v_nb].push_front((v[v_na][j]));
                }
            }
            else{
                for(ll j=0; j<s2; j++){
                    located[v[v_nb][j]] = v_na;
                    v[v_na].push_back(v[v_nb][j]);
                }
            }
        }
    }

    vector<ll> aligned;
    vector<ll> checked(200001, 0);
    for(ll i=1; i<=200000; i++){
        if(located[i] < 0) continue;
        if(checked[i]) continue;
        ll o = located[i];
        for(ll j:v[o]) {
            aligned.push_back(j);
            checked[j] = 1;
        }
    }

    SegTree segtree((ll)aligned.size(), aligned);
    ll na = aligned.size();
    if(DEBUG) {
        cout << "ALIGNED===\n";
        for(ll i=0; i<na; i++) cout << aligned[i]  << " ";
        cout << "\n";
    }
    vector<ll> where(200001, 0);
    for(ll i=0; i<(ll)aligned.size(); i++){
        where[aligned[i]] = i;
    }



    for(ll i=0; i<qq; i++){
        ll a = query[i][1], b = query[i][2];
        if(query[i][0] == 1){
            bool b1 = DJS.Union(a, b);
            if(b1) cout << "YES\n";
            else cout << "NO\n";
        }
        else{
            if(DJS.find(a) == DJS.find(b)){
                int wa = where[a], wb = where[b];
                if(wa > wb) swap(wa, wb);
                cout << segtree.query(1, 0, na-1, wa, wb) << "\n";
            }
            else cout << "-1\n";
        }
    }
    return 0;
}