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

struct SuffixArray{
 int n;
 vector<int> sa,rk,lcp; // note: sa[rk[i]] = i
 SuffixArray(string&s):n(s.size()),sa(n),rk(n+1,-1),lcp(n){
  for(int i=0;i<n;i++) sa[i]=i, rk[i]=s[i];
  for(int d=0;d<n;d=d?d<<1:1){
   vector<pii> g(n);
   vector<int> c(max(256,n));
   for(int i=0;i<n;i++){
    c[rk[i]]++, g[i]={rk[i],rk[min(n,i+d)]};
   }
   auto p=c, t=sa;
   for(int i=1;i<p.size();i++) p[i]+=p[i-1];
   auto upd=[&](int x){t[ p[rk[x]] - (c[rk[x]]--) ]=x;};
   for(int i=n-d;i<n;i++) upd(i);
   for(int i=0;i<n;i++)if(sa[i]>=d) upd(sa[i]-d);
   swap(sa,t); rk[sa[0]]=0;
   for(int i=1;i<n;i++){
    rk[sa[i]]=rk[sa[i-1]]+(g[sa[i]]!=g[sa[i-1]]);
   }
  }
  rk.pop_back();
  for(int i=0,h=0;i<n;i++,h=max(h-1,0)) if(rk[i]){
   while(max(i,sa[rk[i]-1]) + h < n && s[i+h] == s[ sa[rk[i]-1]+h ]) h++;
   lcp[rk[i]] = h;
  }
 }
};

struct SegTree{
    int tree[404040];
    void update(int node, int st, int ed, int i, int v){
        if(ed < i or i < st) return;
        if(st == ed){
            tree[node] = v; return;
        }
        update(node*2, st, (st+ed)/2, i, v);
        update(node*2+1, (st+ed)/2+1, ed, i, v);
        tree[node] = min(tree[node*2], tree[node*2+1]);
    }
    void update(int i, int v){
        update(1, 0, 100000, i, v);
    }
    int query(int node, int st, int ed, int l, int r){
        if(ed < l or r < st) return 0x3f3f3f3f;
        if(l <= st and ed <= r) return tree[node];
        return min(query(node*2, st, (st+ed)/2, l, r), query(node*2+1, (st+ed)/2+1, ed, l, r));
    }
    int query(int l, int r){
        return query(1, 0, 100000, l, r);
    }
} ST;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s;
    getline(cin, s);
    int n = s.size();
    SuffixArray SA(s);
    for(int i=0; i<n; i++){
        ST.update(i, SA.lcp[i]);
    }
    set<int> st;
    for(int i=-1; i<=n; i++) st.insert(i);
    vector<int> DP(n+1);
    for(int i=n-1; i>=0; i--){
        int it = SA.rk[i];
        st.erase(it);
        auto a1 = st.upper_bound(it), a0 = a1;
        a0--;
        int i0 = *a0, i1 = *a1;
        int l = max(ST.query(i0+1, it), ST.query(it+1, i1));
        if(l == 0) DP[i] = DP[i+1] + 1;
        else{
            DP[i] = min(DP[i+1] + 1, DP[i+l] + 3);
        }
    }
    cout << DP[0] << "\n";
    return 0;
}