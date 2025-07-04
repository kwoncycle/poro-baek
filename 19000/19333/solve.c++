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

int n, m;
const ll MOD = 1000000007;

struct T{
    ll V[20];
    T operator + (ll r){
        T ans;
        for(int i=0; i<m; i++){
            ans.V[i] = (ans.V[i] + V[(i+m-r)%m]) % MOD;
        }
        return ans;
    }
} tree[20][200005];

ll v[1000000];

void init(int node, int st, int ed){
    if(st == ed){
        tree[node].V[v[st]] += 1;
        return;
    }
    init(node*2, st, (st+ed)/2);
    init(node*2 + 1, (st+ed)/2+1, ed);
    tree[node] = tree[node*2] + tree[node*2 + 1];
}

T Query(int node, int st, int ed, int l, int r){
    if(ed < l or r < st) return T;
    if(l <= st and ed <= r) return tree[node];
    return Query(node*2, st, (st+ed)/2, l, r) + Query(node*2 + 1, (st+ed)/2 + 1, ed, l, r);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m;
    for(int i=0; i<n; i++) {
        cin >> v[i]; v[i] %= m;
    }
    init(1, 0, n-1);
    int qq; cin >> qq;
    while(qq--){
        int l,r; cin >> l >> r;
        l--; r--;
        T ans = Query(1, 0, n-1, l, r);
        ll A = ans.V[0] % MOD;
        if(A < 0) A += MOD;
        cout << A << "\n";
    }


    return 0;
}