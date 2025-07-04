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

const ll INF = 1e9+11, MX = 1e9+10;
struct Line {
  ll a, b;
  Line() : a(0), b(-INF) {}  // min : INF , max : -INF
  Line(ll _a, ll _b) : a(_a), b(_b) {}
  ll operator()(ll x) { return a * x + b; }
};
struct Node {
  Line f;
  int lc, rc;
  Node() : f(), lc(-1), rc(-1) {}
};
struct LiChao {
  int root;
  vector<Node> NS;
  LiChao() {
    NS = vector<Node>();
    root = newNode();
  }
  int newNode() {
    NS.push_back(Node());
    return NS.size() - 1;
  }
  // Insert line p in O(logN)
  void update(int node, ll tl, ll tr, Line p) {
    ll mid = tl + tr >> 1;
    if (p(mid) > NS[node].f(mid)) swap(p, NS[node].f);  // min : < , max : >
    if (tl == tr) return;
    if (p(tl) > NS[node].f(tl)) {  // min : < , max : >
      if (NS[node].lc == -1) NS[node].lc = newNode();
      update(NS[node].lc, tl, mid, p);
    }
    if (p(tr) > NS[node].f(tr)) {  // min : < , max : >
      if (NS[node].rc == -1) NS[node].rc = newNode();
      update(NS[node].rc, mid + 1, tr, p);
    }
  }
  // Get min (or max) value at x in O(logN)
  ll query(int node, ll tl, ll tr, ll x) {
    if (node == -1) return -INF;  // min : INF , max : -INF
    ll mid = tl + tr >> 1;
    ll ret = NS[node].f(x);
    if (x <= mid) ret = max(ret, query(NS[node].lc, tl, mid, x));  // min : min() , max : max()
    else ret = max(ret, query(NS[node].rc, mid + 1, tr, x));  // min : min() , max : max()
    return ret;
  }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pll> v(n+1);
    for(int i=1; i<=n; i++) cin >> v[i].X >> v[i].Y;
    int m; cin >> m;
    vector<Line> l(m+2);
    for(int i=1; i<=m; i++) {
        ll a, b; cin >> a >> b;
        l[i] = Line(a, b);
    }
    l[m+1] = Line(0, MX);
    vector<pll> rng(n+1, {0, m+1}); // st up, ed down
    for(int u=0; u<20; u++){
        vector<vector<int>> task(m+1);
        for(int i=1; i<=n; i++){
            if(rng[i].X + 1 < rng[i].Y){
                int md = (rng[i].X + rng[i].Y)/2;
                assert(md < m+1);
                task[md].push_back(i);
            }
        }
        LiChao LC;
        
        for(int i=1; i<=m; i++){
            LC.update(0, -MX, MX, l[i]);
            for(int j:task[i]){
                if(LC.query(0, -MX, MX, v[j].X) > v[j].Y) rng[j].Y = i;
                else rng[j].X = i;
            }
        }
    }
    vector<vector<int>> ans(m+2);
    for(int i=1; i<=n; i++){
        ans[rng[i].Y].push_back(i);
    }
    
    for(int i=1; i<=m; i++){
        sort(all(ans[i]));
        cout << ans[i].size() << " ";
        for(int j:ans[i]) cout << j << " ";
        cout << "\n";
    }
    return 0;
}