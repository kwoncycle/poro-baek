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

struct SegTree{
    int n = 100050;
    int tree[500000];
    SegTree(){
        //init(1, 0, n-1);
    }
    void init(int node, int st, int ed){
        if(st == ed){
            tree[node] = 1;
            return;
        }
        init(node*2, st, (st+ed)/2);
        init(node*2 + 1, (st+ed)/2 + 1, ed);
        tree[node] = tree[node*2] + tree[node*2 + 1];
    }
    void update(int node, int st, int ed, int i, int v){
        if(i < st or ed < i) return;
        if(st == ed){
            tree[node] = v;
            return;
        }
        update(node*2, st, (st+ed)/2, i, v);
        update(node*2 + 1, (st+ed)/2 + 1, ed, i, v);
        tree[node] = tree[node*2] + tree[node*2 + 1];
    }
    void update(int i, int v){
        update(1, 0, n-1, i, v);
    }

    int query(int node, int st, int ed, int l, int r){
        if(ed < l or r < st) return 0;
        if(l <= st and ed <= r) return tree[node];
        return query(node*2, st, (st+ed)/2, l, r) + query(node*2 + 1, (st+ed)/2+1, ed, l, r);
    }
    
    int query(int l, int r){
        return query(1, 0, n-1, l, r);
    }
} S1, S2;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    pll s, e;
    cin >> s.X >> s.Y >> e.X >> e.Y;
    int n; cin >> n;
    vector<pll> L, R;
    ll cnt0 = 0, cnt1 = 0, ans = 0;
    for(int i=0; i<n; i++){
        pll p; cin >> p.X >> p.Y;
        ll o = (e-s) / (p-s);
        if(o == 0){
            if((p-s)*(e-s) >= 0) cnt0++;
            else cnt1++;
        }
        else if(o > 0) L.push_back(p);
        else R.push_back(p);
    }
    ans = cnt0 * (cnt0-1) / 2 + cnt1 * (cnt1-1) / 2;
    sort(all(L), [&](pll l, pll r){
        return (l-s)/(r-s) == 0 ? ((l-s)*(l-s) <= (r-s)*(r-s)) : ((l-s)/(r-s) > 0);
    });
    sort(all(R), [&](pll l, pll r){
        return (l-e)/(r-e) == 0 ? ((l-e)*(l-e) <= (r-e)*(r-e)) : ((l-e)/(r-e) > 0);
    });

    vector<int> iL(L.size()), iR(R.size());
    for(int i=0; i<(int)L.size(); i++) iL[i] = i;
    for(int i=0; i<(int)R.size(); i++) iR[i] = i;
    sort(all(iL), [&](int li, int ri){
        return (L[li]-e)/(L[ri]-e) == 0 ? ((L[li]-e)*(L[li]-e) <= (L[ri]-e)*(L[ri]-e)) : ((L[li]-e)/(L[ri]-e) < 0);
    });
    sort(all(iR), [&](int li, int ri){
        return (R[li]-s)/(R[ri]-s) == 0 ? ((R[li]-s)*(R[li]-s) <= (R[ri]-s)*(R[ri]-s)) : ((R[li]-s)/(R[ri]-s) < 0);
    });

    n = iL.size();
    for(int i=0; i<n; i++){
        ans += S1.query(0, iL[i]);
        S1.update(iL[i], 1);
    }

    n = iR.size();
    for(int i=0; i<n; i++){
        ans += S2.query(0, iR[i]);
        S2.update(iR[i], 1);
    }

    // for(int i:iL) cout << i << " "; cout << "\n";
    // for(int i:iR) cout << i << " "; cout << "\n";
    cout << ans << "\n";
    return 0;
}