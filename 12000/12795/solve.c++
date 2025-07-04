#include <bits/stdc++.h>
using namespace std;
 
typedef __int128 ll;
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


const ll INF = 3e22+11;
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
    LiChao LC;
    int qq; cin >> qq;
    while(qq--){
        int q; cin >> q;
        if(q == 1){
            long long a, b; cin >> a >> b;
            assert(abs(a) <= 1000'000 and abs(b) <= 1000'000'000'000ll);
            LC.update(0, -INF, INF, Line(a, b));
        }
        else{
            long long x; cin >> x;
            assert(abs(x) <= 1000'000'000'000ll);
            cout << (long long)LC.query(0, -INF, INF, x) << "\n";
        }
    }
    return 0;
}